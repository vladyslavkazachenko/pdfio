#include "read_dictionary.h"

#include "read_name.h"
#include "pdfio/pdf1_0/generic_object_type.h"
#include "read_generic_object.h"
#include "pdfio/log.h"

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
    LOG_DEBUG(LOG_PREFIX << "skipping space character:" << std::hex << std::showbase << istream.get() << "\n");
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
                LOG_ERROR(LOG_PREFIX << "failed to read value for key " << std::string(name) << "\n");
              }
            }
            else
            {
              LOG_ERROR(LOG_PREFIX << "unknown key " << std::string(name) << "\n");
              istream.setstate(std::ios_base::failbit);
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
            if(istream >> buffer)
            {
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
              LOG_ERROR(LOG_PREFIX << "failed to read 2nd delimiter");
            }
          }
          else
          {
            LOG_ERROR(LOG_PREFIX << "cannot read 2nd delimiter, stream state is " << istream.rdstate());
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
      LOG_ERROR(LOG_PREFIX << "failed to read 1st delimiter");
    }
  }
  else
  {
    LOG_ERROR(LOG_PREFIX << "cannot read 1st delimiter, stream state is " << istream.rdstate());
  }
  LOG_DEBUG(LOG_PREFIX << "leave\n");
  return istream;
}