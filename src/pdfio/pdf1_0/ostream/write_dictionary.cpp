#include "write_dictionary.h"

#include "pdfio/log.h"
#include "write_name.h"
#include "pdfio/write_generic_object.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":ostream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&ostream) << \
   "],dictionary[" << reinterpret_cast<unsigned long>(&dictionary) << "]:"

std::ostream &operator<<(std::ostream &ostream, 
   const pdfio::pdf1_0::Dictionary &dictionary)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   if(ostream << "<<")
   {
      auto keys = dictionary.keys();
      while(ostream && !keys.empty())
      {
         if(ostream << *keys.begin())
         {
            if(ostream << ' ')
            {
               if(ostream << dictionary.get(*keys.begin()))
               {
                  keys.erase(keys.begin());
               }
            }
         }
      }
      if(ostream)
      {
         if(!(ostream << ">>"))
         {
            
         }
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return ostream;
}
