#pragma once


namespace utils {


    SDL_Window *sdl_safe_create_window(std::string title,
            int x, int y, int w, int h, std::uint32_t flags);

    SDL_Renderer *sdl_safe_create_renderer(SDL_Window *window, std::string preferredRenderer);

    SDL_Texture *sdl_safe_create_texture(SDL_Renderer *renderer, int width, int height);
    SDL_Texture *sdl_safe_create_texture(SDL_Renderer *renderer, SDL_Window *window);

    SDL_Surface *sdl_safe_create_surface(const std::int32_t surfaceWidth, const std::int32_t surfaceHeight);

    SDL_Surface *sdl_safe_load_bmp(const std::string &filePath);

    void sdl_ttf_safe_init();

    TTF_Font *sdl_ttf_safe_open_font(const std::string &filePath, int ptsize);
}
