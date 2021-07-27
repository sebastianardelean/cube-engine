#include "engine.hpp"
#include "scene_manager.hpp"
#include "draw.hpp"
class GameLogic : public SceneManager {
protected:
  void DrawScene() {
      draw::DrawLine(*this,0, 0, 800, 600, GREEN, 0xAA55AA55);
      draw::DrawLine(*this,0, 0, 800, 600, GREEN, 0xAA55AA55);
      draw::DrawLine(*this,0, 300, 800, 300, RED, 0xAA55AA55);
      draw::DrawLine(*this,400, 0, 400, 600, BLUE, 0xAA55AA55);
      draw::DrawCircle(*this,150,150,10,MAGENTA);
      draw::FillCircle(*this,400,400,120,MAGENTA);
  }
};

int main(int argc, char **argv) {

  std::unique_ptr<GameLogic> game = std::make_unique<GameLogic>();
  spdlog::info("Hello World");

  cube::Engine<cube::GameConfig> engine;
  engine.Init(std::move(game));
  engine.Run();
  engine.Stop();
  return 0;
}
