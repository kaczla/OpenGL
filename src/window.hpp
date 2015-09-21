
extern Logger logger;

class Window{
   public:
      Window();
      ~Window();
      bool Create();
      void Update();
      void SetResolution( int width, int height )
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
