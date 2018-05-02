#include "read_destination.h"

#include "pdfio/log.h"

#include "read_indirect_reference.h"
#include "read_name.h"

namespace pdf1_4 = pdfio::pdf1_4;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << \
  reinterpret_cast<unsigned long>(&istream) << \
  "],destination[" << reinterpret_cast<unsigned long>(&destination) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdf1_4::Destination &destination)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   char ch;
   if(istream >> ch)
   {
      if(ch == '[')
      {
         if(istream >> destination.fit().page_)
         {
            pdf1_4::Name type;
            if(istream >> type)
            {
               if(type == "Fit")
               {
                  destination.type() = pdf1_4::Destination::Type::kFit;
                  if(istream >> ch)
                  {
                     if(ch != ']')
                     {
                        
                     }
                  }
               }
            }   
         }
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}
