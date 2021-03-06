#include "pdfio.h"

#include <map>
#include <memory>

#include "pdfio/log.h"
#include "document_reader.h"

using namespace pdfio::pdf1_0;

namespace
{
   
int gDocReaderHandle = 0;
std::map<int, std::shared_ptr<DocumentReader>> gDocReaders;
   
}

extern "C" void pdfio_setdebuglogger(void (*f)(const char *msg))
{
   if(f)
   {
      pdfio::gLogDebugHandler = [f](const std::string &msg){(*f)(msg.c_str());};
   }
   else
   {
      pdfio::gLogDebugHandler = nullptr;
   }
}

extern "C" int pdfio_docreader_create()
{
   gDocReaders[gDocReaderHandle] = std::make_shared<DocumentReader>();
   return gDocReaderHandle++;
}

extern "C" void pdfio_docreader_destroy(int docreader)
{
   gDocReaders.erase(docreader);
}

extern "C" int pdfio_docreader_loadfile(int docreader, const char *fullFileName)
{
   return gDocReaders[docreader]->loadFile(fullFileName);
}