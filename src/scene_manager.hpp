#pragma once
#include "sprite.hpp"
class SceneManager
{
    public:
	SceneManager() {
	}
	virtual ~SceneManager() {
	}

	SceneManager(const SceneManager &)=delete;
	SceneManager(SceneManager &&)=delete;
	SceneManager &operator=(const SceneManager &)=delete;
	SceneManager &operator=(SceneManager &&)=delete;
	[[nodiscard]] Sprite GetDrawTarget() const {
	    return drawTarget;
	}

	void Draw(int32_t x, int32_t y, uint8_t r,uint8_t g,uint8_t b,uint8_t a) {
	    
	    Pixel p(Color(r,g,b,a),x,y);
	    drawTarget.SetPixel(p);
	}

    protected:
	virtual void DrawScene() {}

	virtual void HandleKeyEvents() {}
	virtual void HandleMouseEvents() {}
    private:
	Sprite drawTarget;
};
