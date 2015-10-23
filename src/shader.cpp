#include "shader.hpp"

Shader::Shader(){
}

Shader::~Shader(){
   glDeleteProgram( this->Id );
}

Shader::Shader( const Shader &shader ){
   this->Id = shader.Id;
}

Shader & Shader::operator =( const Shader &shader ){
   this->Id = shader.Id;
   return *this;
}

bool Shader::Create( string vertex_path, string fragment_path, string geometry_path = "" ){
   if( vertex_path.empty() ){
      logger << ( "[ERROR] Vertex shader path is empty!" );
      return false;
   }
   if(  fragment_path.empty() ){
      logger << ( "[ERROR] Fragment shader path is empty!" );
      return false;
   }
   logger << ( "[LOG] CREATING SHADER:" );
   logger << ( "[LOG] Shader Vertex: " + vertex_path );
   logger << ( "[LOG] Shader Fragment: " + fragment_path );
   if( ! geometry_path.empty() ){
      logger << ( "[LOG] Shader Geometry: " + geometry_path );
   }

   string vertex_code;
   ifstream vertex_file;
   vertex_file.open( vertex_path.c_str() );
   if( vertex_file.good() ){
      ostringstream vertex_stream;
      vertex_stream << vertex_file.rdbuf();
      vertex_file.close();
      vertex_code = vertex_stream.str();
   }
   else{
      logger << ( "[ERROR] Problem with file: " + vertex_path );
      return false;
   }

   string fragment_code;
   ifstream fragment_file;
   fragment_file.open( fragment_path.c_str() );
   if( fragment_file.good() ){
      ostringstream fragment_stream;
      fragment_stream << fragment_file.rdbuf();
      fragment_file.close();
      fragment_code = fragment_stream.str();
   }
   else{
      logger << ( "[ERROR] Problem with file: " + fragment_path );
      return false;
   }

   string geometry_code;
   ifstream geometry_file;
   if( ! geometry_path.empty() ){
      if( geometry_file.good() ){
         ostringstream geometry_stream;
         geometry_stream << geometry_file.rdbuf();
         geometry_file.close();
         geometry_code = geometry_stream.str();
      }
      else{
         logger << ( "[ERROR] Problem with file: " + geometry_path );
         return false;
      }
   }


   GLint shader_error;
   GLint shader_error_length;

   const GLchar * vertex_code_gl = vertex_code.c_str();
   GLuint vertex = 0;
   vertex = glCreateShader( GL_VERTEX_SHADER );
   glShaderSource( vertex, 1, &vertex_code_gl, NULL );
   glCompileShader( vertex );
   shader_error = GL_FALSE;
   glGetShaderiv( vertex, GL_COMPILE_STATUS, &shader_error );
   if( shader_error == GL_FALSE ){
      shader_error_length = 0;
      glGetShaderiv( vertex, GL_INFO_LOG_LENGTH, &shader_error_length );
      vector <GLchar> Message( shader_error_length );
      glGetShaderInfoLog( vertex, shader_error_length, &shader_error_length, &Message[0] );
      string shader_error_string = string( Message.begin(), Message.end() );
      logger << ( "[ERROR] Vertex shader: " + shader_error_string );
      glDeleteShader( vertex );
      return false;
   }

   const GLchar * fragment_code_gl = fragment_code.c_str();
   GLuint fragment = 0;
   fragment = glCreateShader( GL_FRAGMENT_SHADER );
   glShaderSource( fragment, 1, &fragment_code_gl, NULL );
   glCompileShader( fragment );
   shader_error = GL_FALSE;
   glGetShaderiv( fragment, GL_COMPILE_STATUS, &shader_error );
   if( shader_error == GL_FALSE ){
      shader_error_length = 0;
      glGetShaderiv( fragment, GL_INFO_LOG_LENGTH, &shader_error_length );
      vector <GLchar> Message( shader_error_length );
      glGetShaderInfoLog( fragment, shader_error_length, &shader_error_length, &Message[0] );
      string shader_error_string = string( Message.begin(), Message.end() );
      logger << ( "[ERROR] Fragment shader: " + shader_error_string );
      glDeleteShader( fragment );
      return false;
   }

   const GLchar * geometry_code_gl = nullptr;
   GLuint geometry = 0;
   if( ! geometry_path.empty() ){
      geometry_code_gl = geometry_code.c_str();
      geometry = glCreateShader( GL_GEOMETRY_SHADER );
      glShaderSource( geometry, 1, &geometry_code_gl, NULL );
      glCompileShader( geometry );
      shader_error = GL_FALSE;
      glGetShaderiv( geometry, GL_COMPILE_STATUS, &shader_error );
      if( shader_error == GL_FALSE ){
         shader_error_length = 0;
         glGetShaderiv( geometry, GL_INFO_LOG_LENGTH, &shader_error_length );
         vector <GLchar> Message( shader_error_length );
         glGetShaderInfoLog( geometry, shader_error_length, &shader_error_length, &Message[0] );
         string shader_error_string = string( Message.begin(), Message.end() );
         logger << ( "[ERROR] Geometry shader: " + shader_error_string );
         glDeleteShader( geometry );
         return false;
      }
   }


   this->Id = glCreateProgram();
   glAttachShader( this->Id, vertex );
   glAttachShader( this->Id, fragment );
   if( ! geometry_path.empty() ){
      glAttachShader( this->Id, geometry );
   }
   glLinkProgram( this->Id );
   shader_error = GL_FALSE;
   glGetProgramiv( this->Id, GL_LINK_STATUS, &shader_error );
   if( shader_error == GL_FALSE ){
      shader_error_length = 0;
      glGetProgramiv( this->Id, GL_INFO_LOG_LENGTH, &shader_error_length );
      vector <GLchar> Message( shader_error_length );
      glGetProgramInfoLog( this->Id, shader_error_length, &shader_error_length, &Message[0] );
      string shader_error_string = string( Message.begin(), Message.end() );
      logger << ( "[ERROR] Geometry shader: " + shader_error_string );
      glDeleteProgram( this->Id );
      glDeleteShader( vertex );
      glDeleteShader( fragment );
      if( ! geometry_path.empty() ){
         glDeleteShader( geometry );
      }
      return false;
   }
   glDeleteShader( vertex );
   glDeleteShader( fragment );
   if( ! geometry_path.empty() ){
      glDeleteShader( geometry );
   }

   logger << ( "[LOG] CREATED SHADER" );
   return true;
}

void Shader::Use() const{
   glUseProgram( this->Id );
}

GLuint Shader::ReturnId() const{
   return this->Id;
}
