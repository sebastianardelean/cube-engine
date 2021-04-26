#include "engine.hpp"
#include "scene_manager.hpp"
class GameLogic: public SceneManager{
    protected:
	void DrawScene() {
	    for (size_t x=0;x<800;x++) {
		for (size_t y=0;y<600;y++) {
		    Draw(x,y,rand()%256, rand()%256,rand()%256,255);
		}
	    }
	}
};

int main(int argc,char **argv)
{

    std::unique_ptr<GameLogic>game = std::make_unique<GameLogic>();
//    std::move(uniqueptr);
    spdlog::info("Hello World");

    cube::Engine<cube::GameConfig> engine;
    engine.Init(std::move(game));
    engine.Run();

    return 0;
}
