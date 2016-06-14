#include "input.h"

#include <cmath>

InputHandler::InputHandler() :
	quit(false),
	camera_x(0),
	camera_y(0),
	zoom(60) {
	keyboard_state = SDL_GetKeyboardState(NULL);
	mouse_state = SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);
}

void InputHandler::get_input(Gamestate& gamestate) {
	get_input_poll(gamestate);
	get_input_camera();
	get_input_mouse(gamestate);
}

void InputHandler::get_input_poll(Gamestate& gamestate) {
	SDL_Event event;
	while(SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			quit = true;
			return;
		}
		if (event.type == SDL_KEYDOWN and event.key.keysym.sym == SDLK_SPACE) {
			gamestate.paused = not gamestate.paused;
		}
	}
}

void InputHandler::get_input_camera() {
	if (keyboard_state[SDL_SCANCODE_W]) {
		camera_y -= CAMERA_PAN_SPEED;
	}
	if (keyboard_state[SDL_SCANCODE_A]) {
		camera_x -= CAMERA_PAN_SPEED;
	}
	if (keyboard_state[SDL_SCANCODE_S]) {
		camera_y += CAMERA_PAN_SPEED;
	}
	if (keyboard_state[SDL_SCANCODE_D]) {
		camera_x += CAMERA_PAN_SPEED;
	}
	if (keyboard_state[SDL_SCANCODE_Q]) {
		zoom *= CAMERA_ZOOM_SPEED;
	}
	if (keyboard_state[SDL_SCANCODE_E]) {
		zoom /= CAMERA_ZOOM_SPEED;
	}
}

void InputHandler::get_input_mouse(Gamestate& gamestate) {
	mouse_state = SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);
	highlighted_cell = {(int)floor((mouse_pos_x + camera_x) / zoom),
	                    (int)floor((mouse_pos_y + camera_y) / zoom)};
	if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		gamestate.board.insert(highlighted_cell);
	}
	if (mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		gamestate.board.erase(highlighted_cell);
	}
}
