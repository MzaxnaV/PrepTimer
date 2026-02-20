
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

uint32_t Timer::ElapsedMs() const {
    if (!running)
        return m_accumulated_ms;

    auto now     = Clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start);
    return m_accumulated_ms + static_cast<uint32_t>(elapsed.count());
}

const char* FormatTime(uint32_t ms) {
    static char buf[16];
    uint32_t total_s = ms / 1000;
    uint32_t minutes = total_s / 60;
    uint32_t seconds = total_s % 60;
    std::snprintf(buf, sizeof(buf), "%02u:%02u", minutes, seconds);
    return buf;
}