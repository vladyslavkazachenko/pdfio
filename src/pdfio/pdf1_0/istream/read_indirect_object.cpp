#include "read_indirect_object.h"

#include "pdfio/read_generic_object.h"
#include "pdfio/log.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&istream) << "],indirectObject[" << \
   reinterpret_cast<unsigned long>(&indirectObject) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_0::IndirectObject &indirectObject)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   if(istream >> indirectObject.objectNumber())
   {
      LOG_DEBUG(LOG_PREFIX << "object number is " << 
         indirectObject.objectNumber() << "\n");
      if(istream >> indirectObject.generationNumber())
      {
         LOG_DEBUG(LOG_PREFIX << "generation number is " << 
            indirectObject.generationNumber() << "\n");
         while(istream && std::isspace(istream.peek()))
         {
            static_cast<void>(istream.get());
         }
         char tmp[4] = {'\0', '\0', '\0', '\0'};
         if(istream.read(tmp, 3))
         {
            std::string buffer(tmp);
            if(buffer == "obj")
            {
               if(istream >> indirectObject.get())
               {
                  if(istream >> buffer)
                  {
                     if(buffer != "endobj")
                     {
                        LOG_ERROR(LOG_PREFIX << 
                           "\"endobj\" is expected but got:" << 
                           buffer << "\n");
                        istream.setstate(std::ios_base::failbit);
                     }
                  }
               }
               else
               {
                  LOG_ERROR(LOG_PREFIX << 
                     "failed to read object, stream state is " << 
                     istream.rdstate() << "\n");
               }
            }
            else
            {
               LOG_ERROR(LOG_PREFIX << "\"obj\" is expected but got:" << 
                  buffer << "\n");
               istream.setstate(std::ios_base::failbit);
            }
         }
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX
