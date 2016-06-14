#include "graphics.h"

#include <cmath>

Graphics::Graphics() {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("dungeon", 0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Graphics::~Graphics() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Graphics::render(const Gamestate& gamestate, const InputHandler& i) const {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect destination;
	// Draw board
	for (Cell c : gamestate.board) {
		destination = {(int)(c.x * i.zoom - i.camera_x), (int)(c.y * i.zoom - i.camera_y),
		               (int)ceil(i.zoom), (int)ceil(i.zoom)};
		SDL_RenderFillRect(renderer, &destination);
	}
	// Highlight cell under mouse
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
	Cell c = i.highlighted_cell;
	destination = {(int)(c.x * i.zoom - i.camera_x), (int)(c.y * i.zoom - i.camera_y),
	               (int)ceil(i.zoom), (int)ceil(i.zoom)};
	SDL_RenderFillRect(renderer, &destination);

	SDL_RenderPresent(renderer);
}
