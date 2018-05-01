#include "read_file_structure.h"

#include <cassert>

#include "pdfio/log.h"
#include "pdfio/pdf1_0/istream/read_file_structure.h"
#include "pdfio/pdf1_4/istream/read_file_version.h"

namespace pdf1_4 = pdfio::pdf1_4;
namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&istream) << \
   "],trailer[" << reinterpret_cast<unsigned long>(&trailer) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::FileStructure::Trailer &trailer)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   trailer.prepare4Reading();
   istream >> static_cast<pdf1_0::FileStructure::Trailer &>(trailer);
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&istream) << \
   "],fileStruct[" << reinterpret_cast<unsigned long>(&fileStruct) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdfio::FileStructure<pdfio::pdf1_4::FileVersion> &fileStruct)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   if(istream >> fileStruct.header_)
   {
      if(istream.seekg(-1, std::ios_base::end))
      {
         if(istream.peek() == '\n' || istream.peek() == '\r')
         {
            if(istream.seekg(-1, std::ios_base::cur))
            {
               if(istream.peek() == '\r')
               {
                  if(!(istream.seekg(-1, std::ios_base::cur)))
                  {
                     LOG_ERROR(LOG_PREFIX << "failed to seek to the two before "
                        "last character offset: stream state " << 
                        istream.rdstate() << "\n");
                  }
               }
            }
            else
            {
               LOG_ERROR(LOG_PREFIX << "failed to seek to the one before last "
                  "character offset: stream state " << istream.rdstate() << 
                  "\n");
            }
         }
         if(istream)
         {
            while(istream && istream.peek() != '\n' && istream.peek() != '\r')
            {
               istream.seekg(-1, std::ios_base::cur);
            }
            if(istream)
            {
               auto pos = istream.tellg();
               std::string eofLine;
               if(istream >> eofLine)
               {
                  if(eofLine != "%%EOF")
                  {
                     LOG_ERROR(LOG_PREFIX << "invalid eof line: " << eofLine << 
                        "\n");
                     istream.setstate(std::ios_base::failbit);
                  }
               }
               else
               {
                  LOG_ERROR(LOG_PREFIX << "failed to read eof line: "
                     "stream state " << istream.rdstate() << "\n");
               }
               if(istream)
               {
                  assert(istream.seekg(pos));
                  if(istream.peek() == '\n' || istream.peek() == '\r')
                  {
                     if(istream.seekg(-1, std::ios_base::cur))
                     {
                        if(istream.peek() == '\r')
                        {
                           if(!(istream.seekg(-1, std::ios_base::cur)))
                           {
                              LOG_ERROR(LOG_PREFIX << "failed to seek to two "
                                 "before last character offset: "
                                 "stream state " << istream.rdstate() << "\n");
                           }
                        }
                     }
                     else
                     {
                        LOG_ERROR(LOG_PREFIX << "failed to seek to one before "
                           "last character offset: stream state " << 
                           istream.rdstate() << "\n");
                     }
                  }
                  while(istream && istream.peek() != '\n' && 
                     istream.peek() != '\r')
                  {
                     istream.seekg(-1, std::ios_base::cur);
                  }
                  if(istream)
                  {
                     pdf1_0::Integer lastXrefOffset;
                     if(istream >> lastXrefOffset)
                     {
                        auto xrefOffset = lastXrefOffset;
                        while(xrefOffset != -1)
                        {
                           istream.seekg(int(xrefOffset));
                           xrefOffset = -1;
                           while(std::isspace(istream.peek()))
                           {
                              static_cast<void>(istream.get());
                           }
                           pos = istream.tellg();
                           pdf1_4::FileVersion::XrefSection xrefSection;
                           if(istream >> xrefSection)
                           {
                              pdf1_4::FileVersion::Trailer trailer;
                              if(istream >> trailer)
                              {
                                 pdf1_4::FileVersion version;
                                 version.xrefSection_ = xrefSection;
                                 version.trailer_ = trailer;
                                 fileStruct.versions_.insert(
                                    std::begin(fileStruct.versions_), version);
                                 if(trailer.hasPrev())
                                 {
                                    xrefOffset = trailer.prev();
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "failed to seek to the last character offset: "
            "stream state " << istream.rdstate() << "\n");
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "failed to read file header: stream state " << 
         istream.rdstate() << "\n");
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX
