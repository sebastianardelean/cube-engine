#pragma once
#include "canvas.hpp"
class SceneManager {
public:
  SceneManager() {}
  virtual ~SceneManager() {}

  void Init(int32_t windowWidth, int32_t windowHeight) {
    nWindowWidth = windowWidth;
    nWindowHeight = windowHeight;
    drawTarget = Canvas(windowWidth, windowHeight);
  }
  SceneManager(const SceneManager &) = delete;
  SceneManager(SceneManager &&) = delete;
  SceneManager &operator=(const SceneManager &) = delete;
  SceneManager &operator=(SceneManager &&) = delete;
  [[nodiscard]] Canvas GetDrawTarget() const { return drawTarget; }

  void Draw(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    Color c(r, g, b, a);
    Pixel p(c, x, y);
    drawTarget.SetPixel(p);
  }
  void DrawBackground(Color p = WHITE) {
    for (int x = 0; x < nWindowWidth; x++) {
      for (int y = 0; y < nWindowHeight; y++) {
        Draw(x, y, p.red, p.green, p.blue, p.alpha);
      }
    }
  }
  [[nodiscard]] int32_t GetWindowWidth() const { return nWindowWidth; }

  [[nodiscard]] int32_t GetWindowHeight() const { return nWindowHeight; }

  void UpdateScene() { DrawScene(); }

protected:
  virtual void DrawScene() {}

  virtual void HandleKeyEvents() {}
  virtual void HandleMouseEvents() {}

private:
  Canvas drawTarget;
  int32_t nWindowWidth;
  int32_t nWindowHeight;
};
