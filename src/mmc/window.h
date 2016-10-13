#pragma once

#include <SDL2/SDL.h>

#include "types.h"


typedef struct m_Window {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture * texture;
	void *pixels;
	u32 pitch;
} m_Window;

m_Window *m_window_create(u32 w, u32 h);
void m_window_destroy(m_Window *win);
void m_window_get_size(const m_Window *win, u32 *w, u32 *h);
u32 m_window_update(m_Window *win);
void m_window_set_pixel(m_Window *win, u32 x, u32 y, u32 color);
u32 m_window_get_pixel(const m_Window *win, u32 x, u32 y);
