#ifndef _window_hpp_
#define _window_hpp_

#include <SDL2/SDL.h>
#include "logger.hpp"
using namespace std;

extern Logger logger;

class Window{
   public:
      Window();
      ~Window();
      Window( const Window &window );
      Window & operator =( const Window &window );
      bool Create();
      void Update();
      void SetResolution( int width, int height );
      int ReturnWidth() const;
      int ReturnHeight() const;
      int ReturnWidthHalf() const;
      int ReturnHeightHalf() const;
      int ReturnWidthMin() const;
      int ReturnHeightMin() const;
      int ReturnWidthMax() const;
      int ReturnHeightMax() const;
      int ReturnPositionX() const;
      int ReturnPositionY() const;
      string ReturnTitle() const;
      bool ReturnInit() const;
      static void SetMaxMinResolution( SDL_Window * window, int &min_width, int &min_height, int &max_width, int &max_height  );
   private:
      SDL_Window * Id = nullptr;
      SDL_GLContext GLContext = nullptr;
      Uint32 Flag = SDL_WINDOW_OPENGL;
      int Width = 800;
      int Height = 600;
      int WidthHalf = Width / 2;
      int HeightHalf = Height / 2;
      int WidthMin = 800;
      int HeightMin = 600;
      int WidthMax = 800;
      int HeightMax = 600;
      int PositionX = SDL_WINDOWPOS_CENTERED;
      int PositionY = SDL_WINDOWPOS_CENTERED;
      string Title = "OpenGL";
      bool Init = false;
};

#endif
