#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

typedef Uint8  u8;
typedef Sint8  i8;
typedef Uint16 u16;
typedef Sint16 i16;
typedef Uint32 u32;
typedef Sint32 i32;


static i32 mm_sys_refcount = 0;

static void mm_sys_init() {
	if(mm_sys_refcount == 0) {
		SDL_Init(SDL_INIT_EVERYTHING);
	}
	mm_sys_refcount += 1;
}

static void mm_sys_quit() {
	if(mm_sys_refcount > 0) {
		mm_sys_refcount -= 1;
		if(mm_sys_refcount == 0) {
			SDL_Quit();
		}
	}
}

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture * texture = NULL;

void *pixels = NULL;
u32 pitch = 0;

#define MM_ERROR_SIZE 200

static char mm_error[MM_ERROR_SIZE + 1];

const char *mm_get_error() {
	return mm_error;
}

u32 mm_init(u32 w, u32 h) {
	if(mm_sys_refcount > 0) {
		strncpy(mm_error, "You can init system only once", MM_ERROR_SIZE);
		return 2;
	}

	mm_sys_init();

	window = SDL_CreateWindow(
		"SDL2",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		w, h, 
		0 // SDL_WINDOW_RESIZABLE
		);
	if(window == NULL) {
		strncpy(mm_error, SDL_GetError(), MM_ERROR_SIZE);
		goto window_fault;
	}

	renderer = SDL_CreateRenderer(
		window, 
		-1, 
		SDL_RENDERER_ACCELERATED // | SDL_RENDERER_PRESENTVSYNC
		);
	if(renderer == NULL) {
		strncpy(mm_error, SDL_GetError(), MM_ERROR_SIZE);
		goto renderer_fault;
	}

	texture = SDL_CreateTexture(
		renderer, 
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 
		w, h
		);
	if(texture == NULL) {
		strncpy(mm_error, SDL_GetError(), MM_ERROR_SIZE);
		goto texture_fault;
	}

	SDL_LockTexture(texture, NULL, &pixels, &pitch);

	return 0;

texture_fault:
	SDL_DestroyRenderer(renderer);
renderer_fault:
	SDL_DestroyWindow(window);
window_fault:
	mm_sys_quit();

	return 1;
}

void mm_quit() {
	if(mm_sys_refcount > 0) {
		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

	mm_sys_quit();
}

void mm_get_size(u32 *w, u32 *h) {
	SDL_GetWindowSize(window, w, h);
}

void mm_update() {
	SDL_UnlockTexture(texture);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_LockTexture(texture, NULL, &pixels, &pitch);
}

void mm_draw_pixel(u32 x, u32 y, u32 color) {
	*(u32*)((u8*)pixels + pitch*y + 4*x) = color;
}

u32 mm_handle() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			return 1;
		} else if(event.type == SDL_KEYDOWN) {
			if(event.key.keysym.sym == SDLK_ESCAPE) {
				return 2;
			}
		}
	}
	return 0;
}

void mm_sleep(u32 ms) {
	SDL_Delay(ms);
}

u32 mm_get_ticks() {
	return SDL_GetTicks();
}
