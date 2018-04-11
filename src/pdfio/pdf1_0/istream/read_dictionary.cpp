#include "read_dictionary.h"

#include "read_name.h"
#include "pdfio/pdf1_0/generic_object_type.h"
#include "pdfio/read_generic_object.h"
#include "pdfio/log.h"

std::istream &skipUnknownValue(std::istream &, int levelCounter = 0);

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
   "],dictionary[" << reinterpret_cast<unsigned long>(&dictionary) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_0::Dictionary &dictionary)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   std::string buffer;
   while(istream && std::isspace(istream.peek()))
   {
      LOG_DEBUG(LOG_PREFIX << "skipping space character:" << std::hex << std::showbase << istream.peek() << "\n");
      static_cast<void>(istream.get());
   }
   if(istream)
   {
      char tmp[3] = {0, 0, 0};
      if(istream.read(tmp, 2))
      {
         buffer = tmp;
         LOG_DEBUG(LOG_PREFIX << "1st delimiter is " << buffer << "\n");
         if(buffer == "<<")
         {
            auto streamPosition = istream.tellg();
            std::set<pdf1_0::Name> keys = dictionary.keys();
            while(istream)
            {
               streamPosition = istream.tellg();
               pdf1_0::Name name;
               if(istream >> name)
               {
                  LOG_DEBUG(LOG_PREFIX << "key is " << std::string(name) << "\n");
                  if(dictionary.contains(name))
                  {
                     if(istream >> dictionary.get(name))
                     {
                        keys.erase(name);
                        streamPosition = istream.tellg();
                     }
                     else
                     {
                        LOG_ERROR(LOG_PREFIX << "failed to read value for key " << 
                           std::string(name) << "\n");
                     }
                  }
                  else
                  {
                     LOG_ERROR(LOG_PREFIX << "unknown key " << std::string(name) << "\n");
                     skipUnknownValue(istream);
                  }
               }
               else
               {
                  LOG_DEBUG(LOG_PREFIX << "token is not a name\n");
                  istream.clear();
                  break;
               }
            }
            if(istream)
            {
               if(istream.seekg(streamPosition))
               {
                  while(istream && std::isspace(istream.peek()))
                  {
                     LOG_DEBUG(LOG_PREFIX << "skipping space character:" << std::hex << std::showbase << istream.peek() << "\n");
                     static_cast<void>(istream.get());
                  }
                  if(istream)
                  {
                     char tmp[3] = {0, 0, 0};
                     if(istream.read(tmp, 2))
                     {
                        buffer = tmp;
                        LOG_DEBUG(LOG_PREFIX << "2nd delimiter is " << buffer << "\n");
                        if(buffer != ">>")
                        {
                           LOG_ERROR(LOG_PREFIX << "invalid 2nd delimiter: " << buffer << "\n");
                           istream.setstate(std::ios_base::failbit);
                        }
                        else
                        {
                           for(auto key : keys)
                           {
                              LOG_DEBUG(LOG_PREFIX << "removing key " << std::string(key) << "\n");
                              dictionary.remove(key);
                           }
                        }
                     }
                     else
                     {
                        LOG_ERROR(LOG_PREFIX << "failed to read 2nd delimiter\n");
                     }
                  }
                  else
                  {
                     LOG_ERROR(LOG_PREFIX << "cannot read 2nd delimiter, stream state is " << 
                        istream.rdstate() << "\n");
                  }
               }
            }
         }
         else
         {
            LOG_ERROR(LOG_PREFIX << "invalid 1st delimiter: " << buffer << "\n");
            istream.setstate(std::ios_base::failbit);
         }
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "failed to read 1st delimiter\n");
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "cannot read 1st delimiter, stream state is " << istream.rdstate() << "\n");
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
   "]:"

std::istream &skipUnknownValue(std::istream &istream, int levelCounter)
{
   //LOG_DEBUG(LOG_PREFIX << "enter\n");
   //if(istream){LOG_DEBUG(LOG_PREFIX << "level=" << levelCounter << "," << char(istream.peek()) << "\n");};
   if(istream && istream.peek() == '<')
   {
      static_cast<void>(istream.get());
      if(istream && istream.peek() == '<')
      {
         static_cast<void>(istream.get());
         skipUnknownValue(istream, levelCounter + 1);
      }
   }
   if(istream && istream.peek() == '>')
   {
      static_cast<void>(istream.get());
      if(istream && istream.peek() == '>')
      {
         if(!levelCounter)
         {
            static_cast<void>(istream.unget());
           // LOG_DEBUG(LOG_PREFIX << "leave\n");
            return istream;
         }
         else
         {
            static_cast<void>(istream.get());
            //LOG_DEBUG(LOG_PREFIX << "leave\n");
            return istream;
         }
      }
   }
   if(istream && istream.peek() == '/' && !levelCounter)
   {
     // LOG_DEBUG(LOG_PREFIX << "leave\n");
      return istream;
   }
   else
   {
      if(istream)
      {
         istream.get();
         if(istream)
         {
            skipUnknownValue(istream, levelCounter);
         }
         else
         {
            istream.clear();
         }
      }
   }
  // LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX