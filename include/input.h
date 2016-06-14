#ifndef _input_h_included_
#define _input_h_included_

#include <SDL2/SDL.h>

#include "logic.h"

const int WINDOW_SIZE_X = 800;
const int WINDOW_SIZE_Y = 800;

const double CAMERA_PAN_SPEED = 50.0;
const double CAMERA_ZOOM_SPEED = 1.05;

class InputHandler {
private:
	const unsigned char* keyboard_state;
	unsigned int mouse_state;
	int mouse_pos_x;
	int mouse_pos_y;

	void get_input_poll(Gamestate&);
	void get_input_camera();
	void get_input_mouse(Gamestate&);

public:
	InputHandler();
	InputHandler(const InputHandler&) = delete;

	bool quit;
	double camera_x;
	double camera_y;
	double zoom;
	Cell highlighted_cell;

	void get_input(Gamestate&);
};

#endif
