#pragma once
#include "../cube.hpp"
struct pixel {
    cube::color_t color;
    int x;
    int y;

    bool operator==(const pixel &p) const {
        auto checkIfColorsAreEqual=[](const cube::color_t &c1, const cube::color_t &c2) {
            return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
        };
        return (checkIfColorsAreEqual(color, p.color) && x == p.x && y == p.y);
    }

    bool operator!=(const pixel &p) const { return !(*this == p); }
};