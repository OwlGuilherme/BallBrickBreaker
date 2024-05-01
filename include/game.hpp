#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

struct Person {
  int x;
  int y;
  int width;
  int height;
};

struct Circle {
  float x;
  float y;
  float radius;
};

void drawCircles (const std::vector<Circle>& circles, int segments);

#endif
