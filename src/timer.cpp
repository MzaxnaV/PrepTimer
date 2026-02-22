#include "timer.h"

#include <cstdio>

void Timer::Start()
{
    m_accumulated_ms = 0;
    m_start  = Clock::now();
    running  = true;
}

void Timer::Pause()
{
    if (!running) return;
    m_accumulated_ms = ElapsedMs();
    running = false;
}

void Timer::Resume()
{
    if (running) return;
    m_start = Clock::now();
    running = true;
}

void Timer::Reset()
{
    running          = false;
    m_accumulated_ms = 0;
}

void Timer::RecordLap()
{
    if (!running) return;
    auto now     = Clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start);
    laps.push_back({ m_accumulated_ms + static_cast<uint32_t>(elapsed.count()) });
    m_accumulated_ms = 0;
    m_start          = now;   // next question starts at the exact same instant
}

uint32_t Timer::ElapsedMs() const
{
    if (!running)
        return m_accumulated_ms;

    auto now     = Clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start);
    return m_accumulated_ms + static_cast<uint32_t>(elapsed.count());
}

uint32_t Timer::AverageLapMs() const
{
    if (laps.empty()) return 0;
    uint32_t total = 0;
    for (const auto& lap : laps)
        total += lap.duration_ms;
    return total / static_cast<uint32_t>(laps.size());
}

StrBuf FormatTime(uint32_t ms)
{
    StrBuf buf = {};
    uint32_t total_s = ms / 1000;
    std::snprintf(buf.data, sizeof(buf.data), "%02u:%02u", total_s / 60, total_s % 60);
    return buf;
}
