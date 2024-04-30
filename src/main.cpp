#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
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
                                      600, 400,
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

  glClearColor(0, 0, 0, 0);

  // Área exibida
  glViewport(0, 0, 600, 400);
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);

  auto running = true;
  SDL_Event event;
  while (running)
  {
    while (SDL_PollEvent(&event) != 0)
    {
      if (event.type == SDL_QUIT)
      {
        running = false;
      }
    }
    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer
    SDL_GL_SwapWindow(window); // Troca os buffers para exibir a janela
  }

  // Lógica


  // Renderização


  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

