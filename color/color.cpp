//
// Created by kirill on 02.05.22.
//

#include "color.h"

std::ostream& operator<< (std::ostream& out, Color color)
{
    switch(color)
    {
        case Color::kRed  :  out << "\033[31m"; break;
        case Color::kBlue :  out << "\033[34m"; break;
        case Color::kNone :  out << "\033[0m" ; break;
        default          :  out.setstate(std::ios_base::failbit); break;
    }
    return out;
}