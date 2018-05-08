#include "write_name.h"

#include "pdfio/log.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&ostream) << \
   "],name[" << reinterpret_cast<unsigned long>(&name) << "]:"

std::ostream &operator<<(std::ostream &ostream, 
   const pdf1_0::Name &name)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   if(ostream << '/')
   {
      ostream << static_cast<std::string>(name);
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return ostream;
}
