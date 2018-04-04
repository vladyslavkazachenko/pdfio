#pragma once

#ifdef PDF_LOG

#include <functional>
#include <string>
#include <sstream>

namespace pdfio
{
  
extern std::function<void(const std::string &msg)> gLogErrorHandler;
extern std::function<void(const std::string &msg)> gLogDebugHandler;

#define LOG(msg, logHandler) {std::stringstream logStream; logStream << msg;\
  if(logHandler){logHandler(logStream.str());}}
#define LOG_DEBUG(msg) LOG(msg, pdfio::gLogDebugHandler)
#define LOG_ERROR(msg) LOG(msg, pdfio::gLogErrorHandler)
  
}

#else

#define LOG_DEBUG(msg) 
  
#endif //PDF_LOG