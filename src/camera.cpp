#include "camera.hpp"

Camera::Camera(){
   this->ViewMatrix = lookAt( this->Position, this->Position + this->ViewDirection, this->Up );
   this->ProjectionMatrix = perspective( radians( this->VOF ), this->Aspect, this->Near, this->Far );
}

Camera::~Camera(){
}

mat4 Camera::ReturnProjectionMatrix() const{
   return this->ProjectionMatrix;
}

mat4 Camera::ReturnViewMatrix() const{
   return this->ViewMatrix;
}

void Camera::Update(){
   this->ViewMatrix = lookAt( this->Position, this->Position + this->ViewDirection, this->Up );
   this->ProjectionMatrix = perspective( radians( this->VOF ), this->Aspect, this->Near, this->Far );
}

void Camera::SetPosition( vec3 & position ){
   this->Position = position;
   this->UpdateViewMatrix();
}

void Camera::SetUp( vec3 & up ){
   this->Up = up;
   this->UpdateViewMatrix();
}

void Camera::SetViewDirection( vec3 & view_direction ){
   this->ViewDirection = view_direction;
   this->UpdateViewMatrix();
}

void Camera::SetVOF( GLfloat & fov ){
   this->VOF = fov;
   this->UpdateProjectionMatrix();
}

void Camera::SetAspect( GLfloat & aspect ){
   this->Aspect = aspect;
   this->UpdateProjectionMatrix();
}

void Camera::SetNear( GLfloat & near ){
   this->Near = near;
   this->UpdateProjectionMatrix();
}

void Camera::SetFar( GLfloat & far ){
   this->Far = far;
   this->UpdateProjectionMatrix();
}

vec3 Camera::ReturnPosition() const{
   return this->Position;
}

vec3 Camera::ReturnUp() const{
   return this->Up;
}

vec3 Camera::ReturnViewDirection() const{
   return this->ViewDirection;
}

GLfloat Camera::ReturnVOF() const{
   return this->VOF;
}

GLfloat Camera::ReturnAspect() const{
   return this->Aspect;
}

GLfloat Camera::ReturnNear() const{
   return this->Near;
}

GLfloat Camera::ReturnFar() const{
   return this->Far;
}

void Camera::MouseUpdate( const vec2 & mouse ){
   this->RotationAround = cross( this->ViewDirection, this->Up );
   this->Rotation = rotate( mouse.x * this->RotationSpeed, this->Up ) * rotate( mouse.y * this->RotationSpeed, this->RotationAround );
   this->ViewDirection = mat3( this->Rotation ) * this->ViewDirection;
   this->UpdateViewMatrix();
}

void Camera::MoveUp(){
   this->Position += this->MovementSpeed * this->Up;
   this->UpdateViewMatrix();
}

void Camera::MoveDown(){
   this->Position -= this->MovementSpeed * this->Up;
   this->UpdateViewMatrix();
}

void Camera::MoveForward(){
   this->Position += this->MovementSpeed * this->ViewDirection;
   this->UpdateViewMatrix();
}

void Camera::MoveBackward(){
   this->Position -= this->MovementSpeed * this->ViewDirection;
   this->UpdateViewMatrix();
}

void Camera::MoveLeft(){
   this->MovementDirection = normalize( cross( this->ViewDirection, this->Up ) );
   this->Position -= this->MovementSpeed * this->MovementDirection;
   this->UpdateViewMatrix();
}

void Camera::MoveRight(){
   this->MovementDirection = normalize( cross( this->ViewDirection, this->Up ) );
   this->Position += this->MovementSpeed * this->MovementDirection;
   this->UpdateViewMatrix();
}

void Camera::Log() const{
   logger << ( "[LOG] CAMERA:" );
   logger << ( "\tPosition      : " + to_string( this->Position.x ) + " ; " + to_string( this->Position.y ) + " ; " + to_string( this->Position.z ) );
   logger << ( "\tViewDirection : " + to_string( this->ViewDirection.x ) + " ; " + to_string( this->ViewDirection.y ) + " ; " + to_string( this->ViewDirection.z ) );
   logger << ( "\tUp            : " + to_string( this->Up.x ) + " ; " + to_string( this->Up.y ) + " ; " + to_string( this->Up.z ) );
   logger << ( "\tVOF    : " + to_string( this->VOF ) );
   logger << ( "\tAspect : " + to_string( this->Aspect ) );
   logger << ( "\tNear   : " + to_string( this->Near ) );
   logger << ( "\tFar    : " + to_string( this->Far ) );
}

void Camera::UpdateViewMatrix(){
   this->ViewMatrix = lookAt( this->Position, this->Position + this->ViewDirection, this->Up );
}

void Camera::UpdateProjectionMatrix(){
   this->ProjectionMatrix = perspective( radians( this->VOF ), this->Aspect, this->Near, this->Far );
}
