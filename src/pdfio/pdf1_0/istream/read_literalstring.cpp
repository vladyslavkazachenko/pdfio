#include "read_literalstring.h"

#include "pdfio/log.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
  "],literalString[" << reinterpret_cast<unsigned long>(&literalString) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_0::LiteralString &literalString)
{
   LOG_DEBUG(LOG_PREFIX << "entry\n");
   char ch;
   if(istream >> ch)
   {
      LOG_DEBUG(LOG_PREFIX << "1st delimiter is " << static_cast<int>(ch) << "\n");
      if(ch == '(')
      {
         int counter = 1;
         std::string buffer;
         while(istream && (counter > 0))
         {
            ch = istream.get();
            if(istream)
            {
               LOG_DEBUG(LOG_PREFIX << "character is " << static_cast<int>(ch) << "\n");
               if(ch == ')')
               {
                  --counter;
                  if(!counter)
                  {
                     literalString = buffer;
                  }
                  else
                  {
                     buffer += ch;
                  }
               }
               else
               {
                  buffer += ch;
                  if(ch == '(')
                  {
                     ++counter;
                  }
               }
               
            }
            else
            {
               LOG_ERROR(LOG_PREFIX << "failed to read character, buffer " << buffer << "\n");
            }
         }
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "invalid 1st delimiter: " << static_cast<int>(ch) << "\n");
			istream.setstate(std::ios_base::failbit);
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}