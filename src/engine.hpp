#pragma once
#include "error_manager.hpp"
#include "input_manager.hpp"
#include "render_manager.hpp"
#include "scene_manager.hpp"
#include "window_manager.hpp"
namespace cube {

struct GameConfig;
//    struct Color;
//    struct Pixel;
//    struct Sprite;
template <typename Config> class Engine;

}; // namespace cube

template <typename Config> class cube::Engine {
public:
  Engine() {

    pErrorManager = ErrorManager::GetInstance();
    pWindowManager = std::make_unique<WindowManager>();
    pInputManager = std::make_unique<InputManager>();
    pRenderManager =
        std::make_unique<RenderManager>(config.width, config.height);
  }
  Engine(const Engine &) = delete;
  Engine(Engine &&) = delete;
  Engine &operator=(const Engine &) = delete;
  Engine &operator=(Engine &&) = delete;

  void Init(std::unique_ptr<SceneManager> scene) {
    pErrorManager.lock()->RegisterCallback(
	    std::bind(&cube::Engine<Config>::ErrorManagerHandler, this,
		std::placeholders::_1));
    pSceneManager = std::move(scene);
    pWindowManager->Init(config.title, config.width, config.height);
    pInputManager->RegisterCallback(
        std::bind(&cube::Engine<Config>::InputManagerHandler, this,
                  std::placeholders::_1));

    pRenderManager->Init(pWindowManager->GetSdlWindow(), "opengl");
    pSceneManager->Init(config.width, config.height);
    bIsRunning = true;
  }

  void Run() {
    while (bIsRunning) {
      pInputManager->PollEvent();

      pSceneManager->UpdateScene();
      pRenderManager->Prepare(pSceneManager->GetDrawTarget());
      pRenderManager->Render();
    }
  }

  void Stop() { 
      pWindowManager.reset(); 
      SDL_Quit(); 
  }

protected:
private:
  void InputManagerHandler(EventMessage e) {
    if (e.GetEventType() == Event_Quit) {
      spdlog::info("Quiting...");
      bIsRunning = false;
    }
  }

  void ErrorManagerHandler(ErrorEvent error) {
    if (error.GetErrorCode() == Event_FatalError) {
	spdlog::info("Quiting...");
	bIsRunning = false;
	Stop();
    }
  }

  Config config;
  std::weak_ptr<ErrorManager> pErrorManager;
  std::unique_ptr<WindowManager> pWindowManager;
  std::unique_ptr<InputManager> pInputManager;
  std::unique_ptr<RenderManager> pRenderManager;
  std::unique_ptr<SceneManager> pSceneManager;
  std::atomic<bool> bIsRunning{false};
};

#include "game_config.hpp"
#include "pixel.hpp"
