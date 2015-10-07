#ifndef _camera_hpp_
#define _camera_hpp_

#include <GL/glew.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "logger.hpp"
using namespace std;
using namespace glm;

extern Logger logger;

class Camera{
   public:
      Camera();
      ~Camera();
      mat4 ReturnProjectionMatrix() const;
      mat4 ReturnViewMatrix() const;
      void Update();
      void SetPosition( vec3 & position );
      void SetUp( vec3 & up );
      void SetViewDirection( vec3 & view_direction );
      void SetVOF( GLfloat & fov );
      void SetAspect( GLfloat & aspect );
      void SetNear( GLfloat & near );
      void SetFar( GLfloat & far );
      vec3 ReturnPosition() const;
      vec3 ReturnUp() const;
      vec3 ReturnViewDirection() const;
      GLfloat ReturnVOF() const;
      GLfloat ReturnAspect() const;
      GLfloat ReturnNear() const;
      GLfloat ReturnFar() const;
      void MouseUpdate( const vec2 & mouse );
      void MoveUp();
      void MoveDown();
      void MoveForward();
      void MoveBackward();
      void MoveLeft();
      void MoveRight();
      void Log() const;
   private:
      vec3 Position = vec3( 0.0f, 1.0f, 0.0f );
      vec3 Up = vec3( 0.0f, 1.0f, 0.0f );
      vec3 ViewDirection = vec3( 0.0f, 0.0f, -1.0f );
      GLfloat VOF = 45.0f;
      GLfloat Aspect = 800.0f / 600.0f;
      GLfloat Near = 0.1f;
      GLfloat Far = 100.0f;
      GLfloat RotationSpeed = 0.0005f;
      GLfloat MovementSpeed = 0.1f;
      vec3 RotationAround;
      mat4 Rotation;
      vec3 MovementDirection;
      void UpdateViewMatrix();
      void UpdateProjectionMatrix();
      mat4 ViewMatrix;
      mat4 ProjectionMatrix;
};

#endif
