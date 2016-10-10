#include <stdlib.h>

#include <SDL2/SDL.h>

typedef Uint8  u8;
typedef Sint8  i8;
typedef Uint16 u16;
typedef Sint16 i16;
typedef Uint32 u32;
typedef Sint32 i32;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture * texture = NULL;

u32 width = 0, height = 0;
u32 *pixels = NULL;

u32 color = 0;

u32 mmc_init(u32 w, u32 h) {
	SDL_Init(SDL_INIT_EVERYTHING);

	width = w;
	height = h;
	window = SDL_CreateWindow(
		"SDL2",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, 
		SDL_WINDOW_SHOWN // | SDL_WINDOW_RESIZABLE
		);
	if(window == NULL) {
		fprintf(stderr, "%s\n", SDL_GetError());
		goto window_fault;
	}

	renderer = SDL_CreateRenderer(
		window, 
		-1, 
		SDL_RENDERER_ACCELERATED // | SDL_RENDERER_PRESENTVSYNC
		);
	if(renderer == NULL) {
		fprintf(stderr, "%s\n", SDL_GetError());
		goto renderer_fault;
	}

	texture = SDL_CreateTexture(
		renderer, 
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 
		width, height
		);
	if(texture == NULL) {
		fprintf(stderr, "%s\n", SDL_GetError());
		goto texture_fault;
	}

	pixels = malloc(width*height*sizeof(u32));

	return 0;

texture_fault:
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
renderer_fault:
	SDL_DestroyWindow(window);
	window = NULL;
window_fault:
	SDL_Quit();
}

void mmc_quit() {
	free(pixels);
	pixels = NULL;

	SDL_DestroyTexture(texture);
	texture = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

void mmc_get_size(u32 *w, u32 *h) {
	*w = width;
	*h = height;
	// SDL_GetWindowSize(window, w, h);
}

/*
void mmc_clear() {
	SDL_RenderClear(renderer);
}

void mmc_present() {
	SDL_RenderPresent(renderer);
}
*/

void mmc_update() {
	SDL_UpdateTexture(texture, NULL, pixels, width*sizeof(u32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void mmc_set_color(u8 r, u8 g, u8 b, u8 a) {
	color = (a << 3*8) | (r << 2*8) | (g << 1*8) | (b << 0*8);
	// SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void mmc_draw_point(u32 x, u32 y) {
	pixels[width*y + x] = color;
	// SDL_RenderDrawPoint(renderer, x, y);
}

void mmc_sleep(u32 ms) {
	SDL_Delay(ms);
}

u32 mmc_handle() {
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
