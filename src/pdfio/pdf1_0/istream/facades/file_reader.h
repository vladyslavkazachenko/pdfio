#pragma once

#include <string>
#include <mutex>

#include "istream_pool.h"
#include "pdfio/pdf1_0/file_structure.h"
#include "pdfio/pdf1_0/document_catalog.h"
#include "pdfio/pdf1_0/indirect_object.h"
#include "pdfio/pdf1_0/istream/read_indirect_object.h"

namespace pdfio
{
   
namespace pdf1_0
{
   
class FileReader
{
public:
   bool loadFile(const std::string &fullFilePath);
   bool getDocumentCatalog(DocumentCatalog &docCatalog);
   
   template <typename T> bool getObject(Integer objectNumber, Integer generation, T &object)
   {
      auto pos = findObject(objectNumber, generation);
      if(pos == -1)
      {
         return false;
      }
      auto &stream = streamPool_.acquireStream();
      stream.clear();
      if(!stream.seekg(pos))
      {
         streamPool_.releaseStream(stream);
         return false;
      }
      IndirectObject indirectObject;
      indirectObject.set<T>();
      if(!(stream >> indirectObject))
      {
         streamPool_.releaseStream(stream);
         return false;
      }
      streamPool_.releaseStream(stream);
      object = indirectObject.get<T>();
      return true;
   }
   
private:
   std::streampos findObject(Integer objectNumber, Integer generation);
   
   StreamPool streamPool_;
   std::string file_;
   std::mutex mutex_;
   FileStructure fileStruct_;
};
   
}
   
}