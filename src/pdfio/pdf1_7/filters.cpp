#include "filters.h"

#include <cstring>

#include "zlib.h"
#include "pdfio/log.h"

namespace pdfio
{
   
namespace pdf1_7
{
   
#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":input[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&input) << \
   "],output[" << reinterpret_cast<unsigned long>(&output) << "]:"
   
bool FlateDecode(const char *input, std::size_t length, std::string &output)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   LOG_DEBUG(LOG_PREFIX << "length=" << length << "\n");
   bool success = true;
   char c[1024];
   std::memset(c, '\0', 1024);
   z_stream zInfo;
   zInfo.avail_in = length;
   zInfo.avail_out = 1024;
   zInfo.next_in = (Bytef*)input;
   zInfo.next_out = (Bytef *)c;
   zInfo.zalloc = Z_NULL;
   zInfo.zfree = Z_NULL;
   if(inflateInit(&zInfo) == Z_OK)
   {
      int inflateStatus;
      while((inflateStatus = inflate(&zInfo, Z_SYNC_FLUSH)) == Z_OK)
      {
         output.append(c, 1024 - zInfo.avail_out);
         if(!zInfo.avail_out)
         {
            zInfo.next_out = (Bytef *)c;
            zInfo.avail_out = 1024;
         }
      }
      if(inflateStatus == Z_STREAM_END)
      {
         output.append(c, 1024 - zInfo.avail_out);
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "inflate failed, result=" << inflateStatus << 
            ",msg=" << zError(inflateStatus) << "\n");
         success = false;
      }
      if(inflateEnd(&zInfo) != Z_OK)
      {
         LOG_ERROR(LOG_PREFIX << "inflateEnd failed\n");
         success = false;
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "inflateInit failed\n");
      success = false;
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return success;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":input[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&input) << \
   "],output[" << reinterpret_cast<unsigned long>(&output) << "]:"

bool FlateDecode(const char *input, std::size_t length, int predictor, 
   int columns, std::string &output)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   LOG_DEBUG(LOG_PREFIX << "length=" << length << ",predictor=" << predictor << 
      ",columns=" << columns << "\n");
   bool success = true;
   if((success = FlateDecode(input, length, output)))
   {
      for(int i = 0; i < 100; i+=4)
      {
         if(!i || i)
         {
            LOG_DEBUG(LOG_PREFIX << static_cast<int>(uint8_t(output.data()[i])) << " " << static_cast<int>(*(reinterpret_cast<const uint16_t *>((output.data() + i +1)))) << " " << static_cast<int>(int8_t(output.data()[i+3])) << "\n");
         }
         else
         {
            LOG_DEBUG(LOG_PREFIX << static_cast<int>(output[i] + output[i - 4]) << " " << static_cast<int>(output[i+1] + output[i - 3]) << " " << static_cast<int>(output[i+2] + output[i - 2]) << " " << static_cast<int>(output[i+3] + output[i - 1]) << "\n");
         }
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "flate decoding failed\n");
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return true;
}

#undef LOG_PREFIX
   
}
   
}
