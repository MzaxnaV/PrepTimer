#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>
#include <cstdint>

struct Timer {
    bool running = false;

    void Start();
    void Pause();
    void Resume();
    void Reset();

    // Returns elapsed time for current question in milliseconds
    uint32_t ElapsedMs() const;

private:
    using Clock     = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    TimePoint m_start;
    uint32_t  m_accumulated_ms = 0; // stores time across pause/resume
};

// Formats milliseconds as "MM:SS"
const char* FormatTime(uint32_t ms);

#endif // TIMER_H_