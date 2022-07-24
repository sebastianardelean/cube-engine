#pragma once



class Text {
public:
    Text();
    ~Text();
    Text(const Text &) = delete;
    Text(Text &&) = delete;
    Text &operator=(const Text &) = delete;
    Text &operator=(Text &&) = delete;

    class Font
    {
    public:
        Font(const std::string &filePath, int ptSize, int fontStyle,int hinting=TTF_HINTING_NORMAL, int fontOutline = 0);
        ~Font();
        Font(const Font &) = delete;
        Font(Font &&) = delete;
        Font &operator=(const Font &) = delete;
        Font &operator=(Font &&) = delete;
        [[no_discard]] TTF_Font * GetRawFont() {return p_SdlFont.get();}
    private:
        std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> p_SdlFont;
        int n_FontStyle;
    };
    enum class ETextRenderMethod: std::uint8_t {
        TextRenderSolid,
        TextRenderShaded,
        TextRenderBlended
    };
    enum class ETextRenderType: std::uint8_t {
        TextRender_LATIN1,
        TextRender_UTF8,
        TextRender_UNICODE
    };
    void SetRenderMethod (const ETextRenderMethod& renderMethod);
    void SetRenderType(const ETextRenderType& renderType);
    void SetText(int x, int y, int w, int h,const std::string &text, Text::Font& font,const cube::CubeColor& fg, const cube::CubeColor& bg);

private:

    class SdlTTFGlobalInitializer
    {
    public:
        SdlTTFGlobalInitializer();
        ~SdlTTFGlobalInitializer();
        SdlTTFGlobalInitializer(const SdlTTFGlobalInitializer &) = delete;
        SdlTTFGlobalInitializer(SdlTTFGlobalInitializer &&) = delete;
        SdlTTFGlobalInitializer &operator=(const SdlTTFGlobalInitializer &) = delete;
        SdlTTFGlobalInitializer &operator=(SdlTTFGlobalInitializer &&) = delete;
    };
    std::unique_ptr<SdlTTFGlobalInitializer> p_SdlTTFGlobalInit;
    ETextRenderMethod n_RenderMethod;
    ETextRenderType n_RenderType;

};

