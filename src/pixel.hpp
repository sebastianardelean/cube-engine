#pragma once
#include "cube.hpp"
struct pixel {
    cube::color_t color;
    int posX;
    int posY;

    bool operator==(const pixel &p) const {
        return (color == p.color && posX == p.posX && posY == p.posY);
    }

    bool operator!=(const pixel &p) const { return !(*this == p); }
};