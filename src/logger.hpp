#ifndef _logger_hpp_
#define _logger_hpp_

#include <iostream>
#include <fstream>

class Logger{
   public:
      Logger();
      ~Logger();
      void operator <<( std::string input );
      void SendLog( std::string input );
      void SendError( std::string input );
      void SendDebug( std::string input );
   private:
      std::ofstream LogFile;
      std::string LogFileName = "log.log";
};

#endif
