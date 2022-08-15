#pragma once
#include "vector2d.hpp"
#include "cube.hpp"
struct vertex_t
{

    cube::vector2df position;
    cube::color_t color;
    cube::vector2df textureCoords;
};
