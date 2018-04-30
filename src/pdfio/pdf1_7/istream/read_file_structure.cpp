#include "read_file_structure.h"

#include <string>
#include <cassert>
#include <cstring>

#include "zlib.h"
#include "pdfio/log.h"
#include "read_dictionary.h"
#include "read_stream.h"
#include "pdfio/pdf1_0/istream/read_file_structure.h"
#include "pdfio/pdf1_7/istream/read_indirect_object.h"

namespace pdf1_7 = pdfio::pdf1_7;
namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&istream) << \
   "],xrefEntry[" << reinterpret_cast<unsigned long>(&xrefEntry) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdf1_7::FileStructure::XrefEntry &xrefEntry)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   int byteCounter = 0;
   pdf1_7::Integer type = 0;
   while(istream && byteCounter++ < std::get<0>(std::get<0>(xrefEntry)))
   {
      type <<= 1;
      type += istream.get();
   }      
   if(istream)
   {
      std::get<1>(xrefEntry) = 
         static_cast<pdf1_7::FileStructure::XrefEntryType>(type);
      byteCounter = 0;
      std::get<2>(xrefEntry) = 0;
      while(istream && byteCounter++ < std::get<1>(std::get<0>(xrefEntry)))
      {
         std::get<2>(xrefEntry) <<= 1;
         std::get<2>(xrefEntry) += istream.get();
      }
      if(istream)
      {
         byteCounter = 0;
         std::get<3>(xrefEntry) = 0;
         while(istream && byteCounter++ < std::get<2>(std::get<0>(xrefEntry)))
         {
            std::get<3>(xrefEntry) <<= 1;
            std::get<3>(xrefEntry) += istream.get();
         }
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&istream) << \
   "],subsection[" << reinterpret_cast<unsigned long>(&subsection) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_7::FileStructure::XrefSubsection &subsection)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   for(auto &entry : subsection.entries_)
   {
      if(!(istream >> entry))
      {
         break;
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&istream) << \
   "],xrefSection[" << reinterpret_cast<unsigned long>(&xrefSection) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_7::FileStructure::XrefSection &xrefSection)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   for(auto &subsection : xrefSection.subsections_)
   {
      if(!(istream >> subsection))
      {
         break;
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&istream) << \
   "],trailer[" << reinterpret_cast<unsigned long>(&trailer) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdf1_7::FileStructure::Trailer &trailer)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   trailer.prepare4Reading();
   istream >> static_cast<pdf1_0::FileStructure::Trailer &>(trailer);
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&istream) << \
   "],xrefStream[" << reinterpret_cast<unsigned long>(&xrefStream) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdf1_7::FileStructure::XrefStream &xrefStream)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   xrefStream.prepare4Reading();
   if(istream >> static_cast<pdf1_7::Dictionary &>(xrefStream))
   {
      if(xrefStream.contains(pdf1_0::Name("Length")))
      {
         std::string buffer;
         if(istream >> buffer)
         {
            if(buffer == "stream")
            {
               if(istream.good())
               {
                  while(std::isspace(istream.peek()))
                  {
                     static_cast<void>(istream.get());
                  }
                  auto streamPos = istream.tellg();
                  if(istream.seekg(xrefStream.get<pdf1_0::Integer>(
                     pdf1_0::Name("Length")), std::ios_base::cur))
                  {
                     if(istream >> buffer)
                     {
                        if(buffer == "endstream")
                        {
                           istream.clear();
                           auto streamLength = xrefStream.get<pdf1_0::Integer>(
                              pdf1_0::Name("Length"));
                           char *streamData = new char[streamLength];
                           auto newStreamPos = istream.tellg();
                           if(istream.seekg(streamPos))
                           {
                              if(istream.read(streamData, streamLength))
                              {
                                 xrefStream.data() = "";
                                 xrefStream.data().append(streamData, 
                                    streamLength);
                                 if(!istream.seekg(newStreamPos))
                                 {
                                    istream.setstate(std::ios_base::failbit);
                                 }
                              }
                              else
                              {
                                 LOG_ERROR(LOG_PREFIX << 
                                    "failed to read the stream data,"
                                    " stream state is " << 
                                    istream.rdstate() << "\n");
                                 istream.setstate(std::ios_base::failbit);
                              }
                           }
                           else
                           {
                              LOG_ERROR(LOG_PREFIX << 
                                 "failed to seek to the stream data,"
                                 " stream state is " << 
                                 istream.rdstate() << "\n");
                              istream.setstate(std::ios_base::failbit);
                           }
                           delete [] streamData;
                        }
                        else
                        {
                           LOG_ERROR(LOG_PREFIX << 
                              "invalid end of stream line:" << buffer << "\n");
                           istream.setstate(std::ios_base::failbit);
                        }
                     }
                     else
                     {
                        LOG_ERROR(LOG_PREFIX << "failed to read end of stream,"
                        " stream state is " << istream.rdstate() << "\n");
                        istream.setstate(std::ios_base::failbit);
                     }
                  }
                  else
                  {
                     LOG_ERROR(LOG_PREFIX << "failed to seek to end of stream,"
                        " stream state is " << istream.rdstate() << "\n");
                  }
               }
               else
               {
                  istream.setstate(std::ios_base::failbit);
               }
            }
            else
            {
               LOG_DEBUG(LOG_PREFIX << "invalid stream line is: " << buffer << 
                  "\n");
               istream.setstate(std::ios_base::failbit);
            }
         }
         else
         {
            LOG_ERROR(LOG_PREFIX << "failed to read stream line,"
               " stream state is " << istream.rdstate() << "\n");
            istream.setstate(std::ios_base::failbit);
         }
      }
      else
      {
         istream.setstate(std::ios_base::failbit);
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "failed to read dictionary\n");
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&istream) << \
   "],fileStruct[" << reinterpret_cast<unsigned long>(&fileStruct) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdf1_7::FileStructure &fileStruct)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   if(istream.seekg(-1, std::ios_base::end))
   {
      if(istream.peek() == '\n' || istream.peek() == '\r')
      {
         if(istream.seekg(-1, std::ios_base::cur))
         {
            if(istream.peek() == '\r')
            {
               if(!(istream.seekg(-1, std::ios_base::cur)))
               {
                  LOG_ERROR(LOG_PREFIX << 
                     "failed to seek to the two before last character offset: "
                     "stream state " << istream.rdstate() << "\n");
               }
            }
         }
         else
         {
            LOG_ERROR(LOG_PREFIX << 
               "failed to seek to the one before last character offset: "
               "stream state " << istream.rdstate() << "\n");
         }
      }
      if(istream)
      {
         while(istream && istream.peek() != '\n' && istream.peek() != '\r')
         {
            istream.seekg(-1, std::ios_base::cur);
         }
         if(istream)
         {
            auto pos = istream.tellg();
            std::string eofLine;
            if(istream >> eofLine)
            {
               LOG_DEBUG(LOG_PREFIX << "eof line: " << eofLine << "\n");
               if(eofLine != "%%EOF")
               {
                  LOG_ERROR(LOG_PREFIX << "invalid eof line: " << eofLine << 
                     "\n");
                  istream.setstate(std::ios_base::failbit);
               }
            }
            else
            {
               LOG_ERROR(LOG_PREFIX << 
                  "failed to read eof line: stream state " << 
                  istream.rdstate() << "\n");
            }
            if(istream)
            {
               assert(istream.seekg(pos));
               if(istream.peek() == '\n' || istream.peek() == '\r')
               {
                  LOG_DEBUG(LOG_PREFIX << "skipping character " << 
                     istream.peek() << "\n");
                  if(istream.seekg(-1, std::ios_base::cur))
                  {
                     if(istream.peek() == '\r')
                     {
                        if(!(istream.seekg(-1, std::ios_base::cur)))
                        {
                           LOG_ERROR(LOG_PREFIX << 
                              "failed to seek to two before last character "
                              "offset: stream state " << istream.rdstate() << 
                              "\n");
                        }
                     }
                  }
                  else
                  {
                     LOG_ERROR(LOG_PREFIX << 
                        "failed to seek to one before last character offset: "
                        "stream state " << istream.rdstate() << "\n");
                  }
               }
               while(istream && istream.peek() != '\n' && 
                  istream.peek() != '\r')
               {
                  istream.seekg(-1, std::ios_base::cur);
               }
               if(istream)
               {
                  pdf1_7::Integer lastXrefOffset;
                  if(istream >> lastXrefOffset)
                  {
                     auto xrefOffset = lastXrefOffset;
                     while(xrefOffset != -1)
                     {
                        istream.seekg(xrefOffset);
                        xrefOffset = -1;
                        while(std::isspace(istream.peek()))
                        {
                           static_cast<void>(istream.get());
                        }
                        pos = istream.tellg();
                        pdf1_0::FileStructure::XrefSection xrefSection;
                        if(istream >> xrefSection)
                        {
                           pdf1_7::FileStructure::Trailer trailer;
                           if(istream >> trailer)
                           {
                              pdf1_7::FileStructure::Version version;
                              version.xrefSection_ = xrefSection;
                              version.trailer_ = trailer;
                              fileStruct.versions_.insert(
                                 std::begin(fileStruct.versions_), version);
                              if(trailer.hasPrev())
                              {
                                 xrefOffset = trailer.prev();
                              }
                           }
                        }
                        else
                        {
                           istream.clear();
                           istream.seekg(pos);
                           pdf1_7::IndirectObject indirectObject;
                           indirectObject.set<
                              pdf1_7::FileStructure::XrefStream>();
                           if(istream >> indirectObject)
                           {
                              auto &xrefStream = indirectObject.get<
                                 pdf1_7::FileStructure::XrefStream>();
                              char c[1024];
                              memset(c, '\0', 1024);
                              z_stream zInfo;
                              zInfo.avail_in=  xrefStream.data().length();
                              zInfo.avail_out= 1024;
                              zInfo.next_in= (Bytef*)xrefStream.data().c_str();
                              zInfo.next_out= (Bytef *)c;
                              zInfo.zalloc = Z_NULL;
                              zInfo.zfree = Z_NULL;
                              if(inflateInit(&zInfo) != Z_OK)
                              {
                                 LOG_ERROR(LOG_PREFIX << 
                                    "inflateInit failed\n");
                              }
                              if(inflate(&zInfo, Z_FINISH) != Z_STREAM_END)
                              {
                                 LOG_ERROR(LOG_PREFIX << "inflate failed\n");
                              }
                              if(inflateEnd(&zInfo) != Z_OK)
                              {
                                 LOG_ERROR(LOG_PREFIX << "inflateEnd failed\n");
                              }
                              
                              //std::vector<char> bytes;
                              auto width = xrefStream.decodeParms().get<
                                 pdf1_7::Integer>(pdf1_7::FileStructure::
                                 XrefStream::kKeyColumns);
                              for(unsigned int i = 0; i < zInfo.total_out; 
                                 i += (width + 1))
                              {
                                 if(!i)
                                 {
                                    //bytes.push_back(c[i]);
                                    LOG_DEBUG(LOG_PREFIX << "offset=" << 
                                       c[i + 1] << "\n");
                                 }
                                 else
                                 {
                                    //bytes.push_back(c[i] + c[i - width - 1]);
                                    LOG_DEBUG(LOG_PREFIX << "offset=" << 
                                       c[i + 1] + c[i - width] << "\n");
                                 }
                              }
                              
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "failed to seek to the last character offset: "
         "stream state " << istream.rdstate() << "\n");
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX
