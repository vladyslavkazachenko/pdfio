#include "log.h"

namespace pdfio
{

std::function<void(const std::string &msg)> gLogErrorHandler;
std::function<void(const std::string &msg)> gLogDebugHandler;

}