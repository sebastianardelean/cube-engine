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

    }
};

int main(int argc, char **argv)
{
    cube::GameConfig gameConfig;
    Game game(gameConfig);

    spdlog::info("Hello World");
    cube::Engine engine(gameConfig);
    engine.Run(game);
    return 0;
}