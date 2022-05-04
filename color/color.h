//
// Created by kirill on 02.05.22.
//

#ifndef INC_1LAB_PAS_3_2_COLOR_H
#define INC_1LAB_PAS_3_2_COLOR_H

#include <ostream>

enum class Color
{
    kRed,
    kBlue,
    kNone,
};

///
/// @brief Insertion operator
///
/// @param[in] out Ostream object
/// @param[in] color Color to set
///
/// @note Outputs control character that sets color of text in terminal.
/// @warning If you don't reset color, all text that goes further in terminal will be colored with last set color
///
/// @return object ostream with color.
///
std::ostream& operator<< (std::ostream& out, Color color);

#endif //INC_1LAB_PAS_3_2_COLOR_H
