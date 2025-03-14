#ifndef CAMERA_HPP
#define CAMERA_HPP
// author: prisha sujin kumar
// desc: class to handle camera 

// third party libraries
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif
#include <glm/glm.hpp>

class Camera {
	public:
    		/**
 		* @brief constructs a Camera at a given position
		* @param position (default of (0.0f, 0.0f, 3.0f)) 
 		**/
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f));

		/**
 		* @brief returns view matrix
	 	* @return glm::mat4
 		**/
    		glm::mat4 GetViewMatrix() const;

		/**
 		* @brief returns projection matrix
	 	* @param float aspectRatio
 		* @return glm::mat4
		 **/
    		glm::mat4 GetProjectionMatrix(float aspectRatio) const;

		/**
 		* @brief handles keyboard input
	 	* @param const Uint8* pressState, float deltaTime
 		**/
    		void ProcessKeyboard(const Uint8* pressState, float deltaTime);
		
		/**
		* @brief handles keyboard keys rotation
		* @param float xOffset, float yOffset
		**/
		void ProcessKeyboardRotation(float xOffset, float yOffset, float deltaTime);

		/**
		* @brief handles mouse movements
		* @param float xOffset, yOffset, constrainPitch (default of true)
		**/
		void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
		float MouseSensitivity = 0.1f;

		/**
		 * @brief resets camera to original starting position
		 **/ 
		void Reset();
		
		// Camera attributes
    		glm::vec3 Position;
    		glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
    		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    		glm::vec3 Right;
    		float Yaw = -90.0f;
    		float Pitch = 0.0f;
		glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    		float MovementSpeed = 5.0f;
		float RotationSpeed = 8.0f;
    		float Zoom = 45.0f;
		float lastKey = -1.0f;
		const float doubleKey = 0.5f;


	private:
    		/**
 		* @brief updates camera vectors
  		**/
		void updateCameraVectors();
		
};

#endif // CAMERA_HPP
