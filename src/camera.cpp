// author: prisha sujin kumar
// desc: class to handle camera

// third party libraries
#include <SDL.h> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/constants.hpp>       

// our libraries
#include "Camera.hpp"

Camera::Camera(glm::vec3 position) : Position(position), Front(0.0f, 0.0f, -1.0f) {
	Position = glm::vec3(0.0f, 0.0f, 5.0f);
	Zoom = 40.0f;
	Yaw = -90.0f;
	Pitch = 0.0f;
	
	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const {
    	return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const {
    	return glm::perspective(glm::radians(Zoom), aspectRatio, 0.1f, 100.0f);
}

void Camera::ProcessKeyboard(const Uint8* pressState, float deltaTime) {
    	float velocity = MovementSpeed * deltaTime;

	if (pressState[SDL_SCANCODE_W]) {
		Position += Front * velocity;
	} else if (pressState[SDL_SCANCODE_S]) {
		Position -= Front * velocity;
	} else if (pressState[SDL_SCANCODE_A]) {
		Position -= Right * velocity;
	} else if (pressState[SDL_SCANCODE_D]) {
		Position += Right * velocity;
	} else if (pressState[SDL_SCANCODE_SPACE]) {
		Position += Up * velocity;
	} else if (pressState[SDL_SCANCODE_LCTRL]) {
		Position -= Up * velocity;
	}
}

void Camera::ProcessKeyboardRotation(float xOffset, float yOffset, float deltaTime) {

	xOffset *= RotationSpeed * deltaTime;
	yOffset *= RotationSpeed * deltaTime;

	Yaw += xOffset;
	Pitch += yOffset;

	if (Pitch) {
		if (Pitch > 89.0f) {
			Pitch = 89.0f;
		} if (Pitch < -89.0f) {
			Pitch = -89.0f;
		}
	}

	if (Yaw) {
		if (Yaw > 180.0f) {
			Yaw -= 360.0f;
		} if (Yaw < -180.0f) {
			Yaw += 360.0f;
		}
	}

	updateCameraVectors();
}

void Camera::Reset() {
	Position = glm::vec3(0.0f, 0.0f, 5.0f);
	Zoom = 45.0f;
	Yaw = -90.0f;
	Pitch = 0.0f;
	updateCameraVectors();
}

void Camera::updateCameraVectors() {
	glm::vec3 front;
    	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    	front.y = sin(glm::radians(Pitch));
    	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    	Front = glm::normalize(front);
    	Right = glm::normalize(glm::cross(Front, WorldUp));
    	Up = glm::normalize(glm::cross(Right, Front));
}
