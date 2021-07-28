#pragma once
#include "SDL.h"
#include "pixel.hpp"
struct Sprite
{
    Sprite()
    {
    }

    bool operator==(const Sprite &s) const {
	return (spriteHeight == s.SpriteHeight &&
		spriteWidth == s.spriteWidth);
    }

    bool operator!=(const Sprite &s) const {
	return !(*this == s);
    }

    void LoadFromFile(const std::string& imagePath)
    {
	SDL_Surface *bmpSurface = SDL_LoadBMP(imagePath.c_str());
	if (bmpSurface != nullptr) {
	    uint32_t *pixels = (uint32_t *)bmpSurface->pixels;
	    spriteWidth = bmpSurface->w;
	    spriteHeight = bmpSurface->h;
	    uint32_t totalSize = spriteWidth * spriteHeight;
	    for(size_t i = 0; i < totalSize; i++) {
		surface.push_back(pixels[i]);
	    }
	}
    }

    Pixel GetPixel(int32_t posX,int32_t posY) const {
	return surface[posY*spriteWidth+posX];
    }

    void SetPixel(Pixel p) {
	surface[p.posY*spriteWidth+p.posX].color = p.color;
    }
    uint32_t spriteHeight;
    uint32_t spriteWidth;
    int32_t posX;
    int32_t posY;
    std::vector<Pixel> surface;
};
