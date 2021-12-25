/**
\file
\brief .cpp --file with implementation of PhilosophersRunner class
*/

#include "philisophersrunner.h"

PhilosophersRunner::PhilosophersRunner(int philosophersNumber) :
    m_Mersenne(std::chrono::system_clock::now().time_since_epoch().count()),
    m_Forks(philosophersNumber)
{

}

void PhilosophersRunner::Run(int steps, int chance) {
    m_Philosophers.clear();
    m_Changes.clear();
    for (size_t i = 0; i < m_Forks.size(); i++) {
        m_Philosophers.push_back(std::async(std::launch::async, &PhilosophersRunner::RunPhilosopher, this, i, steps, chance));
    }
}

void PhilosophersRunner::RunPhilosopher(int philosopher, int steps, int chance) {
    if (steps > 0) {
        int cur_chance;
        {
            std::lock_guard<std::mutex> chance_guard(m_ChanceMutex);
            cur_chance = m_Mersenne() % 100;
        }
        if (cur_chance < chance) {
            bool was_wait_message = false;
            while (true) {
                std::unique_lock<std::mutex> fork_guard1(m_Forks[philosopher], std::try_to_lock);
                std::unique_lock<std::mutex> fork_guard2(m_Forks[(philosopher+1)%m_Forks.size()], std::try_to_lock);
                if (!fork_guard1.owns_lock() || !fork_guard2.owns_lock()) {
                    if (!was_wait_message) {
                        std::lock_guard<std::mutex> output_guard(m_OutputMutex);
                        m_Changes.emplace_back(philosopher, TYPE::PH_WAIT);
                        was_wait_message = true;
                    }
                }
                else {
                    {
                        std::lock_guard<std::mutex> output_guard(m_OutputMutex);
                        m_Changes.emplace_back(philosopher, TYPE::PH_EAT);
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(20));
                    {
                        std::lock_guard<std::mutex> output_guard(m_OutputMutex);
                        m_Changes.emplace_back(philosopher, TYPE::PH_ORDINARY);
                    }
                    break;
                }
            }
        }
        else {
            std::lock_guard<std::mutex> output_guard(m_OutputMutex);
            m_Changes.emplace_back(philosopher, TYPE::PH_SPEAK);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        RunPhilosopher(philosopher, steps - 1, chance);
    }
    else {
        {
            std::lock_guard<std::mutex> output_guard(m_OutputMutex);
            m_Changes.emplace_back(philosopher, TYPE::PH_ORDINARY);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

const std::vector<std::pair<int, PhilosophersRunner::TYPE>>& PhilosophersRunner::GetResult(){
    m_Philosophers.clear();
    return m_Changes;
}
