#include "session.h"

const char* SectionName(Section s)
{
    switch (s) {
    case Section::QA:   return "QA";
    case Section::DILR: return "DILR";
    case Section::VARC: return "VARC";
    default:            return "None";
    }
}