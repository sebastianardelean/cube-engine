#include "../utils/utils.hpp"
#include "../utils/cube_exceptions.hpp"
#include "../utils/logger_manager.hpp"
#include "../cube.hpp"
#include "sprite.hpp"


Sprite::Sprite(const std::string &path) try:
    p_SdlSurface(utils::sdl_safe_load_bmp(path), &SDL_FreeSurface)
{

}
catch (const cubeexcept::SdlLoadBmpException &e)
{
    LoggerManager::GetInstance().GetLogger()->error(e.what());
}

Sprite::~Sprite()
{

}

