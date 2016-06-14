	#include <cstdio>

	#include <SDL2/SDL.h>

	#include "graphics.h"
	#include "input.h"
	#include "logic.h"

	const int TARGET_FRAMERATE = 60;
	const int TARGET_TICKRATE = 2;
	const int FRAMES_PER_TICK = TARGET_FRAMERATE / TARGET_TICKRATE;
	const int TARGET_TIMESTEP = 1000 / TARGET_FRAMERATE;

	int main() {
		Graphics graphics;
		InputHandler input_handler;
		Gamestate gamestate;

		unsigned int timestep, time0, time1 = 0;
		unsigned int frame_count = 0;
		while (!input_handler.quit) {
			// Get time
			time0 = time1;
			time1 = SDL_GetTicks();
			timestep = time1 - time0;
			frame_count++;
			// Main game loop
			if (frame_count % FRAMES_PER_TICK == 0) {
				gamestate.update();
			}
			input_handler.get_input(gamestate);
			graphics.render(gamestate, input_handler);
			// FPS cap
			if (timestep < TARGET_TIMESTEP) {
				SDL_Delay(TARGET_TIMESTEP - timestep);
				time1 += TARGET_TIMESTEP - timestep;
			}
		}
		printf("Exiting game\n");
	}
