#include "render_manager.hpp"

void RenderManager::Init(SDL_Window &window, std::string preferredRenderer)
{

    int rendererIndex = -1;
    for (int i=0;i<SDL_GetNumRenderDrivers(); ++i) {
	SDL_RendererInfo rendererInfo = {};
	SDL_GetRenderDriverInfo (i, &rendererInfo);
	if (rendererInfo.name != preferredRenderer) {
	    continue;
	}
	else {
	    rendererIndex = i;
	    break;
	}
    }
    pRenderer = SDL_CreateRenderer(&window, rendererIndex,SDL_RENDERER_ACCELERATED);
    if (pRenderer != nullptr) {
	pTexture = SDL_CreateTexture(pRenderer,
		SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_TARGET,
		nWindowWidth,
		nWindowHeight);
    }
    pSdlSurface = SDL_CreateRGBSurface(0,nWindowWidth,nWindowHeight,32,0,0,0,0);
}

void RenderManager::Prepare(Canvas c)
{
    canvas = c;
}

void RenderManager::Render()
{
    std::vector<Pixel> surface;

    SDL_RenderClear(pRenderer);

    surface = canvas.GetSurface();

    /*Map to SDL surface*/
    for (auto p:surface) {
	if (p.posX >= 0 && p.posX < nWindowWidth && 
		p.posY >= 0 && p.posY < nWindowHeight) {
	    uint32_t *pixels = (uint32_t *)pSdlSurface->pixels;
	    pixels[(p.posY*pSdlSurface->w)+p.posX] = p.color.GetColor();
	}
    }

    SDL_UpdateTexture(pTexture, NULL,pSdlSurface->pixels,pSdlSurface->pitch);
    
    SDL_RenderCopy(pRenderer,pTexture,NULL,NULL);
    SDL_RenderPresent(pRenderer);


}


