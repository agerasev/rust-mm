#include "error.h"

#include <string.h>

#include <SDL2/SDL.h>

static char m_error[M_ERROR_SIZE + 1] = "\0";

const char *m_get_error() {
	return m_error;
}

void m_set_error(const char *msg) {
	strncpy(m_error, msg, M_ERROR_SIZE);
}