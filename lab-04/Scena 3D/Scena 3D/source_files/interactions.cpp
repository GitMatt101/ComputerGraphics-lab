#include "../lib.h"
#include "../header_files/interactions.h"
#include "../header_files/shape.h"
#include "../header_files/view.h"

extern vector<Shape*> scene;
extern View camera;
extern Perspective cameraPerspective;
extern mat4 projectionMatrix;
extern mat4 view;
extern Transformation currentTransformation;
extern Axis currentAxis;

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

/*
* Modifies the model matrix of a shape to apply a transformation.
* 
* @param translationVector - The vector that defines a movement.
* @param rotationVector - The vector that defines the axis around which the shape will rotate.
* @param rotationAngle - The angle of rotation.
* @param scaleValue - The value used to scale the shape.
*/
void modifyModelMatrix(Shape* shape, vec3 translationVector, vec3 rotationVector, GLfloat rotationAngle, GLfloat scaleValue);

/*
* Modifies the shape by applying the currently selected transformation on the currently selected axis.
* 
* @param shape - The shape to apply the transformation on.
* @param transformationValue - The value of the transformation.
*/
void applyTransformation(Shape* shape, float transformationValue);

void keyboardEvent(unsigned char key, int x, int y) {
	Shape* selectedShape = NULL;
	for (Shape* shape : scene)
		if (shape->isSelected()) selectedShape = shape;
	if (selectedShape == NULL) return;

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
			currentAxis = X;
			break;
		case 'y':	// Y axis
			currentAxis = Y;
			break;
		case 'z':	// Z axis
			currentAxis = Z;
			break;
		case 'T':	// Translation
			currentTransformation = TRANSLATION;
			break;
		case 'R':	// Rotation
			currentTransformation = ROTATION;
			break;
		case 'S':	// Scale
			currentTransformation = SCALE;
			break;
		case '+':	// Increase
			applyTransformation(selectedShape, 0.05f);
			break;
		case '-':	// Decrease
			applyTransformation(selectedShape, -0.05f);
			break;
		default:
			break;
	}
}

void zoom(int button, int direction, int x, int y) {
	if (direction > 0) cameraPerspective.fov -= 2.0f;
	else cameraPerspective.fov += 2.0f;

	// Limits the perspective if it goes too far or too close
	if (cameraPerspective.fov < 1.0f) cameraPerspective.fov = 1.0f;
	if (cameraPerspective.fov > 180.0f) cameraPerspective.fov = 180.0f;

	glutPostRedisplay();
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

void modifyModelMatrix(Shape* shape, vec3 translationVector, vec3 rotationVector, GLfloat rotationAngle, GLfloat scaleValue) {
	mat4 traslationMatrix = translate(mat4(1), translationVector);
	mat4 scaleMatrix = scale(mat4(1), vec3(scaleValue, scaleValue, scaleValue));
	mat4 rotationMatrix = rotate(mat4(1), rotationAngle, rotationVector);

	*shape->getModel() = *shape->getModel() * scaleMatrix * rotationMatrix * traslationMatrix;

	glutPostRedisplay();
}

void applyTransformation(Shape* shape, float transformationValue) {
	vec3 axis;
	switch (currentAxis) {
		case X:
			axis = vec3(1.0f, 0.0f, 0.0f);
			break;
		case Y:
			axis = vec3(0.0f, 1.0f, 0.0f);
			break;
		case Z:
			axis = vec3(0.0f, 0.0f, 1.0f);
			break;
		default:
			return;
	}
	
	switch (currentTransformation) {
		case TRANSLATION:
			modifyModelMatrix(shape, axis * transformationValue, axis, 0.0f, 1.0f);
			break;
		case ROTATION:
			modifyModelMatrix(shape, vec3(0.0f), axis, transformationValue, 1.0f);
			break;
		case SCALE:
			modifyModelMatrix(shape, vec3(0.0f), axis, 0.0f, 1.0f + transformationValue);
			break;
		default:
			return;
	}

	glutPostRedisplay();
}