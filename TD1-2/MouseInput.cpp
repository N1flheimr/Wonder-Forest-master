#include "MouseInput.h"
#include "DxLib.h"

bool mouseClick[2] = { false ,false };
bool oldMouseClick[2] = { false ,false };
int mouseX, mouseY;

void MouseInput() {
	for (int i = 0; i < 2; i++) {
		oldMouseClick[i] = mouseClick[i];

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != false) {
			mouseClick[LEFT] = true;
		}
		else {
			mouseClick[LEFT] = false;
		}

		if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != false) {
			mouseClick[RIGHT] = true;
		}
		else {
			mouseClick[RIGHT] = false;
		}
	}
	GetMousePoint(&mouseX, &mouseY);
}
