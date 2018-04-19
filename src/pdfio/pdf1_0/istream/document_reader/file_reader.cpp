#include "file_reader.h"

#include "pdfio/pdf1_0/istream/include.h"
#include "pdfio/pdf1_0/istream/read_file_structure.h"

namespace pdfio
{
   
namespace pdf1_0
{
   
bool FileReader::loadFile(const std::string &fullFilePath)
{
   mCachedObjects.clear();
   fileStruct_ = FileStructure();
   mutex_.lock();
   file_ = fullFilePath;
   auto &stream = streamPool_.acquireStream();
   if(stream.is_open())
   {
      stream.close();
   }
   stream.open(file_.c_str(), std::ios_base::binary | std::ios_base::in);
   if(!stream.is_open())
   {
      mutex_.unlock();
      streamPool_.releaseStream(stream);
      return false;
   }
   if(!(stream >> fileStruct_))
   {
      mutex_.unlock();
      streamPool_.releaseStream(stream);
      return false;
   }
   mutex_.unlock();
   streamPool_.releaseStream(stream);
   return true;
}

bool FileReader::getDocumentCatalog(DocumentCatalog &docCatalog)
{
   int i = fileStruct_.versions_.size() - 1;
   for(; i >= 0; --i)
   {
      if(fileStruct_.versions_[i].trailer_.hasRoot())
      {
         break;
      }
   }
   if(i < 0)
   {
      return false;
   }
   auto &trailer = fileStruct_.versions_[i].trailer_;
   return getObject(trailer.root().objectNumber(), trailer.root().generationNumber(), docCatalog);
}

std::streampos FileReader::findObject(Integer objectNumber, Integer generation)
{
   for(auto version : fileStruct_.versions_)
   {
      auto &xrefSection = version.xrefSection_;
      for(size_t i = 0; i < xrefSection.subsections().size(); ++i)
      {
         const auto &subsection = xrefSection.subsections()[i];
         auto objectIndex = objectNumber - subsection.firstObjectNumber_;
         if((objectIndex >= 0) && (static_cast<size_t>(objectIndex) < subsection.entries_.size()))
         {
            const auto &entry = subsection.entries_[static_cast<size_t>(objectIndex)];
            if(entry.generation_ == generation)
            {
               return static_cast<std::streampos>(entry.offset_);
            }
            else
            {
               i = xrefSection.subsections().size();
            }
         }
      }
   }
   return -1;
}
   
}

}
