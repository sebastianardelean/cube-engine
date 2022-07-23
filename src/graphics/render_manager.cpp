#include "../utils/utils.hpp"
#include "../utils/cube_exceptions.hpp"
#include "../utils/logger_manager.hpp"
#include "render_manager.hpp"

RenderManager::RenderManager(SDL_Window *window) try:
    p_Renderer(utils::sdl_safe_create_renderer(window, "opengl"), &SDL_DestroyRenderer),
    p_Texture(utils::sdl_safe_create_texture(p_Renderer.get(),window), &SDL_DestroyTexture)
{

}
catch (const cubeexcept::SdlException &e)
{
    LoggerManager::GetInstance().GetLogger()->error(e.what());
}

void RenderManager::PrepareScene()
{
    SDL_RenderClear(p_Renderer.get());
}
void RenderManager::Render(const std::uint32_t *gamePixels,const std::uint32_t pitch)
{
    SDL_UpdateTexture(p_Texture.get(), NULL, gamePixels, pitch);
    SDL_RenderCopy(p_Renderer.get(), p_Texture.get(), NULL, NULL);
    SDL_RenderPresent(p_Renderer.get());
}