#pragma once
#include "sprite.hpp"
class RenderManager
{
    public:
	RenderManager(const int32_t windowWidth, const int32_t windowHeight):nWindowWidth(windowWidth),nWindowHeight(windowHeight)
	{
	}
	~RenderManager()
	{
	    if (pRenderer != nullptr) {
	       SDL_DestroyRenderer(pRenderer);
	    }
	    if (pTexture != nullptr) {
	       SDL_DestroyTexture(pTexture);
	    }
	}
	RenderManager(const RenderManager &)=delete;
	RenderManager(RenderManager &&)=delete;
	RenderManager &operator=(const RenderManager &)=delete;
	RenderManager &operator=(RenderManager &&)=delete;

	void Init(SDL_Window &window, std::string preferredRenderer);
	void Prepare(const Sprite s);
	void Render();
    protected:
    private:
	SDL_Renderer *pRenderer = nullptr;
	SDL_Texture *pTexture = nullptr;
	SDL_Surface *pSdlSurface = nullptr;
	int32_t nWindowWidth;
	int32_t nWindowHeight;
	Sprite sprite;
};
