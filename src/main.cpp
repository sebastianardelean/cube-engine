#include "engine.hpp"


int main(int argc,char **argv)
{
    spdlog::info("Hello World");

    cube::Engine<cube::GameConfig> engine;
    engine.Run();

    return 0;
}
