#include "read_info.h"

#include "read_dictionary.h"
#include "pdfio/log.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << \
  reinterpret_cast<unsigned long>(&istream) << "],info[" << \
  reinterpret_cast<unsigned long>(&info) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_0::Info &info)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   info.prepare4Reading();
   if(istream >> static_cast<pdf1_0::Dictionary &>(info))
   {
      
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}
