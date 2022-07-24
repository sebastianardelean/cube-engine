#pragma once

namespace cube {
    using color_t = SDL_Color;
    struct GameConfig;

    class Shape; // will have draw line function; and fill with color_t; one constructor will have a vector of points as params
    class Triangle; //inherits shape

    class Vertex; //2D header only vertex
    class Engine;
    class GameScene;
};