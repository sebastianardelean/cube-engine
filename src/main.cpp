#include "cube.hpp"
#include "graphics/engine.hpp"
#include "game_config.hpp"
#include "graphics/game_scene.hpp"


class Game: public cube::GameScene {
public:
    Game(const cube::GameConfig &gameConfig):GameScene(gameConfig) {
        //initialize viewports
    }

protected:
    void DrawScene() {
        cube::color_t textColor {0xFF, 0xA5, 0x00, 0xFF};
        DrawLine(100,100,250,250, textColor);
        WriteText(150,150,"Ana are mere", textColor);
        DrawLine(250,250,470,500, textColor);

    }

    void OnKeyPressed(SDL_Keycode key) {
        cube::color_t newColor{rand() % 255, rand() % 255, rand() % 255, 0xFF};
        DrawLine(rand()%800,rand()%600,rand()%800,rand()%600, newColor);
    }
};

int main(int argc, char **argv)
{
    cube::GameConfig gameConfig;
    std::unique_ptr<Game> game=std::make_unique<Game>(gameConfig);

    spdlog::info("Hello World");
    cube::Engine engine(gameConfig);
    engine.Run(game.release());
    return 0;
}