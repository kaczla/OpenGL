#ifndef _shader_hpp_
#define _shader_hpp_

#include <sstream>
#include <vector>
#include <GL/glew.h>
#include "logger.hpp"
using namespace std;

extern Logger logger;

class Shader{
   public:
      Shader();
      ~Shader();
      Shader( const Shader &shader );
      Shader & operator =( const Shader &shader );
      bool Create( string vertex_path, string fragment_path, string geometry_path );
      void Use() const;
      GLuint ReturnId() const;
   private:
      GLuint Id = 0;
};

#endif
