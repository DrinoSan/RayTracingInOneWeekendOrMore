//
// Created by Sandrino Becirbegovic on 11.12.21.
//

#pragma once

#include <iostream>

// Custom header
#include "Vec3.h"

void write_color(std::ostream &out, color pixel_color)
{
    // Write the trasnlated [0, 255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

