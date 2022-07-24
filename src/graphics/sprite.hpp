#pragma once
#include "../cube.hpp"

class Sprite
{
public:
    Sprite(const std::string &path) ;
    ~Sprite();
    Sprite(const Sprite &)=default;
    Sprite(Sprite &&)=default;
    Sprite &operator=(const Sprite &)=default;
    Sprite &operator=(Sprite &&)=default;
private:
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> p_SdlSurface;
};