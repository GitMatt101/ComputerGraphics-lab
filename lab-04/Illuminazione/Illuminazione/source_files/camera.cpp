#include "../lib.h"
#include "../header_files/camera.h"
#include "../header_files/view.h"

extern View camera;

/*
* Calculates the moving direction of the camera.
* 
* @return The direction of the camera.
*/
vec4 getDirection();

void moveCameraForward() {
	vec4 direction = getDirection();
	camera.position += direction * CAMERA_SPEED;
}

void moveCameraBackward() {
	vec4 direction = getDirection();
	camera.position -= direction * CAMERA_SPEED;
}

void moveCameraRight() {
	vec4 direction = getDirection();
	vec3 slideVector = cross(vec3(direction), vec3(camera.upVector)) * CAMERA_SPEED;
	camera.position += vec4(slideVector, 0.0f);
	camera.target += vec4(slideVector, 0.0f);
}

void moveCameraLeft() {
	vec4 direction = getDirection();
	vec3 slideVector = cross(vec3(direction), vec3(camera.upVector)) * CAMERA_SPEED;
	camera.position -= vec4(slideVector, 0.0f);
	camera.target -= vec4(slideVector, 0.0f);
}

void moveCameraUpward() {
	camera.position += camera.upVector * CAMERA_SPEED;
}

void moveCameraDownward() {
	camera.position -= camera.upVector * CAMERA_SPEED;
}

vec4 getDirection() {
	return camera.target - camera.position;
}