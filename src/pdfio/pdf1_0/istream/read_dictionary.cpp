#include "read_dictionary.h"

#include "read_name.h"
#include "pdfio/pdf1_0/generic_object_type.h"
#include "read_generic_object.h"
#include "pdfio/log.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::Dictionary &dictionary)
{
  LOG_DEBUG(__PRETTY_FUNCTION__ << ":dictionary[" << std::hex << std::showbase << 
    reinterpret_cast<unsigned long>(&dictionary) << "]:enter\n");
  std::string buffer;
  while(istream && std::isspace(istream.peek()))
  {
    LOG_DEBUG(__PRETTY_FUNCTION__ << ":dictionary[" << std::hex << std::showbase << 
    reinterpret_cast<unsigned long>(&dictionary) << "]:skipping space character:" << std::hex << std::showbase << 
    reinterpret_cast<int>(istream.get()) << "\n");
  }
  if(istream)
  {
    char tmp[3] = {0, 0, 0};
    if(istream.read(tmp, 2))
    {
      buffer = tmp;
      LOG_DEBUG(__PRETTY_FUNCTION__ << ":dictionary[" << std::hex << std::showbase << 
        reinterpret_cast<unsigned long>(&dictionary) << "]:1st delimiter is " << buffer << "\n");
    }
  }
  if(istream)
  {
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
          LOG_DEBUG(__PRETTY_FUNCTION__ << ":dictionary[" << std::hex << std::showbase << 
            reinterpret_cast<unsigned long>(&dictionary) << "]:key is " << std::string(name) << "\n");
          if(dictionary.contains(name))
          {
            if(istream >> dictionary.get(name))
            {
              keys.erase(name);
              streamPosition = istream.tellg();
            }
            else
            {
              std::cerr << "failed to read " << std::string(name) << "\n";
            }
          }
          else
          {
            std::cerr << __PRETTY_FUNCTION__ << ":unknown name " << std::string(name) << "\n" ;
            istream.setstate(std::ios_base::failbit);
          }
        }
        else
        {
          LOG_DEBUG(__PRETTY_FUNCTION__ << ":dictionary[" << std::hex << std::showbase << 
            reinterpret_cast<unsigned long>(&dictionary) << "]:token is not a name\n");
        }
      }
      istream.clear();
      if(istream.seekg(streamPosition))
      {
        if(istream >> buffer)
        {
          if(buffer != ">>")
          {
            std::cerr << __PRETTY_FUNCTION__ << ":failed to read second delimiter\n";
            istream.setstate(std::ios_base::failbit);
          }
          else
          {
            for(auto key : keys)
            {
              dictionary.remove(key);
            }
          }
        }
      }
    }
    else
    {
      std::cerr << __PRETTY_FUNCTION__ << ":invalid first delimiter\n";
      istream.setstate(std::ios_base::failbit);
    }
  }
  else
  {
    std::cerr << __PRETTY_FUNCTION__ << ":failed to read first delimiter\n";
  }
  LOG_DEBUG(__PRETTY_FUNCTION__ << ":dictionary[" << std::hex << std::showbase << 
    reinterpret_cast<unsigned long>(&dictionary) << "]:leave\n");
  return istream;
}