#pragma once
#include "pixel.hpp"

class Canvas {
public:
  Canvas() : nCanvasWidth(0), nCanvasHeight(0) {}
  ~Canvas() {}
  Canvas(std::string imagePath) {}
  Canvas(int32_t width, int32_t height)
      : nCanvasWidth(width), nCanvasHeight(height) {
    vSurface.reserve(nCanvasWidth * nCanvasHeight);
  }

  [[nodiscard]] int32_t GetCanvasWidth() const { return nCanvasWidth; }

  [[nodiscard]] int32_t GetCanvasHeight() const { return nCanvasHeight; }

  void SetPixel(const Pixel p) {
    if (vSurface.size() < (nCanvasWidth * nCanvasHeight)) {
      vSurface.emplace_back(p);
    }
  }

  [[nodiscard]] std::vector<Pixel> GetSurface() const { return vSurface; }

private:
  std::vector<Pixel> vSurface;
  int32_t nCanvasWidth;
  int32_t nCanvasHeight;
};
