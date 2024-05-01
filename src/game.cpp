#include "../include/game.hpp"
#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <cstddef>
#include <vector>

void drawCircles(const std::vector<Circle>& circles, int segments) {
  for (const auto& circle : circles) {
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(circle.x, circle.y); // Centro do círculo
    
    for (int i = 0; i <= segments; i++) {
      float angle = 2.0f * M_PI * float(i) / float(segments);
      float dx = circle.radius * cosf(angle);
      float dy = circle.radius * sinf(angle);
      glVertex2f(circle.x + dx, circle.y + dy);
    }

    glEnd();
  }
}

void uptadeCirclePos(Circle &circle) {
  circle.x += circle.velocityX;
  circle.y += circle.velocityY;
}
