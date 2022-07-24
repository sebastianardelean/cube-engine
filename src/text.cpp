#include "utils/utils.hpp"
#include "utils/cube_exceptions.hpp"
#include "utils/logger_manager.hpp"
#include "cube.hpp"
#include "text.hpp"


Text::Text()
{
    p_SdlTTFGlobalInit = std::make_unique<SdlTTFGlobalInitializer>();
    n_RenderMethod = ETextRenderMethod::TextRenderSolid;
    n_RenderType = ETextRenderType::TextRender_UTF8;
}

Text::~Text()
{

}

void Text::SetRenderMethod(const Text::ETextRenderMethod &renderMethod) {
    n_RenderMethod=renderMethod;
}




void Text::SetText(int x, int y, int w, int h,const std::string &text, Text::Font &font, const cube::CubeColor &fg,
                         const cube::CubeColor &bg) {

    auto configureCaptionSurface=[&] (Text::Font &font, const std::string &message) {
        switch(n_RenderMethod) {
            case ETextRenderMethod::TextRenderSolid:
                return std::unique_ptr<SDL_Surface,decltype(&SDL_FreeSurface)>(
                        TTF_RenderText_Solid(font.GetRawFont(),text.c_str(), fg),
                        &SDL_FreeSurface);
            case ETextRenderMethod::TextRenderShaded:
                return std::unique_ptr<SDL_Surface,decltype(&SDL_FreeSurface)>(
                        TTF_RenderText_Shaded(font.GetRawFont(), text.c_str(), fg, bg),
                        &SDL_FreeSurface);
            case ETextRenderMethod::TextRenderBlended:
                return std::unique_ptr<SDL_Surface,decltype(&SDL_FreeSurface)>(
                        TTF_RenderText_Blended(font.GetRawFont(), text.c_str(), fg),
                        &SDL_FreeSurface);
        }
    };
    using ptr_func_non_shaded = std::function<SDL_Surface*(TTF_Font *,const char *text, SDL_Color fg)>;
    using ptr_func_shaded = std::function<SDL_Surface*(TTF_Font *,const char *text, SDL_Color fg,SDL_Color bg)>;

    auto configureMessageRenderMethod = [&](Text::Font &font,
                                            const std::string &message,
                                            bool isShaded,
                                            ptr_func_non_shaded nonShaded,
                                            ptr_func_shaded shaded) {
        if (isShaded) {
            return std::unique_ptr<SDL_Surface,decltype(&SDL_FreeSurface)>(
                    shaded(font.GetRawFont(), text.c_str(), fg, bg),
                    &SDL_FreeSurface);
        } else {
            return std::unique_ptr<SDL_Surface,decltype(&SDL_FreeSurface)>(
                    nonShaded(font.GetRawFont(),text.c_str(), fg),
                    &SDL_FreeSurface);
        }

    };

    auto configureMessageSurface=[&] (Text::Font &font, const std::string &message) {
        switch (n_RenderType) {
            case ETextRenderType::TextRender_LATIN1:
                switch(n_RenderMethod) {
                    case ETextRenderMethod::TextRenderSolid:
                        return configureMessageRenderMethod(font,message,false, &TTF_RenderText_Solid, nullptr);
                    case ETextRenderMethod::TextRenderShaded:
                        return configureMessageRenderMethod(font,message,true, nullptr, &TTF_RenderText_Shaded);
                    case ETextRenderMethod::TextRenderBlended:
                        return configureMessageRenderMethod(font,message,false, &TTF_RenderText_Blended, nullptr);
                }

            case ETextRenderType::TextRender_UTF8:
                switch(n_RenderMethod) {
                    case ETextRenderMethod::TextRenderSolid:
                        return configureMessageRenderMethod(font,message,false, &TTF_RenderUTF8_Solid, nullptr);
                    case ETextRenderMethod::TextRenderShaded:
                        return configureMessageRenderMethod(font,message,true, nullptr, &TTF_RenderUTF8_Shaded);
                    case ETextRenderMethod::TextRenderBlended:
                        return configureMessageRenderMethod(font,message,false, &TTF_RenderUTF8_Blended, nullptr);
                }
//            TODO: TBD
//            case ETextRenderType::TextRender_UNICODE:
//                switch(n_RenderMethod) {
//                    case ETextRenderMethod::TextRenderSolid:
//                        return configureMessageRenderMethod(font,message,false, &TTF_RenderUNICODE_Solid, nullptr);
//                    case ETextRenderMethod::TextRenderShaded:
//                        return configureMessageRenderMethod(font,message,true, nullptr, &TTF_RenderUNICODE_Shaded);
//                    case ETextRenderMethod::TextRenderBlended:
//                        return configureMessageRenderMethod(font,message,false, &TTF_RenderUNICODE_Blended, nullptr);
//                }

        }

    };

    std::unique_ptr<SDL_Surface,decltype(&SDL_FreeSurface)> captionSdlSurface=configureCaptionSurface(font,text);
    std::unique_ptr<SDL_Surface,decltype(&SDL_FreeSurface)> messageSdlSurface=configureMessageSurface(font,text);
    SDL_Rect captionRectangle;
    SDL_Rect messageRectangle;
    captionRectangle.x = x;
    captionRectangle.y = y;
    captionRectangle.w = captionSdlSurface->w;
    captionRectangle.h = captionSdlSurface->h;

    messageRectangle.x = x;
    messageRectangle.y = y;
    messageRectangle.w = messageSdlSurface->w;
    messageRectangle.h = messageSdlSurface->h;


}

void Text::SetRenderType(const ETextRenderType& renderType) {
    n_RenderType=renderType;
}

Text::SdlTTFGlobalInitializer::SdlTTFGlobalInitializer()
{
    try {
        utils::sdl_ttf_safe_init();
    } catch (const cubeexcept::SdlInitTTFException &e) {
        LoggerManager::GetInstance().GetLogger()->error(e.what());
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
Text::Font::Font(const std::string &filePath, int ptSize, int fontStyle,int hinting, int fontOutline) try:
        p_SdlFont(utils::sdl_ttf_safe_open_font(filePath, ptSize), &TTF_CloseFont),
        n_FontStyle(fontStyle)
{
    TTF_SetFontStyle(p_SdlFont.get(), fontStyle);
    TTF_SetFontOutline(p_SdlFont.get(), fontOutline);
    TTF_SetFontKerning(p_SdlFont.get(), 1);
    TTF_SetFontHinting(p_SdlFont.get(), hinting);

}
catch (const cubeexcept::SdlTTFOpenFontException &e) {
    LoggerManager::GetInstance().GetLogger()->error(e.what());
}

Text::Font::~Font() {

}
