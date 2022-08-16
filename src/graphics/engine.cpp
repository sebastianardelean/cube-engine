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


void cube::Engine::Run(cube::GameScene *game) {

    std::uint32_t *gamePixels= new std::uint32_t[gameConfig.width*gameConfig.height];
    std::int32_t pitch;
      //UserLoop
      //Render
    p_GameScene.reset(game);
    p_GameScene->SetRenderer(p_RenderManager.release());
    while(bIsRunning) {
        timePoint2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = timePoint2 - timePoint1;
        timePoint1 = timePoint2;

        f_ElapsedTime = elapsedTime.count();
        f_LastElapsedTime = f_ElapsedTime;


        p_EventHandler->PollEvent();

        p_GameScene->UpdateScene();






        f_FrameTimer += f_ElapsedTime;
        n_FrameCounter++;
        if (f_FrameTimer >= 1.0f) {
            n_LastFPS = n_FrameCounter;
            f_FrameTimer -= 1.0f;
            std::string fpsInfo = "FPS "+std::to_string(n_FrameCounter);
            LoggerManager::GetInstance().GetLogger()->info(fpsInfo);
            n_FrameCounter = 0;
          
        }
        
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
        case SDL_KEYDOWN:
            p_GameScene->EventKeyPressed(event.key.keysym.sym);
            LoggerManager::GetInstance().GetLogger()->debug("Key {}",SDL_GetKeyName(event.key.keysym.sym));
            break;
        case SDL_KEYUP:
            p_GameScene->EventKeyReleased(event.key.keysym.sym);
            LoggerManager::GetInstance().GetLogger()->debug("Key {}",SDL_GetKeyName(event.key.keysym.sym));
            break;
        case SDL_MOUSEBUTTONDOWN:
            p_GameScene->EventMouseButtonDown(event.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            p_GameScene->EventMouseButtonUp(event.button.button);
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

