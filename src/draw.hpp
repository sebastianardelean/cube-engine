#pragma once
#include "pixel.hpp"
#include "vector2d.hpp"
#include "scene_manager.hpp"
namespace draw {

void DrawLine(SceneManager &obj,int32_t x1, int32_t y1, int32_t x2, int32_t y2, Color p = WHITE,
              Uint32 pattern = 0xFFFFFFFF) {
  auto rol = [&](void) {
    pattern = (pattern << 1) | (pattern >> 31);
    return pattern & 1;
  };

  int32_t dx, dy, dx1, dy1, px, py, xe, ye, i;
  dx = x2 - x1;
  dy = y2 - y1;
  dx1 = abs(dx);
  dy1 = abs(dy);
  int32_t x, y;
  // straight vertical line
  if (dx == 0) {
    if (y2 < y1) {
      std::swap(y1, y2);
    }
    for (y = y1; y <= y2; y++) {
      if (rol())
        obj.Draw(x1, y, p.red, p.green, p.blue, p.alpha);
    }
    return;
  }

  // straight horizontal line
  if (dy == 0) {
    if (x2 < x1) {
      std::swap(x1, x2);
    }
    for (x = x1; x <= x2; x++) {
      if (rol())
        obj.Draw(x, y1, p.red, p.green, p.blue, p.alpha);
    }
    return;
  }

  px = 2 * dy1 - dx1;
  py = 2 * dx1 - dy1;

  if (dy1 <= dx1) {
    if (dx >= 0) {
      x = x1;
      y = y1;
      xe = x2;
    } else {
      x = x2;
      y = y2;
      xe = x1;
    }

    if (rol())
      obj.Draw(x, y, p.red, p.green, p.blue, p.alpha);

    for (i = 0; x < xe; i++) {
      x = x + 1;
      if (px < 0)
        px = px + 2 * dy1;
      else {
        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
          y = y + 1;
        else
          y = y - 1;
        px = px + 2 * (dy1 - dx1);
      }
      if (rol())
        obj.Draw(x, y, p.red, p.green, p.blue, p.alpha);
    }
  } else {
    if (dy >= 0) {
      x = x1;
      y = y1;
      ye = y2;
    } else {
      x = x2;
      y = y2;
      ye = y1;
    }

    if (rol())
      obj.Draw(x, y, p.red, p.green, p.blue, p.alpha);

    for (i = 0; y < ye; i++) {
      y = y + 1;
      if (py <= 0)
        py = py + 2 * dx1;
      else {
        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
          x = x + 1;
        else
          x = x - 1;
        py = py + 2 * (dx1 - dy1);
      }
      if (rol())
        obj.Draw(x, y, p.red, p.green, p.blue, p.alpha);
    }
  }
}

void DrawLine(SceneManager &obj,const vector::vector2Di_t &pos1, const vector::vector2Di_t &pos2,
              Color p = WHITE, Uint32 pattern = 0xFFFFFFFF) {
  DrawLine(obj,pos1.X(), pos1.Y(), pos2.X(), pos2.Y(), p, pattern);
}
// Draws a circle located at (x,y) with radius
void DrawCircle(SceneManager &obj,int32_t x, int32_t y, int32_t radius, Color p = WHITE,
                uint8_t mask = 0xFF) {
  if (radius < 0 || x < -radius || y < -radius || x - obj.GetWindowWidth() > radius ||
      y - obj.GetWindowHeight() > radius)
    return;
  if (radius > 0) {
    int32_t x0 = 0;
    int32_t y0 = radius;
    int32_t d = 3 - 2 * radius;

    while (y0 >= x0) // only formulate 1/8 of circle
    {
      // Draw even octants
      if (mask & 0x01)
        obj.Draw(x + x0, y - y0, p.red, p.green, p.blue,
             p.alpha); // Q6 - upper right right
      if (mask & 0x04)
        obj.Draw(x + y0, y + x0, p.red, p.green, p.blue,
             p.alpha); // Q4 - lower lower right
      if (mask & 0x10)
        obj.Draw(x - x0, y + y0, p.red, p.green, p.blue,
             p.alpha); // Q2 - lower left left
      if (mask & 0x40)
        obj.Draw(x - y0, y - x0, p.red, p.green, p.blue,
             p.alpha); // Q0 - upper upper left
      if (x0 != 0 && x0 != y0) {
        if (mask & 0x02)
          obj.Draw(x + y0, y - x0, p.red, p.green, p.blue,
               p.alpha); // Q7 - upper upper right
        if (mask & 0x08)
          obj.Draw(x + x0, y + y0, p.red, p.green, p.blue,
               p.alpha); // Q5 - lower right right
        if (mask & 0x20)
          obj.Draw(x - y0, y + x0, p.red, p.green, p.blue,
               p.alpha); // Q3 - lower lower left
        if (mask & 0x80)
          obj.Draw(x - x0, y - y0, p.red, p.green, p.blue,
               p.alpha); // Q1 - upper left left
      }

      if (d < 0)
        d += 4 * x0++ + 6;
      else
        d += 4 * (x0++ - y0--) + 10;
    }
  } else {
    obj.Draw(x, y, p.red, p.green, p.blue, p.alpha);
  }
}

void DrawCircle(SceneManager &obj,const vector::vector2Di_t &pos, int32_t radius, Color p = WHITE,
                uint8_t mask = 0xFF) {
  DrawCircle(obj,pos.X(), pos.Y(), radius, p, mask);
}

// Fills a circle located at (x,y) with radius
void FillCircle(SceneManager &obj,int32_t x, int32_t y, int32_t radius, Color p = WHITE) {
  if (radius < 0 || x < -radius || y < -radius || x - obj.GetWindowWidth() > radius ||
      y - obj.GetWindowHeight() > radius)
    return;

  if (radius > 0) {
    int32_t x0 = 0;
    int32_t y0 = radius;
    int32_t d = 3 - 2 * radius;

    auto drawline = [&](int sx, int ex, int y) {
      for (int x = sx; x <= ex; x++)
        obj.Draw(x, y, p.red, p.green, p.blue, p.alpha);
    };

    while (y0 >= x0) {
      drawline(x - y0, x + y0, y - x0);
      if (x0 > 0)
        drawline(x - y0, x + y0, y + x0);

      if (d < 0)
        d += 4 * x0++ + 6;
      else {
        if (x0 != y0) {
          drawline(x - x0, x + x0, y - y0);
          drawline(x - x0, x + x0, y + y0);
        }
        d += 4 * (x0++ - y0--) + 10;
      }
    }
  } else {
    obj.Draw(x, y, p.red, p.green, p.blue, p.alpha);
  }
}

void FillCircle(SceneManager &obj,const vector::vector2Di_t &pos, int32_t radius,
                Color p = WHITE) {
  FillCircle(obj,pos.X(), pos.Y(), radius, p);
}

// Draws a rectangle at (x,y) to (x+w,y+h)
void DrawRect(SceneManager &obj,int32_t x, int32_t y, int32_t w, int32_t h, Color p = WHITE) {
  DrawLine(obj,x, y, x + w, y, p);
  DrawLine(obj,x + w, y, x + w, y + h, p);
  DrawLine(obj,x + w, y + h, x, y + h, p);
  DrawLine(obj,x, y + h, x, y, p);
}

void DrawRect(SceneManager &obj,const vector::vector2Di_t &pos, const vector::vector2Di_t &size,
              Color p = WHITE) {
  DrawRect(obj,pos.X(), pos.Y(), size.X(), size.Y(), p);
}

// Fills a rectangle at (x,y) to (x+w,y+h)
void FillRect(SceneManager &obj,int32_t x, int32_t y, int32_t w, int32_t h, Color p = WHITE) {
    int32_t x2 = x + w;
    int32_t y2 = y + h;

    if (x < 0) x = 0;
    if (x >= (int32_t)obj.GetWindowWidth()) 
	x = (int32_t)obj.GetWindowWidth();
    if (y < 0) y = 0;
    if (y >= (int32_t)obj.GetWindowHeight()) 
	y = (int32_t)obj.GetWindowHeight();

    if (x2 < 0) x2 = 0;
    if (x2 >= (int32_t)obj.GetWindowWidth()) 
	x2 = (int32_t)obj.GetWindowWidth();
    if (y2 < 0) y2 = 0;
    if (y2 >= (int32_t)obj.GetWindowHeight()) 
	y2 = (int32_t)obj.GetWindowHeight();

    for (int i = x; i < x2; i++)
	for (int j = y; j < y2; j++)
	    obj.Draw(i, j, p.red,p.green,p.blue,p.alpha);

}

void FillRect(SceneManager &obj,const vector::vector2Di_t &pos, const vector::vector2Di_t &size,
              Color p = WHITE) {
  FillRect(obj,pos.X(), pos.Y(), size.X(), size.Y(), p);
}

#if 0
// Draws an entire sprite at well location (x,y)
void DrawSprite(int32_t x, int32_t y, Sprite *sprite, Uint32 scale = 1,
                uint8_t flip = 0u) {
  if (sprite == nullptr)
    return;

  int32_t fxs = 0, fxm = 1, fx = 0;
  int32_t fys = 0, fym = 1, fy = 0;
  if (flip & Sprite::Flip::FLIP_HORIZONTAL) {
    fxs = sprite->GetSpriteWidth() - 1;
    fxm = -1;
  }
  if (flip & Sprite::Flip::FLIP_VERTICAL) {
    fys = sprite->GetSpriteHeight() - 1;
    fym = -1;
  }

  if (scale > 1) {
    fx = fxs;
    for (int32_t i = 0; i < sprite->GetSpriteWidth(); i++, fx += fxm) {
      fy = fys;
      for (int32_t j = 0; j < sprite->GetSpriteHeight(); j++, fy += fym)
        for (Uint32 is = 0; is < scale; is++)
          for (Uint32 js = 0; js < scale; js++) {
            Pixel p = sprite->GetPixel(fx, fy);
            Draw(x + (i * scale) + is, y + (j * scale) + js, p.value.red,
                 p.value.green, p.value.blue, p.value.alpha);
          }
    }
  } else {
    fx = fxs;
    for (int32_t i = 0; i < sprite->GetSpriteWidth(); i++, fx += fxm) {
      fy = fys;
      for (int32_t j = 0; j < sprite->GetSpriteHeight(); j++, fy += fym) {
        Pixel p = sprite->GetPixel(fx, fy);
        Draw(x + i, y + j, p.value.red, p.value.green, p.value.blue,
             p.value.alpha);
      }
    }
  }
}

void DrawSprite(const vector::vector2Di_t &pos, Sprite *sprite,
                Uint32 scale = 1, uint8_t flip = 0u) {
  DrawSprite(pos.X(), pos.Y(), sprite, scale, flip);
}
#endif
}; // namespace draw
