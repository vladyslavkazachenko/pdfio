#include "write_indirect_reference.h"

#include "pdfio/log.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&ostream) << \
   "],indirRef[" << reinterpret_cast<unsigned long>(&indirRef) << "]:"
   
std::ostream &operator<<(std::ostream &ostream, 
   const pdf1_0::IndirectReference &indirRef)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   if(ostream << indirRef.objectNumber())
   {
      if(ostream << " ")
      {
         if(ostream << indirRef.generationNumber())
         {
            if(!(ostream << " R"))
            {
               
            }
         }
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return ostream;
}
