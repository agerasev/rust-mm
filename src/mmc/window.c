#include "window.h"

#include "error.h"

m_Window *m_window_create(u32 w, u32 h) {
	m_Window *win = malloc(sizeof(m_Window));

	win->window = SDL_CreateWindow(
		"SDL2",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		w, h, 
		0 // SDL_WINDOW_RESIZABLE
		);
	if(win->window == NULL) {
		m_set_error(SDL_GetError());
		goto window_fault;
	}

	win->renderer = SDL_CreateRenderer(
		win->window, 
		-1, 
		0 // SDL_RENDERER_ACCELERATED // | SDL_RENDERER_PRESENTVSYNC
		);
	if(win->renderer == NULL) {
		m_set_error(SDL_GetError());
		goto renderer_fault;
	}

	win->texture = SDL_CreateTexture(
		win->renderer, 
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 
		w, h
		);
	if(win->texture == NULL) {
		m_set_error(SDL_GetError());
		goto texture_fault;
	}

	if(SDL_LockTexture(win->texture, NULL, &win->pixels, &win->pitch) != 0) {
		m_set_error(SDL_GetError());
		goto lock_fail;
	}

	return win;
lock_fail:
	SDL_DestroyTexture(win->texture);
texture_fault:
	SDL_DestroyRenderer(win->renderer);
renderer_fault:
	SDL_DestroyWindow(win->window);
window_fault:
	free(win);

	return NULL;
}

void m_window_destroy(m_Window *win) {
	SDL_DestroyTexture(win->texture);
	SDL_DestroyRenderer(win->renderer);
	SDL_DestroyWindow(win->window);
}

void m_window_get_size(const m_Window *win, u32 *w, u32 *h) {
	SDL_GetWindowSize(win->window, w, h);
}

u32 m_window_update(m_Window *win) {
	SDL_UnlockTexture(win->texture);
	if(SDL_RenderClear(win->renderer) != 0) {
		m_set_error(SDL_GetError());
		return 1;
	}
	if(SDL_RenderCopy(win->renderer, win->texture, NULL, NULL) != 0) {
		m_set_error(SDL_GetError());
		return 2;
	}
	SDL_RenderPresent(win->renderer);
	if(SDL_LockTexture(win->texture, NULL, &win->pixels, &win->pitch) != 0) {
		m_set_error(SDL_GetError());
		return 3;
	}
	return 0;
}

void m_window_set_pixel(m_Window *win, u32 x, u32 y, u32 color) {
	*(u32*)((u8*)win->pixels + win->pitch*y + 4*x) = color;
}

u32 m_window_get_pixel(const m_Window *win, u32 x, u32 y) {
	return *(u32*)((u8*)win->pixels + win->pitch*y + 4*x);
}