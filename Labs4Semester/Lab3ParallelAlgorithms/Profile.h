/**
\file
\brief .h file with definition of profile class
*/

#pragma once

#include <chrono>
#include <iostream>
#include <string>

/**
\brief class definition of profile
*/
class LogDuration {
public:
    /**
    \brief LogDuration ctor

    \param msg message after duration calculated
    */
    explicit LogDuration(const std::string& msg = "");

    /**
    \brief Visualizer dtor

    \note message will be shown here
    */
    ~LogDuration();
private:
    std::string message;
    std::chrono::steady_clock::time_point start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) \
  LogDuration UNIQ_ID(__LINE__){message};
