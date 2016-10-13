#include <SDL2/SDL.h>

#include "types.h"
#include "error.h"

#include <stdio.h>

static int m_refcount = 0;

u32 m_init() {
	if(m_refcount == 0) {
		fprintf(stderr, "init\n");
		fflush(stderr);
		u32 status = SDL_Init(SDL_INIT_VIDEO);
		if(status != 0) {
			m_set_error(SDL_GetError());
			return status;
		}
	}
	m_refcount += 1;
	return 0;
}

void m_quit() {
	if(m_refcount > 0) {
		m_refcount -= 1;
		if(m_refcount == 0) {
			fprintf(stderr, "quit\n");
			fflush(stderr);
			SDL_Quit();
		}
	}
}
