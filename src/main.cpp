#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

int main()
{
  // Verificação de erros
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
      std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << '\n';
      return -1;
  }
  
  // Define o tamanho de x e de y em variáveis
  auto x_size = 600;
  auto y_size = 400;

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

  glClearColor(1, 1, 1, 1);

  // Área exibida
  glViewport(0, 0, x_size, y_size);
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);

  auto running = true;
  SDL_Event event;

  auto person_x = 300;
  auto person_y = 350;
  auto person_comp = 50;
  auto person_alt = 30;

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

    // Lógica
    // Movimentos
    auto vel = 8;
    if (esq == true)
    {
      if (person_x >= 0)
      {
        person_x -= vel;
      }      
    }
    if (dir == true)
    {
      if (person_x + person_comp <= x_size)
      {
        person_x += vel;
      }
    }
    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer

    glPushMatrix(); // Inicialização da matriz

    glOrtho(0, x_size, y_size, 0, -1, 1); // Domensões da matriz
    glColor4ub(255, 0, 0, 255);

    // Definições do quadrado inferior
    glBegin(GL_QUADS);
    glVertex2f(person_x, person_y);
    glVertex2f(person_x + person_comp, person_y);
    glColor4ub(200, 125, 55, 230);
    glVertex2f(person_x + person_comp, person_y + person_alt);
    glVertex2f(person_x, person_y + person_alt);
    glEnd();

    glPopMatrix(); // Encerramento da matrix

    SDL_GL_SwapWindow(window); // Troca os buffers para exibir a janela
  }

  // Renderização
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

