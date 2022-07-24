#include "../utils/utils.hpp"
#include "../utils/cube_exceptions.hpp"
#include "../utils/logger_manager.hpp"
#include "../cube.hpp"
#include "text.hpp"


Text::Text()
{
    p_SdlTTFGlobalInit = std::make_unique<SdlTTFGlobalInitializer>();
    n_RenderMethod = ETextRenderMethod::TextRenderSolid;

}

Text::~Text()
{

}

void Text::SetRenderMethod(const Text::ETextRenderMethod &renderMethod) {
    n_RenderMethod=renderMethod;
}




SDL_Surface* Text::SetText(int x, int y, const std::string &text, Text::Font &font, const cube::color_t &fg,
                         const cube::color_t &bg) {


    auto generateSdlSurfaceFromText=[&] (Text::Font &font, const std::string &message) {
            switch (n_RenderMethod) {
                case ETextRenderMethod::TextRenderSolid:
                    return TTF_RenderText_Solid(font.GetRawFont(), message.c_str(),fg);
                case ETextRenderMethod::TextRenderShaded:
                    return TTF_RenderText_Shaded(font.GetRawFont(), message.c_str(),fg,bg);
                case ETextRenderMethod::TextRenderBlended:
                    return TTF_RenderText_Blended(font.GetRawFont(), message.c_str(),fg);
            }
    };


    SDL_Surface* messageSdlSurface=generateSdlSurfaceFromText(font,text);

    return messageSdlSurface;

}


Text::SdlTTFGlobalInitializer::SdlTTFGlobalInitializer()
{
    try {
        utils::sdl_ttf_safe_init();
    } catch (const cubeexcept::SdlInitTTFException &e) {
        LoggerManager::GetInstance().GetLogger()->error(e.what());
        LoggerManager::GetInstance().GetLogger()->flush();
    }

}


Text::SdlTTFGlobalInitializer::~SdlTTFGlobalInitializer()
{
    TTF_Quit();
}
/* Font Style
 * TTF_STYLE_NORMAL (is zero)
 * TTF_STYLE_BOLD
 * TTF_STYLE_ITALIC
 * TTF_STYLE_UNDERLINE
 * TTF_STYLE_STRIKETHROUGH
 *
 * Font Hinting
 * TTF_HINTING_NORMAL
 * TTF_HINTING_LIGHT
 * TTF_HINTING_MONO
 * TTF_HINTING_NONE
 * TTF_HINTING_LIGHT_SUBPIXEL
 * */
Text::Font::Font(const std::string &filePath, int ptSize, int fontStyle,int hinting) try:
        p_SdlFont(utils::sdl_ttf_safe_open_font(filePath, ptSize), &TTF_CloseFont),
        n_FontStyle(fontStyle)
{
    TTF_SetFontStyle(p_SdlFont.get(), fontStyle);
    TTF_SetFontKerning(p_SdlFont.get(), 1);
    TTF_SetFontHinting(p_SdlFont.get(), hinting);

}
catch (const cubeexcept::SdlTTFOpenFontException &e) {
    LoggerManager::GetInstance().GetLogger()->error(e.what());
    LoggerManager::GetInstance().GetLogger()->flush();
}

Text::Font::~Font() {

}
