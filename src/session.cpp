#include "session.h"

const char* SectionName(Section s)
{
    switch (s) {
    case Section::AAA:
        return "AAA";
    case Section::BBB:
        return "BBB";
    case Section::CCC:
        return "CCC";
    default:
        return "None";
    }
}