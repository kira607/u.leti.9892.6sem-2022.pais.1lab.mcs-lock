#ifndef INC_1LAB_PAS_3_2_COLOR_COLOR_H
#define INC_1LAB_PAS_3_2_COLOR_COLOR_H

#include <ostream>

enum class Color
{
    kRed,
    kBlue,
    kNone,
};

std::ostream& operator<< (std::ostream& out, Color color);

#endif //INC_1LAB_PAS_3_2_COLOR_COLOR_H
