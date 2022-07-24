#pragma once
#include "render_manager.hpp"
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
    void SetRenderer(RenderManager* renderer);
    void EventKeyPressed(SDL_Keycode key);
 //   void GetPixelsAndPitch(std::uint32_t *pixels, std::int32_t *pitch);
protected:
    void WriteText(int x, int y, const std::string &text, const cube::color_t &color);
    void DrawLine(int x1,int y1,int x2,int y2,const cube::color_t &color);
    virtual void DrawScene() {}
    virtual void OnKeyPressed(SDL_Keycode key) {}
    std::unique_ptr<RenderManager> p_Renderer;
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> p_Surface;

    std::vector<SDL_Rect> viewports;
};



