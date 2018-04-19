#pragma once

#include <string>
#include <mutex>
#include <map>

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
      cacheMutex_.lock();
      auto iter1 = mCachedObjects.find(objectNumber);
      if(iter1 != mCachedObjects.end())
      {
         auto iter2 = iter1->second.find(generation);
         if(iter2 != iter1->second.end())
         {
            object = iter2->second.get<T>();
            cacheMutex_.unlock();
            return true;
         }
      }
      cacheMutex_.unlock();
      auto pos = findObject(objectNumber, generation);
      if(pos == -1)
      {
         return false;
      }
      auto &stream = streamPool_.acquireStream();
      if(stream.is_open())
      {
         stream.close();
      }
      stream.open(file_.c_str(), std::ios_base::binary | std::ios_base::in);
      if(!stream.is_open())
      {
         streamPool_.releaseStream(stream);
         return false;
      }
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
      cacheMutex_.lock();
      mCachedObjects[objectNumber][generation] = indirectObject.get<T>();
      cacheMutex_.unlock();
      return true;
   }
   
private:
   std::streampos findObject(Integer objectNumber, Integer generation);
   
   StreamPool streamPool_;
   std::string file_;
   std::mutex mutex_;
   FileStructure fileStruct_;
   std::map<Integer, std::map<Integer, IndirectObject>> mCachedObjects;
   std::mutex cacheMutex_;
};
   
}
   
}