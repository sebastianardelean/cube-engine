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
template <typename Config> class Engine;

}; // namespace cube

template <typename Config> class cube::Engine {
public:
  Engine() {

    pErrorManager = std::make_unique<ErrorManager>();
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

  void Stop() { SDL_Quit(); }

protected:
private:
  void InputManagerHandler(EventMessage e) {
    if (e.GetEventType() == Event_Quit) {
      bIsRunning = false;
    }
  }

  Config config;
  std::unique_ptr<ErrorManager> pErrorManager;
  std::unique_ptr<WindowManager> pWindowManager;
  std::unique_ptr<InputManager> pInputManager;
  std::unique_ptr<RenderManager> pRenderManager;
  std::unique_ptr<SceneManager> pSceneManager;
  std::atomic<bool> bIsRunning{false};
};

#include "game_config.hpp"
#include "pixel.hpp"
