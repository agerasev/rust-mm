#include <SDL2/SDL.h>

static int m_refcount = 0;

void m_init() {
	if(m_refcount == 0) {
		SDL_Init(SDL_INIT_EVERYTHING);
	}
	m_refcount += 1;
}

void m_quit() {
	if(m_refcount > 0) {
		m_refcount -= 1;
		if(m_refcount == 0) {
			SDL_Quit();
		}
	}
}
