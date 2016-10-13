#include "event.h"


u32 m_is_closed() {
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