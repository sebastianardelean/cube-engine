#pragma once

enum InputManagerEvent: uint8_t
{
    Event_Quit=0,
    Event_KeyDown,
    Event_KeyUp,
    Event_MouseMotion,
    Event_MouseButtonDown,
    Event_MouseButtonUp,
    Event_MouseWheel

};

struct EventMessage {
    EventMessage(const InputManagerEvent event):eventType(event)
    {
    }

    [[nodiscard]]InputManagerEvent GetEventType() const {
	return eventType;
    }
    protected:
        InputManagerEvent eventType;
};

struct QuitEventMessage: public EventMessage {
    QuitEventMessage():EventMessage(Event_Quit){
    }
};

struct KeyDownEventMessage: public EventMessage {
    KeyDownEventMessage(const int8_t readKey):EventMessage(Event_KeyDown) {
	key = readKey;
    }
    
    int8_t key;
};

struct KeyUpEventMessage: public EventMessage {
    KeyUpEventMessage(const int8_t readKey):EventMessage(Event_KeyUp) {
	key = readKey;
    }
    
    int8_t key;
};

struct MouseMotionEventMessage: public EventMessage {
    MouseMotionEventMessage(int32_t dx,int32_t dy):EventMessage(Event_MouseMotion){
	x=dx;
	y=dy;
    }
    int32_t x;
    int32_t y;
};

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
	    switch(event.type) {
		case SDL_QUIT: {
		    spdlog::info("Quit");
		    QuitEventMessage msg;
		    fCallback(msg);
		    break;
		}
		case SDL_KEYDOWN:
		    spdlog::info("Keydown");
		    break;
		case SDL_KEYUP:
		    spdlog::info("KeyUP");
		    break;
		case SDL_MOUSEMOTION:
		    break;
		case SDL_MOUSEBUTTONDOWN:
		    break;
		case SDL_MOUSEBUTTONUP:
		    spdlog::info("MOUSE");
		    break;
		case SDL_MOUSEWHEEL:
		    spdlog::info("Mouse Wheel");
		    break;
	    }
//	    fCallback();
	}
    protected:
    private:
	std::function<void(EventMessage)>fCallback;
	
};


