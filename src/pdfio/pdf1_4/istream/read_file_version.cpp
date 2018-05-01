#include "read_file_version.h"

#include "pdfio/log.h"
#include "pdfio/pdf1_0/istream/read_file_structure.h"

namespace pdf1_4 = pdfio::pdf1_4;
namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&istream) << \
   "],header[" << reinterpret_cast<unsigned long>(&header) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::FileVersion::Header &header)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   if(istream >> header.data_)
   {
      if(header.data_ != "%PDF−1.0" && header.data_ != "%PDF−1.1" &&
         header.data_ != "%PDF−1.2" && header.data_ != "%PDF−1.3" &&
         header.data_ != "%PDF−1.4")
      {
         LOG_ERROR(LOG_PREFIX << "header is invalid: " << header.data_ << "\n");
         istream.setstate(std::ios_base::failbit);
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "failed to read end of stream, "
         "stream state is " << 
         istream.rdstate() << "\n");
      istream.setstate(std::ios_base::failbit);
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&istream) << \
   "],entry[" << reinterpret_cast<unsigned long>(&entry) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::FileVersion::XrefEntry &entry)
{
   if(istream >> entry.offset_)
   {
      if(istream >> entry.generation_)
      {
         char inUseFlag;
         if(istream >> inUseFlag)
         {
            if(inUseFlag == 'n')
            {
               entry.inUseFlag_ = true;
            }
            else
            {
               if(inUseFlag == 'f')
               {
                  entry.inUseFlag_ = false;
               }
               else
               {
                  LOG_ERROR(LOG_PREFIX << "invalid in use flag: " << std::hex << std::showbase << 
                     static_cast<int>(inUseFlag) << "\n");
                  istream.setstate(std::ios_base::failbit);
               }
            }
         }
         else
         {
            LOG_ERROR(LOG_PREFIX << "failed to read in use flag: stream state " << istream.rdstate() << "\n");
         }
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "failed to read generation: stream state " << istream.rdstate() << "\n");
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "failed to read offset: stream state " << istream.rdstate() << "\n");
   }
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&istream) << \
   "],trailer[" << reinterpret_cast<unsigned long>(&trailer) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::FileVersion::Trailer &trailer)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   trailer.prepare4Reading();
   istream >> static_cast<pdf1_0::FileStructure::Trailer &>(trailer);
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX
