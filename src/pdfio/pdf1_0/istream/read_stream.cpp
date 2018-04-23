#include "read_stream.h"

#include "pdfio/log.h"
#include "read_dictionary.h"
#include "read_name.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << \
  reinterpret_cast<unsigned long>(&istream) << "],pdfStream[" << \
  reinterpret_cast<unsigned long>(&pdfStream) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdf1_0::Stream &pdfStream)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   pdfStream.prepare4Reading();
   if(istream >> static_cast<pdf1_0::Dictionary &>(pdfStream))
   {
      if(pdfStream.contains(pdf1_0::Name("Length")))
      {
         std::string buffer;
         if(istream >> buffer)
         {
            if(buffer == "stream")
            {
               while(istream.peek() == '\n' || istream.peek() == '\r')
               {
                  static_cast<void>(istream.get());
               }
               if(istream.good())
               {
                  auto streamPos = istream.tellg();
                  if(istream.seekg(pdfStream.length(), 
                     std::ios_base::cur))
                  {
                     if(istream >> buffer)
                     {
                        if(buffer == "endstream")
                        {
                           const bool isEof = istream.eof();
                           if(isEof)
                           {
                              istream.clear();
                           }
                           auto endOfStreamPos = istream.tellg();
                           char *streamData = 
                              new char[pdfStream.length()];
                           if(istream.seekg(streamPos))
                           {
                              if(istream.read(streamData, 
                                 pdfStream.length()))
                              {
                                 pdfStream.data().append(streamData, 
                                    pdfStream.length());
                                 if(!isEof)
                                 {
                                    istream.seekg(endOfStreamPos);
                                    if(!istream && !istream.eof())
                                    {
                                       LOG_ERROR(LOG_PREFIX << 
                                          "failed to seek after"
                                          " \"endstream\"\n");
                                    }
                                 }
                              }
                              else
                              {
                                 LOG_ERROR(LOG_PREFIX << 
                                 "failed to read stream data\n");
                              }
                           }
                           else
                           {
                              LOG_ERROR(LOG_PREFIX << 
                                 "failed to seek to the stream data\n");
                           }
                           delete [] streamData;
                        }
                        else
                        {
                           LOG_ERROR(LOG_PREFIX << 
                              "\"endstream\" is expected but got:" << 
                              buffer << "\n");
                           istream.setstate(std::ios_base::failbit);
                        }
                     }
                     else
                     {
                        LOG_ERROR(LOG_PREFIX << 
                           "failed to read \"endstream\"\n");
                     }
                  }
                  else
                  {
                     LOG_ERROR(LOG_PREFIX << 
                        "failed to seek to the end of the stream\n");
                  }
               }
               else
               {
                  LOG_ERROR(LOG_PREFIX << "something went wrong\n");
                   istream.setstate(std::ios_base::failbit);
               }
            }
            else
            {
               LOG_ERROR(LOG_PREFIX << 
                  "\"stream\" is expected but got:" << buffer << "\n");
               istream.setstate(std::ios_base::failbit);
            }
         }
         else
         {
            LOG_ERROR(LOG_PREFIX << "failed to read \"stream\"\n");
         }
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "\"Length\" is not found\n");
         istream.setstate(std::ios_base::failbit);
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << \
  reinterpret_cast<unsigned long>(&istream) << "],filter[" << \
  reinterpret_cast<unsigned long>(&filter) << "]:"

std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::Stream::Filter &filter)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   istream >> filter.name_;
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX
