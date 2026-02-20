#ifndef SESSION_H_
#define SESSION_H_

#include "timer.h"
#include <string>
#include <vector>
#include <cstdint>

enum class Section : uint8_t { None, QA, DILR, VARC };

const char* SectionName(Section s);

struct Session {
    std::string              name;
    std::vector<std::string> tags;
    Section                  current_section = Section::None;
    int64_t                  unix_start      = 0;
    uint32_t                 target_ms       = 120000; // default 2 min per question
    Timer                    timer;
};

#endif // SESSION_H_