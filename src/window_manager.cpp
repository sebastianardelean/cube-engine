#include "window_manager.hpp"


WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{
    if (pWindow != nullptr) {
	SDL_DestroyWindow(pWindow);
    }
}


void WindowManager::Init(std::string title,
	    int32_t width,
	    int32_t height,
	    int32_t posX,
	    int32_t posY,
	    bool fullscreen)
{
    uint32_t flags = 0ul;
    if (fullscreen) {
	flags |= SDL_WINDOW_FULLSCREEN;

    }

    if (SDL_Init(SDL_INIT_EVERYTHING) !=0 ) {
	//TODO:Error message SDLInit
    }
    else {
	pWindow = SDL_CreateWindow(
		title.c_str(),
		posX,
		posY,
		width,
		height,
		flags
		);
	if (pWindow == nullptr) {
	    //TODO: Error message
	}
    }
}

