/**
\file
\brief .h file with definition of PhilosophersRunner class
*/

#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <future>
#include <chrono>
#include <random>
#include <utility>

/**
\brief class definition of PhilosophersRunner
*/
class PhilosophersRunner {
public:
    /**
    \brief enumeration of actions of philosophers
    */
    enum class TYPE{
        PH_ORDINARY,
        PH_EAT,
        PH_WAIT,
        PH_SPEAK
    };

    /**
    \brief PhilosophersRunner ctor

    \param philosophersNumber number of philosophers
    */
    PhilosophersRunner(int philosophersNumber);

    /**
    \brief runs philosophers actions in different threads

    \param steps number of actions
    \param chance chance of "philosopher wants to eat" event
    */
    void Run(int steps, int chance);

    /**
    \brief runs single philosopher's one action, invoked recursively

    \param philosopher number of run philosopher
    \param steps number of actions
    \param chance chance of "philosopher wants to eat" event
    */
    void RunPhilosopher(int philosopher, int steps, int chance);

    /**
    \brief returns all changes after run operation
    */
    const std::vector<std::pair<int, TYPE>>& GetResult();
private:
    std::mt19937 m_Mersenne;
    std::vector<std::mutex>m_Forks;
    std::mutex m_OutputMutex;
    std::mutex m_ChanceMutex;
    std::vector<std::future<void>>m_Philosophers;
    std::vector<std::pair<int, TYPE>>m_Changes;
};
