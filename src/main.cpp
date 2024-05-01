#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_opengl.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_math.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>
#include <box2d/box2d.h>
#include <box2d/b2_settings.h>
#include <iostream>
#include <vector>
#include "../include/game.hpp"

const float32 kPixelPerMeter = 30.0f;

int main()
{
  // Verificação de erros
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
      std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << '\n';
      return -1;
  }
  
  // Define o tamanho de x e de y em variáveis
  auto x_size = 500;
  auto y_size = 600;

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_Window* window = SDL_CreateWindow("BallBrickBreaker",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      x_size, y_size,
                                      SDL_WINDOW_OPENGL);

  if (window == nullptr)
  {
      std::cerr << "Erro ao criar janela: " << SDL_GetError() << '\n';
      SDL_Quit();
      return -1;
  }

  SDL_GLContext context = SDL_GL_CreateContext(window);
  if (context == nullptr)
  {
      std::cerr << "Erro ao criar contexto OpenGL: " << SDL_GetError() << '\n';
      SDL_DestroyWindow(window);
      SDL_Quit();
      return -1;
  }

  b2Vec2 gravity(0.0f, 9.8f);
  b2World world(gravity);

  glClearColor(1, 1, 1, 1);

  // Área exibida
  glViewport(0, 0, x_size, y_size);
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);

  auto running = true;
  SDL_Event event;

  Person person;
  person.width = 50;
  person.height = 30;
  person.x = 300;
  person.y = y_size - person.height;


  b2BodyDef personBodyDef;
  personBodyDef.type = b2_staticBody;
  personBodyDef.position.Set(300 / kPixelPerMeter, 500 / kPixelPerMeter); // Posição inicial do retângulo
  b2Body* personBody = world.CreateBody(&personBodyDef);

  b2PolygonShape personShape;
  personShape.SetAsBox(50 / kPixelPerMeter, 30 / kPixelPerMeter);

  b2FixtureDef personFixtureDef;
  personFixtureDef.shape = &personShape;
  personFixtureDef.friction = 0.3f;
  personBody->CreateFixture(&personFixtureDef);

  b2BodyDef ballBodyDef;
  ballBodyDef.type = b2_dynamicBody;
  ballBodyDef.position.Set(300 / kPixelPerMeter, 200 / kPixelPerMeter);
  b2Body* ballBody = world.CreateBody(&ballBodyDef);

  b2CircleShape ballShape;
  ballShape.m_radius = 10 / kPixelPerMeter;

  b2FixtureDef ballFixtureDef;
  ballFixtureDef.shape = &ballShape;
  ballFixtureDef.density = 1.0f; // Densidade da bola
  ballFixtureDef.friction = 0.3f; // Coeficiente de atrito
  ballFixtureDef.restitution = 0.8f; // Coeficiente de restituição (elasticidade)
  ballBody->CreateFixture(&ballFixtureDef);

  auto esq = false;
  auto dir = false;

  while (running)
  {
    while (SDL_PollEvent(&event) != 0)
    {
      if (event.type == SDL_QUIT)
      {
        running = false;
      }
      // Verificação de teclas esquerda e direita pressionada
      if (event.type == SDL_KEYDOWN)
      {
        if (event.key.keysym.sym == SDLK_LEFT)
        {
          esq = true;
        }
        else if (event.key.keysym.sym == SDLK_RIGHT)
        {
          dir = true;
        }
      }
      else if (event.type == SDL_KEYUP)
      {
        if (event.key.keysym.sym == SDLK_LEFT)
        {
          esq = false;
        }
        else if (event.key.keysym.sym == SDLK_RIGHT)
        {
          dir = false;
        }
      }
    }   
    
    /*
    // Movimentação do usuário
    auto vel = 8;
    if (esq == true)
    {
      if (person.x >= 0)
      {
        person.x -= vel;
      }      
    }
    if (dir == true)
    {
      if (person.x + person.width <= x_size)
      {
        person.x += vel;
      }
    }
    */
    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer

    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterarions = 6;
    int32 positionIterations = 2;
    world.Step(timeStep, velocityIterarions, positionIterations);

    glPushMatrix(); // Inicialização da matriz

    glOrtho(0, x_size, y_size, 0, -1, 1); // Dimensões da matriz
    glColor4ub(255, 0, 0, 255);
    
    // Movimentação do retângulo do usuário
    auto vel = 8;
    b2Vec2 velDir(0, 0); // Vetor de velocidade inicialmente nulo

    if (esq == true)
    {
        velDir.x = -vel; // Define a velocidade para a esquerda
    }
    if (dir == true)
    {
        velDir.x = vel; // Define a velocidade para a direita
    }
    
    // Aplica a velocidade ao corpo do retângulo do usuário
    personBody->SetLinearVelocity(velDir);

    // Limita a posição do retângulo do usuário para que ele não saia da tela
    b2Vec2 position = personBody->GetPosition();
    float halfWidth = person.width / 2.0f;
    float halfHeight = person.height / 2.0f;

    // Verifica as bordas da tela e ajusta a posição se necessário
    if (position.x - halfWidth < 0) // Verifica a borda esquerda
    {
        position.x = halfWidth;
        personBody->SetTransform(position, personBody->GetAngle());
    }
    else if (position.x + halfWidth > x_size / kPixelsPerMeter) // Verifica a borda direita
    {
        position.x = x_size / kPixelsPerMeter - halfWidth;
        personBody->SetTransform(position, personBody->GetAngle());
    }

    // Definições do quadrado inferior
    /*
    glBegin(GL_QUADS);
    glVertex2f(person.x, person.y);
    glVertex2f(person.x + person.width, person.y);
    glColor4ub(200, 125, 55, 230);
    glVertex2f(person.x + person.width, person.y + person.height);
    glVertex2f(person.x, person.y + person.height);
    glEnd();
    */
    /*
    // Desenha círculo na tela
    std::vector<Circle> circles;

    Circle circle1;
    circle1.x = 300;
    circle1.y = 200;
    circle1.radius = 10;
    circles.push_back(circle1);

    drawCircles(circles, 10);
    */


    glPopMatrix(); // Encerramento da matrix

    SDL_GL_SwapWindow(window); // Troca os buffers para exibir a janela
  }

  // Renderização
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

