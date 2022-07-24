#include "../utils/utils.hpp"
#include "../utils/cube_exceptions.hpp"
#include "../utils/logger_manager.hpp"
#include "../game_config.hpp"
#include "game_scene.hpp"
#include "../text.hpp"

cube::GameScene::GameScene(const cube::GameConfig &gameConfig) try:
    p_Surface(utils::sdl_safe_create_surface(gameConfig.width,gameConfig.height), &SDL_FreeSurface)
{

}
catch (const cubeexcept::SdlSurfaceCreateException &e) {
    LoggerManager::GetInstance().GetLogger()->error(e.what());
}
cube::GameScene::~GameScene() {}

void cube::GameScene::UpdateScene() {
    p_Renderer->PrepareScene();
    DrawScene();

    p_Renderer->Render();
}

void cube::GameScene::EventKeyPressed(SDL_Keycode key) {
    OnKeyPressed(key);
}

//void cube::GameScene::GetPixelsAndPitch(std::uint32_t *pixels, std::int32_t *pitch) {
//
//    std::int64_t surfaceSize = p_Surface->w*p_Surface->h;
//    SDL_LockSurface(p_Surface.get());
//
//    std::memcpy(pixels,p_Surface->pixels,surfaceSize);
//    *pitch = p_Surface->pitch;
//    SDL_UnlockSurface(p_Surface.get());
//
//}

void cube::GameScene::WriteText(int x, int y, const std::string &text,const cube::CubeColor &color)
{
    Text textWriter;
    textWriter.SetRenderMethod(Text::ETextRenderMethod::TextRenderSolid);
    textWriter.SetRenderType(Text::ETextRenderType::TextRender_UTF8);
    Text::Font font("/usr/share/fonts/TTF/DejaVuSans.ttf",1,TTF_STYLE_BOLD,TTF_HINTING_NORMAL,0);

    textWriter.SetText(25,25,150,150,text,font,color,color);
}

void cube::GameScene::SetRenderer(RenderManager* renderer) {
    p_Renderer.reset(renderer);
}

void cube::GameScene::DrawLine(int x1, int y1, int x2, int y2,const cube::CubeColor &color) {
    p_Renderer->RenderLine(x1,y1,x2,y2,color);
}
