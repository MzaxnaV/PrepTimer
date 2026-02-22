#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>
#include <cstdint>
#include <vector>

struct Lap {
    uint32_t duration_ms;
};

struct Timer {
    bool running = false;
    std::vector<Lap> laps;

    void Start();
    void Pause();
    void Resume();
    void Reset();

    void RecordLap();        // saves current elapsed, resets for next question
    // Returns elapsed time for current question in milliseconds
    [[nodiscard]] uint32_t ElapsedMs()      const;
    [[nodiscard]] uint32_t AverageLapMs()   const;

private:
    using Clock     = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    TimePoint m_start;
    uint32_t  m_accumulated_ms = 0; // stores time across pause/resume
};

// Small fixed-size stack buffer for short display strings.
// Returned by value so each call site gets independent storage.
struct StrBuf {
    char data[16];
};

// Formats milliseconds as "MM:SS"
[[nodiscard]] StrBuf FormatTime(uint32_t ms);

#endif // TIMER_H_