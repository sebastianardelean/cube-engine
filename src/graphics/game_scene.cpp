#include "../utils/utils.hpp"
#include "../utils/cube_exceptions.hpp"
#include "../utils/logger_manager.hpp"
#include "../game_config.hpp"
#include "game_scene.hpp"

cube::GameScene::GameScene(const cube::GameConfig &gameConfig) try:
    p_Surface(utils::sdl_safe_create_surface(gameConfig.width,gameConfig.height), &SDL_FreeSurface)
{

}
catch (const cubeexcept::SdlSurfaceCreateException &e) {
    LoggerManager::GetInstance().GetLogger()->error(e.what());
}
cube::GameScene::~GameScene() {}

void cube::GameScene::UpdateScene() {
    DrawScene();
}

void cube::GameScene::GetPixelsAndPitch(std::uint32_t *pixels, std::int32_t *pitch) {

    std::int64_t surfaceSize = p_Surface->w*p_Surface->h;
    SDL_LockSurface(p_Surface.get());

    std::memcpy(pixels,p_Surface->pixels,surfaceSize);
    *pitch = p_Surface->pitch;
    SDL_UnlockSurface(p_Surface.get());

}