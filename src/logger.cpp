#include "logger.hpp"

Logger::Logger(){
   this->LogFile.open( this->LogFileName.c_str(), std::ios::out );
}

Logger::~Logger(){
   this->LogFile.close();
}

void Logger::operator <<( std::string input ){
   this->LogFile<<input<<"\n";
   std::cout<<input<<"\n";
}

void Logger::SendLog( std::string input ){
   this->LogFile<<"[LOG] "<<input<<"\n";
   std::cout<<"[LOG] "<<input<<"\n";
}

void Logger::SendError( std::string input ){
   this->LogFile<<"[ERROR] "<<input<<"\n";
   std::cout<<"[ERROR] "<<input<<"\n";
}

void Logger::SendDebug( std::string input ){
   this->LogFile<<"[DEBUG] "<<input<<"\n";
   std::cout<<"[DEBUG] "<<input<<"\n";
}
