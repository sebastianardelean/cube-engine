#pragma once


class EventHandler {
public:
    EventHandler(std::function<void(SDL_Event&)> callback);
    ~EventHandler();
    EventHandler(const EventHandler &) = delete;
    EventHandler(EventHandler &&) = delete;
    EventHandler &operator=(const EventHandler &) = delete;
    EventHandler &operator=(EventHandler &&) = delete;

    void PollEvent();
private:
    std::function<void(SDL_Event&)> fCallback;
};



