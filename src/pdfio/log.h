#pragma once

#include <functional>
#include <string>

namespace pdfio
{
  
extern std::function<void(const std::string &msg)> gLogErrorHandler;
extern std::function<void(const std::string &msg)> gLogWarningHandler;
extern std::function<void(const std::string &msg)> gLogDebugHandler;
  
}

#ifdef PDF_LOG

#include <sstream>

#define LOG(msg, logHandler) {std::stringstream logStream; \
   logStream << msg; if(logHandler){logHandler(logStream.str());}}

#define LOG_ERROR(msg) LOG(msg, pdfio::gLogErrorHandler)
#define LOG_WARNING(msg) LOG(msg, pdfio::gLogWarningHandler)
#define LOG_DEBUG(msg) LOG(msg, pdfio::gLogDebugHandler)

#else

#define LOG_ERROR(msg)
#define LOG_WARNING(msg)
#define LOG_DEBUG(msg)
  
#endif //PDF_LOG
