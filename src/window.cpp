#include "window.hpp"

Window::Window(){
}

Window::~Window(){
   SDL_GL_DeleteContext( this->GLContext );
   SDL_DestroyWindow( this->Id );
}

Window::Window( const Window &window ){
}

Window & Window::operator =( const Window &window ){
   return *this;
}

bool Window::Create(){
   logger << ( "[LOG] CREATING WINDOW:" );
   if( SDL_WasInit( SDL_INIT_VIDEO ) == 0 ){
      if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
         logger << ( "[ERROR] SDL_Init: " + string( SDL_GetError() ) );
         this->Init = false;
         return false;
      }
      else{
         logger << ( "[LOG] SDL_Init: SUCCESS" );
      }
   }

   this->Id = SDL_CreateWindow( this->Title.c_str(), this->PositionX, this->PositionY, this->Width, this->Height, this->Flag );
   if( this->Id == NULL ){
      logger << ( "[ERROR] SDL_CreateWindow: " + string( SDL_GetError() ) );
      this->Init = false;
      return false;
   }
   else{
      logger << ( "[LOG] SDL_CreateWindow: SUCCESS" );
   }

   SDL_Surface *surface = NULL;
   Uint16 pixels[16*16] = {
      0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000,
      0xf000, 0xffff, 0xffff, 0xffff, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000,
      0xf000, 0xffff, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000,
      0xf000, 0xffff, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000,
      0xf000, 0xffff, 0xffff, 0xffff, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000,
      0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xffff, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000,
      0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xffff, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000,
      0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000,
      0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xffff, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000,
      0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xffff, 0xf000, 0xf000, 0xf000, 0xf000, 0xffff, 0xf000, 0xf000, 0xf000,
      0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xffff, 0xf000, 0xf000, 0xf000,
      0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xf000,
      0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xffff, 0xf000, 0xf000, 0xf000,
      0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xffff, 0xf000, 0xf000, 0xf000,
      0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000,
      0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000, 0xf000
   };
   surface = SDL_CreateRGBSurfaceFrom( pixels, 16, 16, 16, 16*2, 0x0f00, 0x00f0, 0x000f, 0xf000 );
   if( surface == NULL ){
      logger << ( "[ERROR] SDL_SetWindowIcon: " + string( SDL_GetError() ) );
      this->Init = false;
      return false;
   }
   else{
      logger << ( "[LOG] SDL_SetWindowIcon: SUCCESS" );
      SDL_SetWindowIcon( this->Id, surface );
      SDL_FreeSurface( surface );
   }

   this->GLContext = SDL_GL_CreateContext( this->Id );
   if( this->GLContext == NULL ){
      logger << ( "[ERROR] SDL_GL_CreateContext: " + string( SDL_GetError() ) );
      this->Init = false;
      return false;
   }
   else{
      logger << ( "[LOG] SDL_GL_CreateContext: SUCCESS" );
   }


   logger << ( "[LOG] SDL_GetWindowDisplayIndex: " + to_string( SDL_GetWindowDisplayIndex( this->Id ) ) );
   logger << ( "[LOG] SDL_GetWindowID: " + to_string( SDL_GetWindowID( this->Id ) ) );
   logger << ( "[LOG] SDL_GetWindowBrightness: " + to_string( SDL_GetWindowBrightness( this->Id ) ) );

   SDL_SetWindowMinimumSize( this->Id, this->WidthMin, this->HeightMin );
   SDL_SetWindowMaximumSize( this->Id, this->WidthMax, this->HeightMax );
   Window::SetMaxMinResolution( this->Id, this->WidthMin, this->HeightMin, this->WidthMax, this->HeightMax );

   logger << ( "[LOG] CREATED WINDOW" );
   this->Init = true;
   return this->Init;
}

void Window::Update(){
   SDL_GL_SwapWindow( this->Id );
}

void Window::SetResolution( int width, int height ){
   if( width < this->WidthMin or
       width > this->WidthMax or
       height < this->HeightMin or
       height > this->HeightMax
    ){
      return;
   }
   this->Width = width;
   this->Height = height;
   this->WidthHalf = this->Width / 2;
   this->HeightHalf = this->Height / 2;
}

int Window::ReturnWidth() const{
   return this->Width;
}

int Window::ReturnHeight() const{
   return this->Height;
}

int Window::ReturnWidthHalf() const{
   return this->WidthHalf;
}

int Window::ReturnHeightHalf() const{
   return this->HeightHalf;
}

int Window::ReturnWidthMin() const{
   return this->WidthMin;
}

int Window::ReturnHeightMin() const{
   return this->HeightMin;
}

int Window::ReturnWidthMax() const{
   return this->WidthMax;
}

int Window::ReturnHeightMax() const{
   return this->HeightMax;
}

int Window::ReturnPositionX() const{
   return this->PositionX;
}

int Window::ReturnPositionY() const{
   return this->PositionY;
}

string Window::ReturnTitle() const{
   return this->Title;
}

bool Window::ReturnInit() const{
   return this->Init;
}

void Window::SetMaxMinResolution( SDL_Window * window, int &min_width, int &min_height, int &max_width, int &max_height  ){
   if( window == NULL or window == nullptr ){
      return;
   }

   int DisplayIndex = SDL_GetWindowDisplayIndex( window );
   SDL_DisplayMode CurrentDisplayMode;

   if( SDL_GetDisplayMode( DisplayIndex, SDL_GetNumDisplayModes( DisplayIndex ) - 1, &CurrentDisplayMode ) == 0 ){
      min_width = CurrentDisplayMode.w;
      min_height = CurrentDisplayMode.h;
      logger << ( "[LOG] Minimal resolution: " + to_string( min_width ) + "x" + to_string( min_height ) );
   }
   else{
      logger << ( "[ERROR] SDL_GetDisplayMode: " + string( SDL_GetError() ) );
      return;
   }
   SDL_SetWindowMinimumSize( window, min_width, min_height );

   if( SDL_GetDisplayMode( DisplayIndex, 0, &CurrentDisplayMode ) == 0 ){
      max_width = CurrentDisplayMode.w;
      max_height = CurrentDisplayMode.h;
      logger << ( "[LOG] Maximal resolution: " + to_string( max_width ) + "x" + to_string( max_height ) );
   }
   else{
      logger << ( "[ERROR] SDL_GetDisplayMode: " + string( SDL_GetError() ) );
      return;
   }
   SDL_SetWindowMaximumSize( window, max_width, max_height );
}
