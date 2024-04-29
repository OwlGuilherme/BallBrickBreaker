#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>

int main() {

  if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
    std::cerr << "Erro ao inicilizar o SDL: " << SDL_GetError() << '\n';
    return -1;
  }

  SDL_Window* window = SDL_CreateWindow("BallBrickBreacker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cerr << "Erro ao criar a janela: " << SDL_GetError() << '\n';
    SDL_Quit();
    return -1;
  }

  // Cria render
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    std::cerr << "Erro ao criar o renderer: " << SDL_GetError() << '\n';
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  // Define cor do retângulo (vermelho)
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  // Define coordenadas e dimensões do retângulo
  SDL_Rect rect;
  rect.x = 400 - 25;
  rect.y = 100;
  rect.w = 50;
  rect.h = 400;

  SDL_RenderClear(renderer);

  SDL_RenderFillRect(renderer, &rect);

  SDL_RenderPresent(renderer);

  bool quit = false;
  SDL_Event event;
  while (!quit) {
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;

}



