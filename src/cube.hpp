#pragma once
#include "vector2d.hpp"
namespace cube {
    using vector2di = vector2d<std::int32_t>;
    using vector2du = vector2d<std::uint32_t>;
    using vector2df = vector2d<float>;
    using vector2dd = vector2d<double>;
    using color_t = SDL_Color;

    struct GameConfig;

    //Viewport support
    class Engine;
    class GameScene;
};