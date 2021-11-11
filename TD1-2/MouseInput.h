#pragma once
extern bool mouseClick[2];
extern bool oldMouseClick[2];
extern int mouseX, mouseY;

enum RightLeft {
	LEFT = 0, RIGHT = 1
};

extern void MouseInput();