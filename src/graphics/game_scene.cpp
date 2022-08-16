#include "../utils/utils.hpp"
#include "../utils/cube_exceptions.hpp"
#include "../utils/logger_manager.hpp"
#include "../game_config.hpp"
#include "game_scene.hpp"
#include "text.hpp"
#include "sprite.hpp"

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


    p_Renderer->Render();
    DrawScene();
}

void cube::GameScene::EventKeyPressed(SDL_Keycode key) {
    OnKeyPressed(key);
}

void cube::GameScene::EventKeyReleased(SDL_Keycode key) {
    OnKeyReleased(key);
}

void cube::GameScene::EventMouseButtonDown(std::uint8_t mouseButton)
{
    OnMouseButtonDown(mouseButton);
}
void cube::GameScene::EventMouseButtonUp(std::uint8_t mouseButton)
{
    OnMouseButtonUp(mouseButton);
}



void cube::GameScene::WriteText(int x, int y, const std::string &text,const cube::color_t &color)
{
    Text textWriter;
    textWriter.SetRenderMethod(Text::ETextRenderMethod::TextRenderSolid);

    Text::Font font("/usr/share/fonts/TTF/DejaVuSans.ttf",25,TTF_STYLE_BOLD,TTF_HINTING_NORMAL);

    SDL_Surface  *surface = textWriter.SetText(text,font,color,color);
    p_Renderer->RenderSurface(surface,x,y);
    SDL_FreeSurface(surface);
}

void cube::GameScene::SetRenderer(RenderManager* renderer) {
    p_Renderer.reset(renderer);
}

void cube::GameScene::DrawLine(int x1, int y1, int x2, int y2,const cube::color_t &color) {

    p_Renderer->RenderLine(x1,y1,x2,y2,color);
}

void cube::GameScene::DrawSprite(int x, int y, const std::string path) {
    Sprite sprite(path);
    p_Renderer->RenderSurface(sprite.GetSurface(), x, y);
}

void cube::GameScene::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const cube::color_t &color) {
    DrawLine(x1,y1,x2,y2,color);
    DrawLine(x2,y2,x3,y3,color);
    DrawLine(x3,y3,x1,y1,color);
}

void cube::GameScene::DrawPolygon(std::vector<cube::vector2di> coordinates, const cube::color_t &color) {
    std::for_each(coordinates.begin(), coordinates.end(), [](const cube::vector2di &el){

    });
}

void cube::GameScene::DrawPixel(const pixel &p)
{
    p_Renderer->RenderPixel(p.x, p.y,p.color);

}

void cube::GameScene::DrawPixel(const std::vector<pixel> &pixels)
{
    std::for_each(std::begin(pixels), std::end(pixels), [&](pixel const &p){
        p_Renderer->RenderPixel(p.x, p.y,p.color);
    });
}