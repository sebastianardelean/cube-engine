#pragma once
#include "input_manager_events.hpp"

class InputManager
{
    public:
	void RegisterCallback(std::function<void(EventMessage)> callback)
	{
	    fCallback = callback;
	}
	void PollEvent() 
	{
	    SDL_Event event;
	    SDL_PollEvent(&event);
	    EventMessage msg;
	    switch(event.type) {
		case SDL_QUIT:
		    msg = QuitEventMessage();
		    break;
		case SDL_KEYDOWN: 
		    msg=KeyDownEventMessage(event.key.keysym.sym);
		    break;				  
		case SDL_KEYUP:
		    msg=KeyUpEventMessage(event.key.keysym.sym);
		    break;
		case SDL_MOUSEMOTION:
		{
		    int32_t x = 0, y = 0;
		    SDL_GetMouseState(&x,&y);
		    msg = MouseMotionEventMessage(x,y);
		}
		    break;
		case SDL_MOUSEBUTTONDOWN:
		{
		    uint8_t mouseButton = MouseButton_Left;
		    int32_t x = 0, y = 0;
		    SDL_GetMouseState(&x,&y);
		    if (SDL_BUTTON(SDL_BUTTON_LEFT)) {
			
		    }
		    else if (SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			mouseButton = MouseButton_Right;
		    }
		    else if (SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
			mouseButton = MouseButton_Middle;
		    }
		    msg = MouseButtonDownEventMessage(static_cast<MouseButton>(mouseButton),x,y);
		}
		    break;
		case SDL_MOUSEBUTTONUP:    
		{
		    uint8_t mouseButton = MouseButton_Left;
		    int32_t x = 0, y = 0;
		    SDL_GetMouseState(&x,&y);
		    if (SDL_BUTTON(SDL_BUTTON_LEFT)) {
			
		    }
		    else if (SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			mouseButton = MouseButton_Right;
		    }
		    else if (SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
			mouseButton = MouseButton_Middle;
		    }
		    msg = MouseButtonUpEventMessage(static_cast<MouseButton>(mouseButton),x,y);
		}
		    break;
		case SDL_MOUSEWHEEL:
		{
		    if (event.wheel.y > 0 ) {
			msg = MouseWheelUpEventMessage(event.wheel.y);
		    }
		    else if(event.wheel.y < 0) {
			msg = MouseWheelDownEventMessage(event.wheel.y);
			//scroll down
		    } else if(event.wheel.x > 0) {
			//scroll right
			//TODO:
		    }
		    else if (event.wheel.x < 0) {
			//scroll left
			//TODO:
		    }

		}
		    break;
	    }

	    fCallback(msg);
//	    fCallback();
	}
    protected:
    private:
	std::function<void(EventMessage)>fCallback;
	
};


