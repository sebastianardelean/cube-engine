#pragma once
#include "window_manager.hpp"
#include "error_manager.hpp"
namespace cube {

    struct GameConfig;
    template<typename Config>class Engine;

}; // namespace cube



template <typename Config>
class cube::Engine
{
    public:
	Engine()
	{
	    pErrorManager = std::make_unique<ErrorManager>();
	}
	void Run()
	{
	    spdlog::info("run");
	}
    protected:
    private:
	Config config;
	std::unique_ptr<ErrorManager> pErrorManager;
	std::unique_ptr<WindowManager> pWindowManager;
};


#include "game_config.hpp"
