#include "utils.hpp"
#include "cube_exceptions.hpp"
namespace utils {

    SDL_Window *sdl_safe_create_window(std::string title,
                                int x, int y, int w, int h, std::uint32_t flags) {
        SDL_Window *hdlWindow = SDL_CreateWindow(title.c_str(), x,y,w,h,flags);
        if (hdlWindow == nullptr) {
            throw cubeexcept::SdlCreateWindowException(std::string(SDL_GetError()));
        }
        return hdlWindow;
    }

    SDL_Renderer *sdl_safe_create_renderer(SDL_Window *window, std::string preferredRenderer){
        int rendererIndex = -1;
        for (int i = 0; i < SDL_GetNumRenderDrivers(); ++i) {
            SDL_RendererInfo rendererInfo = {};
            SDL_GetRenderDriverInfo(i, &rendererInfo);
            if (rendererInfo.name != preferredRenderer) {
                continue;
            } else {
                rendererIndex = i;
                break;
            }
        }
        SDL_Renderer *hdlRenderer = SDL_CreateRenderer(window, rendererIndex, SDL_RENDERER_ACCELERATED);
        if (hdlRenderer == nullptr) {
            throw cubeexcept::SdlRendererCreateException(std::string(SDL_GetError()));
        }
        return hdlRenderer;
    }

    SDL_Texture *sdl_safe_create_texture(SDL_Renderer *renderer, SDL_Window *window) {
        std::int32_t windowWidth = 0;
        std::int32_t windowHeight = 0;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        SDL_Texture *hdlTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                                     SDL_TEXTUREACCESS_TARGET, windowWidth,
                                                    windowHeight);
        if(hdlTexture==nullptr) {
            throw cubeexcept::SdlTextureCreateException(std::string(SDL_GetError()));
        }
        return hdlTexture;
    }

    SDL_Surface *sdl_safe_create_surface(const std::int32_t surfaceWidth, const std::int32_t surfaceHeight) {

        SDL_Surface *hdlSurface = SDL_CreateRGBSurface(0, surfaceWidth,surfaceHeight, 32,0,0,0,0);
        if (hdlSurface == nullptr) {
            throw cubeexcept::SdlSurfaceCreateException(std::string(SDL_GetError()));
        }
        return hdlSurface;
    }

    SDL_Surface *sdl_safe_load_bmp(const std::string &filePath) {
        SDL_Surface *hdlSurface = SDL_LoadBMP(filePath.c_str());
        if (hdlSurface == nullptr) {
            throw cubeexcept::SdlLoadBmpException(std::string(SDL_GetError()));
        }
        return hdlSurface;
    }
}