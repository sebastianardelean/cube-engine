#pragma once
namespace cube {
    using vector2di = Eigen::Vector2i;
    using vector2df = Eigen::Vector2f;
    using vector2dd = Eigen::Vector2d;
    using color_t = SDL_Color;

    struct GameConfig;

    //Viewport support
    class Engine;
    class GameScene;
};