#include "../lib.h"
#include "../header_files/interactions.h"
#include "../header_files/shape.h"
#include "../header_files/view.h"

extern vector<Shape*> scene;
extern View camera;
extern mat4 projectionMatrix;
extern mat4 view;

/*
* Calculates the ray that starts from the camera and reaches the clicked point on the screen, transforming it in world coordinates.
*
* @param x - The x value of the clicked point.
* @param y - The y value of the clicked point.
* @return The ray as a glm::vec3
*/
vec3 getRay(int x, int y);

/*
* Checks if the ray created from the mouse click intersects the sphere of a shape.
*
* @param origin - The origin of the ray (usually the camera).
* @param direction - The direction of the ray.
* @param shape - The pointer to the shape.
* @return The distance of the ray from the sphere of the shape.
*/
double getIntersectionDistance(vec3 origin, vec3 direction, Shape* shape);

void keyboardEvent(unsigned char key, int x, int y) {
	switch (key) {
		case 'w':	// Forward
			break;
		case 'a':	// Left
			break;
		case 's':	// Backward
			break;
		case 'd':	// Right
			break;
		case 'q':	// Up
			break;
		case 'e':	// Down
			break;
		case 'x':	// X axis
			break;
		case 'y':	// Y axis
			break;
		case 'z':	// Z axis
			break;
		case '+':	// Increase
			break;
		case '-':	// Decrease
			break;
	}
}

void zoom(int button, int direction, int x, int y) {
	if (direction > 0) {
		// Zoom in
	} else {
		// Zoom out
	}
}

void select(int button, int state, int x, int y) {
	if (button != GLUT_LEFT_BUTTON) return;

	vec3 ray = getRay(x, y);
	double closestIntersection = 0.0f;
	Shape* previousIntersectedShape = NULL;
	for (Shape* shape : scene) {
		double intersectionDistance = getIntersectionDistance(camera.position, ray, shape);
		if (intersectionDistance > 0.0f && intersectionDistance < closestIntersection) {
			if (previousIntersectedShape != NULL) 
				previousIntersectedShape->toggleSelection();
			shape->toggleSelection();
			previousIntersectedShape = shape;
			closestIntersection = intersectionDistance;
		}
	}
	glutPostRedisplay();
}

vec3 getRay(int x, int y) {
	// Normalized Device Coordinates
	vec4 ndc = vec4(2.0f * x / WIDTH - 1.0f, 1.0f - 2.0f * y / HEIGHT, -1.0f, 1.0f);
	// Clip coordinates
	vec4 clipCoordinates = vec4(ndc.x, ndc.y, ndc.z, 1.0f);
	// View coordinates
	vec4 viewCoordinates = inverse(projectionMatrix) * clipCoordinates;
	// ViewModelp.w = 1.0; ?
	// World coordinates
	vec4 worldCoordinates = inverse(view) * viewCoordinates;
	// Direction of the ray that starts from the camera and reaches the clicked point
	vec3 ray = normalize(vec3(worldCoordinates) - vec3(camera.position));

	return ray;
}

/*
* Checks if the ray created from the mouse click intersects the sphere of a shape.
* 
* @param origin - The origin of the ray (usually the camera).
* @param direction - The direction of the ray.
* @param shape - The pointer to the shape.
* @return The distance of the ray from the sphere of the shape.
*/
double getIntersectionDistance(vec3 origin, vec3 direction, Shape* shape) {
	vec3 sphereCenter = vec3(shape->getAnchor()->x, shape->getAnchor()->y, shape->getAnchor()->z);
	float b = dot(direction, (origin - sphereCenter));
	double q = dot((origin - sphereCenter), (origin - sphereCenter)) - pow(shape->getSphereRadius(), 2);
	double delta = pow(b, 2) - q;
	double t0 = - b - sqrt(delta);

	if (delta < 0.0f)
		return -1.0f;
	else
		return t0;
}