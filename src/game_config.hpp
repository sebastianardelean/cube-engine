#pragma once
#include "cube.hpp"

struct cube::GameConfig
{
    static constexpr std::int32_t width = 800;
    static constexpr std::int32_t height = 600;
    const std::string title = "Test";
    static constexpr uint8_t framerate = 60;
};
