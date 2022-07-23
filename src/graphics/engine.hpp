#pragma once
#include "../cube.hpp"
#include "render_manager.hpp"
#include "../game_config.hpp"
class EventHandler;

class cube::Engine {
public:
    Engine(const cube::GameConfig &gameConfig);
    Engine(const Engine &) = delete;
    Engine(Engine &&) = delete;
    Engine &operator=(const Engine &) = delete;
    Engine &operator=(Engine &&) = delete;

    ~Engine();
    void Run(GameScene &game);
protected:

private:
    void Draw();
    void Update();
    void InputEventHandler(SDL_Event &event);


    class SdlGlobalInitializer
    {
    public:
        SdlGlobalInitializer() {SDL_Init(SDL_INIT_EVERYTHING);}
        ~SdlGlobalInitializer() {SDL_Quit();}
    };
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> p_Window;

    std::atomic<bool> bIsRunning;

    std::unique_ptr<EventHandler> p_EventHandler;
    std::unique_ptr<RenderManager> p_RenderManager;
    std::unique_ptr<cube::GameScene> p_GameScene;
    cube::GameConfig gameConfig;
    static std::unique_ptr<Engine::SdlGlobalInitializer>p_SdlGlobalInitializer;


};