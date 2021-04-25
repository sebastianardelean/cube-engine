#pragma once
#include "pixel.hpp"

class Sprite
{
    public:
	Sprite():nSpriteWidth(0),nSpriteHeight(0) {
	}
	~Sprite() {
	}
	Sprite(std::string imagePath) {
	}
	Sprite(int32_t width, int32_t height):nSpriteWidth(width),nSpriteHeight(height) {
	    vSurface.reserve(nSpriteWidth * nSpriteHeight);
	}

	[[nodiscard]]int32_t GetSpriteWidth() const {
	    return nSpriteWidth;
	}

	[[nodiscard]]int32_t GetSpriteHeight() const{
	    return nSpriteHeight;
	}
	
	void SetPixel(const Pixel p) {
	    if (vSurface.size() < (nSpriteWidth * nSpriteHeight)) {
		vSurface.emplace_back(p);
	    }
	}

	[[nodiscard]]std::vector<Pixel> GetSurface() const {
	    return vSurface;
	}

    private:
	std::vector<Pixel> vSurface;
	int32_t nSpriteWidth;
	int32_t nSpriteHeight;
};
