#pragma once
// Width of the window.
#define WIDTH 1280
// Height of the window.
#define HEIGHT 720

// Mathematic's pi, defined using the first 20 digits.
#define PI 3.14159265358979323846

// Enum used to identify the working axis.
const enum Axis { X, Y, Z, NONE }

// Enum used to identify the current transformation in use.
const enum Transformation { TRANSLATION, ROTATION, SCALE, NONE };