
#include "timer.h"
#include <cstdio>

void Timer::Start() {
    m_accumulated_ms = 0;
    m_start  = Clock::now();
    running  = true;
}

void Timer::Pause() {
    if (!running) return;
    m_accumulated_ms += ElapsedMs();
    running = false;
}

void Timer::Resume() {
    if (running) return;
    m_start = Clock::now();
    running = true;
}

void Timer::Reset() {
    running          = false;
    m_accumulated_ms = 0;
}

void Timer::RecordLap()
{
    if (!running) return;
    laps.push_back({ ElapsedMs() });
    m_accumulated_ms = 0;
    m_start = Clock::now();      // reset for next question
}

uint32_t Timer::ElapsedMs() const {
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

const char* FormatTime(uint32_t ms) {
    static char buf[16];
    uint32_t total_s = ms / 1000;
    uint32_t minutes = total_s / 60;
    uint32_t seconds = total_s % 60;
    std::snprintf(buf, sizeof(buf), "%02u:%02u", minutes, seconds);
    return buf;
}