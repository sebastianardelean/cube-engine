#pragma once

#include "../cube.hpp"

class cube::GameScene {
public:
    GameScene(const cube::GameConfig &gameConfig) ;
    virtual ~GameScene();
    GameScene(const GameScene &) = delete;
    GameScene(GameScene &&) = delete;
    GameScene &operator=(const GameScene &) = delete;
    GameScene &operator=(GameScene &&) = delete;

    void UpdateScene();
    void GetPixelsAndPitch(std::uint32_t *pixels, std::int32_t *pitch);
protected:
    virtual void DrawScene() {}
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> p_Surface;
    std::vector<SDL_Rect> viewports;
};



