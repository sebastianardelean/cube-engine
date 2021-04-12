#pragma once

class WindowManager
{
    public:
	WindowManager();
	~WindowManager();
	void Init(std::string title,
		  int32_t width,
		  int32_t height,
		  int32_t posX=SDL_WINDOWPOS_CENTERED,
		  int32_t posY=SDL_WINDOWPOS_CENTERED,
		  bool fullscreen=false
		  );

    protected:
    private:
	SDL_Window *pWindow = nullptr;

};
