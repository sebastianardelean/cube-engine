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
    SDL_SetRenderDrawColor(p_Renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(p_Renderer.get());
}
void RenderManager::Render()
{
 //   SDL_UpdateTexture(p_Texture.get(), NULL, gamePixels, pitch);
   // SDL_RenderCopy(p_Renderer.get(), p_Texture.get(), NULL, NULL);
    SDL_RenderPresent(p_Renderer.get());
}

void RenderManager::RenderLine(int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(p_Renderer.get(), color.r, color.g,color.b,color.a);
    SDL_RenderDrawLine(p_Renderer.get(), x1,y1,x2,y2);
}
