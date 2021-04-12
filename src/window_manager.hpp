#pragma once

class WindowManager
{
    public:
	WindowManager();
	~WindowManager();
	void Init(std::string title,
		  int32_t width,
		  int32_t height,
		  int32_t posX,
		  int32_t posY,
		  bool fullscreen
		  );

    protected:
    private:
	SDL_Window *pWindow = nullptr;

};
