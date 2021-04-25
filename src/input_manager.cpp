#include "input_manager.hpp"

void InputManager::HandleEvent()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
	case SDL_QUIT:
	    spdlog::info("Quit");
	    break;
	case SDL_KEYDOWN:
	    spdlog::info("Keydown");
	    break;
	case SDL_KEYUP:
	    spdlog::info("KeyUP");
	    break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
	    spdlog::info("MOUSE");
	    break;
	case SDL_MOUSEWHEEL:
	    spdlog::info("Mouse Wheel");
	    break;
    }
}

void InputManager::GetMessage()
{
}
