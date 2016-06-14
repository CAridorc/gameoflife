#ifndef _graphics_h_included_
#define _graphics_h_included_

#include <SDL2/SDL.h>

#include "input.h"
#include "logic.h"

class Graphics {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	Graphics();
	Graphics(const Graphics&) = delete;
	~Graphics();

	void render(const Gamestate&, const InputHandler&) const;
};

#endif
