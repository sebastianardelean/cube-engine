#include "event_handler.hpp"

EventHandler::EventHandler(std::function<void(SDL_Event&)> callback):fCallback(callback) {

}

EventHandler::~EventHandler() {

}

void EventHandler::PollEvent() {
    SDL_Event Event;
    while(SDL_PollEvent(&Event)) {
        fCallback(Event);
    }
}