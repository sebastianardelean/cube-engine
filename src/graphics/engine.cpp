#include "../utils/utils.hpp"
#include "../utils/cube_exceptions.hpp"
#include "../utils/logger_manager.hpp"
#include "event_handler.hpp"
#include "game_scene.hpp"
#include "../game_config.hpp"
#include "engine.hpp"


std::unique_ptr<cube::Engine::SdlGlobalInitializer>
cube::Engine::p_SdlGlobalInitializer = std::make_unique<cube::Engine::SdlGlobalInitializer>();

cube::Engine::Engine(const cube::GameConfig &gameConfig) try:
        p_Window(utils::sdl_safe_create_window(gameConfig.title,SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,gameConfig.width,gameConfig.height,SDL_WINDOW_OPENGL),&SDL_DestroyWindow),
        gameConfig(gameConfig),
        bIsRunning(true)
{
    p_EventHandler =
            std::make_unique<EventHandler>(std::bind(&cube::Engine::InputEventHandler, this, std::placeholders::_1));
    p_RenderManager = std::make_unique<RenderManager>(p_Window.release());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

catch (const cubeexcept::SdlException &e) {
    LoggerManager::GetInstance().GetLogger()->error(e.what());
}


cube::Engine::~Engine() {

}

//p_Window->setFramerateLimit(framerate);


void cube::Engine::Run(cube::GameScene &game) {

    std::uint32_t *gamePixels= new std::uint32_t[gameConfig.width*gameConfig.height];
    std::int32_t pitch;
      //UserLoop
      //Render

    while(bIsRunning) {
        p_RenderManager->PrepareScene();
        p_EventHandler->PollEvent();
        game.UpdateScene();
        game.GetPixelsAndPitch(gamePixels,&pitch);
        p_RenderManager->Render(gamePixels,pitch);
    }
    delete [] gamePixels;


}

void cube::Engine::InputEventHandler(SDL_Event &event)
{
    switch (event.type) {
        case SDL_QUIT:
            LoggerManager::GetInstance().GetLogger()->info("Event");
            bIsRunning=false;
            break;
        default:
            break;
    }
}

void cube::Engine::Update() {
    //TODO: Call User handler for updating the scene
}

void cube::Engine::Draw() {

}

