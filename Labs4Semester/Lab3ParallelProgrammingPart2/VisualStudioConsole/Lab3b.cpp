#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <future>
#include <chrono>
#include <random>

class PhilosophersRunner {
public:
    PhilosophersRunner(int philosophersNumber) :
        m_Mersenne(m_RandomDevice()),
        m_Forks(philosophersNumber) {

    }

    void Run(int steps, int delay) {
        m_Philosophers.clear();
        for (size_t i = 0; i < m_Forks.size(); i++) {
            m_Philosophers.push_back(std::async(std::launch::async, &PhilosophersRunner::RunPhilosopher, this, i, steps, delay));
        }
    }
    
    void RunPhilosopher(int philosopher, int steps, int delay) {
        if (steps > 0) {
            int chance;
            {
                std::lock_guard<std::mutex> chance_guard(m_ChanceMutex);
                chance = m_Mersenne() % 100;
            }
            if (chance < 50) {
                bool was_wait_message = false;
                while (true) {
                    std::unique_lock<std::mutex> fork_guard1(m_Forks[philosopher], std::try_to_lock);
                    std::unique_lock<std::mutex> fork_guard2(m_Forks[(philosopher+1)%m_Forks.size()], std::try_to_lock);
                    if (!fork_guard1.owns_lock() || !fork_guard2.owns_lock()) {
                        if (!was_wait_message) {
                            std::lock_guard<std::mutex> output_guard(m_OutputMutex);
                            std::cout << "Philosopher " << philosopher << " is waiting for forks" << std::endl;
                            was_wait_message = true;
                        }
                    }
                    else {
                        std::lock_guard<std::mutex> output_guard(m_OutputMutex);
                        std::cout << "Philosopher " << philosopher << " is eating" << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                        break;
                    }
                }
            }
            else {
                std::lock_guard<std::mutex> output_guard(m_OutputMutex);
                std::cout << "Philosopher " << philosopher << " is speaking" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            RunPhilosopher(philosopher, steps - 1, delay);
        }
        else {
            {
                std::lock_guard<std::mutex> output_guard(m_OutputMutex);
                std::cout << "Philosopher " << philosopher << " finished" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }

private:
    std::random_device m_RandomDevice;
    std::mt19937 m_Mersenne;
    std::vector<std::mutex>m_Forks;
    std::mutex m_OutputMutex;
    std::mutex m_ChanceMutex;
    std::vector<std::future<void>>m_Philosophers;
};

int main()
{
    PhilosophersRunner runner(8);
    runner.Run(10, 50);
}
