#pragma once
#include "canvas.hpp"
class RenderManager
{
    public:
	RenderManager(const int32_t windowWidth, const int32_t windowHeight):nWindowWidth(windowWidth),nWindowHeight(windowHeight)
	{
	}
	~RenderManager()
	{
	    if(pSdlSurface != nullptr) {
		SDL_FreeSurface(pSdlSurface);
	    }
	
	    if (pTexture != nullptr) {
	       SDL_DestroyTexture(pTexture);
	    }
	    if (pRenderer != nullptr) {
	       SDL_DestroyRenderer(pRenderer);
	    }
	}
	RenderManager(const RenderManager &)=delete;
	RenderManager(RenderManager &&)=delete;
	RenderManager &operator=(const RenderManager &)=delete;
	RenderManager &operator=(RenderManager &&)=delete;

	void Init(SDL_Window &window, std::string preferredRenderer);
	void Prepare(const Canvas c);
	void Render();
    protected:
    private:
	SDL_Renderer *pRenderer = nullptr;
	SDL_Texture *pTexture = nullptr;
	SDL_Surface *pSdlSurface = nullptr;
	int32_t nWindowWidth;
	int32_t nWindowHeight;
	Canvas canvas;
};
