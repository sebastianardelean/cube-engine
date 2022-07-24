#pragma once

namespace cube {
    using CubeColor = SDL_Color;
    struct GameConfig;
    class Sprite;
    class Shape; // will have draw line function; and fill with color; one constructor will have a vector of points as params
    class Triangle; //inherits shape

    class Vertex; //2D header only vertex
    class Engine;
    class GameScene;
};