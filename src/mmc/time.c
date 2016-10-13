#include "time.h"

#include <SDL2/SDL.h>

void m_sleep(u32 ms) {
	SDL_Delay(ms);
}

u32 m_get_ticks() {
	return SDL_GetTicks();
}
