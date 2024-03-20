#pragma once
#include "../lib.h"

/*
* Handles all keyboard events.
* 
* @param key - The pressed key.
* @param x - The x value of the cursor when the key is pressed.
* @param y - The y value of the cursor when the key is pressed.
*/
void keyboardEvent(unsigned char key, int x, int y);

/*
* Handles zoom when the mouse wheel is used.
*
* @param wheel - The wheel number.
* @param direction - The direction of the scrolling (+1 means forward, -1 means backward)
* @param x - The x value of the cursor when the wheel is used.
* @param y - The y value of the cursor when the wheel is used.
*/
void zoom(int wheel, int direction, int x, int y);

/*
* Handles mouse clicks to select shapes on the screen.
* 
* @param button - The pressed button (left click, right click, mouse wheel click).
* @param x - The x value of the cursor when the button is pressed.
* @param y - The y value of the cursor when the button is pressed.
*/
void select(int button, int state, int x, int y);