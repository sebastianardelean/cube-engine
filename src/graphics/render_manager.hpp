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
    void Render();

    void RenderLine(int x1,int x2, int y1, int y2, SDL_Color color);
    void RenderText(SDL_Surface *surface);
protected:
private:
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> p_Renderer;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> p_Texture;

    int n_WindowWidth;
    int n_WindowHeight;


};