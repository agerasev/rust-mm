#include <stdlib.h>

#include <SDL2/SDL.h>

SDL_Window *window = NULL;

void mmc_init() {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow( "SDL2",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, 0
	);
}

void mmc_quit() {
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

void mmc_sleep(uint32_t ms) {
	SDL_Delay(ms);
}

uint32_t mmc_handle() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			return 1;
		}
		else
		if(event.type == SDL_KEYDOWN) {
			if(event.key.keysym.sym == SDLK_ESCAPE) {
				return 2;
			}
		}
	}
	return 0;
}
