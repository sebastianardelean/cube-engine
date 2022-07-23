#pragma once
class RenderManager {
public:
    RenderManager(SDL_Window *window);
    ~RenderManager()=default;
    RenderManager(const RenderManager &) = delete;
    RenderManager(RenderManager &&) = delete;
    RenderManager &operator=(const RenderManager &) = delete;
    RenderManager &operator=(RenderManager &&) = delete;

    void PrepareScene();
    void Render(const std::uint32_t *gamePixels, const std::uint32_t pitch);
protected:
private:
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> p_Renderer;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>p_Texture;

};