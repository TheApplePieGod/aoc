#pragma once

#include <string>
#include <iostream>
#include <chrono>

#include "Base.h"

class Timer
{
public:
    Timer(const std::string& name, bool shouldLog = true)
        : m_Name(name), m_ShouldLog(shouldLog)
    { Reset(); }

    Timer()
    { Reset(); }

    ~Timer()
    {
        if (m_ShouldLog)
            Log();
    }

    inline void Log()
    {
        if (!m_Name.empty())
            std::cout << m_Name << " took " << static_cast<u32>(ElapsedMilliseconds()) << "ms" << std::endl;
    }

    inline void Reset() { m_Start = std::chrono::high_resolution_clock::now(); }

    inline void SetName(const std::string& newName) { m_Name = newName; } 

    inline double ElapsedSeconds()
    {
        return ElapsedNanoseconds() * 0.000000001;
    }

    inline double ElapsedMilliseconds()
    {
        return ElapsedNanoseconds() * 0.000001;
    }

    inline double ElapsedNanoseconds()
    {
        auto stop = std::chrono::high_resolution_clock::now();
        return static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(stop - m_Start).count());
    }

protected:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
    std::string m_Name;
    bool m_ShouldLog;
};