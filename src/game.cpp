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

void checkCollision(Circle &circle, int screenWidth, int screenHeight, Person &person){
  // Colisão com as bordas horizontais da tela
  if (circle.x - circle.radius <= 0 || circle.x + circle.radius >= screenWidth) {
    circle.velocityX = -circle.velocityX;
  }

  // Colisão vertical
  if (circle.y - circle.radius <= 0 || circle.y + circle.radius >= screenHeight) {
    circle.velocityY = -circle.velocityY;
  }

  // Colisão com o retângulo do jogador
  if (circle.y + circle.radius >= person.y && circle.x >= person.x && circle.x <= person.x + person.width) {
    circle.velocityY = -circle.velocityY;
  }  
}
