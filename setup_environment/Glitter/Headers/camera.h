// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    DOWN,
    UP,
    ROTRIGHT,
    ROTLEFT,
    ROTUP,
    ROTDOWN,
    TILTRIGHT,
    TILTLEFT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  1.0f;
const float SENSITIVITY =  0.05f;
const float ZOOM        =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
        if (direction == DOWN)
            Position -= Up * velocity;
        if (direction == UP)
            Position += Up * velocity;
        if (direction == ROTRIGHT) {
            glm::mat4 rotationMat(1);
            rotationMat = glm::rotate(rotationMat, -0.05f, WorldUp);

            glm::vec4 positionVec(Front.x, Front.y, Front.z, 1.0);
            Front = glm::vec3(rotationMat * positionVec);

            glm::vec4 worldVec(WorldUp.x, WorldUp.y, WorldUp.z, 1.0);
            WorldUp = glm::vec3(rotationMat * worldVec);

            updateVectors();
        }
        if (direction == ROTLEFT) {
            glm::mat4 rotationMat(1);
            rotationMat = glm::rotate(rotationMat, 0.05f, WorldUp);

            glm::vec4 positionVec(Front.x, Front.y, Front.z, 1.0);
            Front = glm::vec3(rotationMat * positionVec);

            glm::vec4 worldVec(WorldUp.x, WorldUp.y, WorldUp.z, 1.0);
            WorldUp = glm::vec3(rotationMat * worldVec);

            updateVectors();
        }
        /*if (direction == ROTRIGHT) {
            Yaw += 1.0f;
            updateCameraVectors();
        }
        if (direction == ROTLEFT) {
            Yaw -= 1.0f;
            updateCameraVectors();
        }*/
        if (direction == ROTUP) {
            glm::mat4 rotationMat(1);
            rotationMat = glm::rotate(rotationMat, 0.05f, Right);

            glm::vec4 positionVec(Front.x, Front.y, Front.z, 1.0);
            Front = glm::vec3(rotationMat * positionVec);

            glm::vec4 worldVec(WorldUp.x, WorldUp.y, WorldUp.z, 1.0);
            WorldUp = glm::vec3(rotationMat * worldVec);

            updateVectors();
        }
        if (direction == ROTDOWN) {
            glm::mat4 rotationMat(1);
            rotationMat = glm::rotate(rotationMat, -0.05f, Right);

            glm::vec4 positionVec(Front.x, Front.y, Front.z, 1.0);
            Front = glm::vec3(rotationMat * positionVec);

            glm::vec4 worldVec(WorldUp.x, WorldUp.y, WorldUp.z, 1.0);
            WorldUp = glm::vec3(rotationMat * worldVec);

            updateVectors();
        }
        if (direction == TILTRIGHT) {
            glm::mat4 rotationMat(1);
            rotationMat = glm::rotate(rotationMat, 0.05f, Front);

            glm::vec4 positionVec(Front.x, Front.y, Front.z, 1.0);
            Front = glm::vec3(rotationMat * positionVec);

            glm::vec4 worldVec(WorldUp.x, WorldUp.y, WorldUp.z, 1.0);
            WorldUp = glm::vec3(rotationMat * worldVec);

            updateVectors();
        }
        if (direction == TILTLEFT) {
            glm::mat4 rotationMat(1);
            rotationMat = glm::rotate(rotationMat, -0.05f, Front);

            glm::vec4 positionVec(Front.x, Front.y, Front.z, 1.0);
            Front = glm::vec3(rotationMat * positionVec);

            glm::vec4 worldVec(WorldUp.x, WorldUp.y, WorldUp.z, 1.0);
            WorldUp = glm::vec3(rotationMat * worldVec);

            updateVectors();
        }
    }

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= yoffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;
    }

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // Also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }

    void updateVectors()
    {
        // Rze-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};
#endif