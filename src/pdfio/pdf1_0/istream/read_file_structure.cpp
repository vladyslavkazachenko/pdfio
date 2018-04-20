#include "read_file_structure.h"

#include <cassert>

#include "pdfio/log.h"
#include "read_dictionary.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
  "],xrefEntry[" << reinterpret_cast<unsigned long>(&xrefEntry) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_0::FileStructure::XrefEntry &xrefEntry)
{
   if(istream >> xrefEntry.offset_)
   {
      if(istream >> xrefEntry.generation_)
      {
         char inUseFlag;
         if(istream >> inUseFlag)
         {
            if(inUseFlag == 'n')
            {
               xrefEntry.inUseFlag_ = true;
            }
            else
            {
               if(inUseFlag == 'f')
               {
                  xrefEntry.inUseFlag_ = false;
               }
               else
               {
                  LOG_ERROR(LOG_PREFIX << "invalid in use flag: " << std::hex << std::showbase << 
                     static_cast<int>(inUseFlag) << "\n");
                  istream.setstate(std::ios_base::failbit);
               }
            }
         }
         else
         {
            LOG_ERROR(LOG_PREFIX << "failed to read in use flag: stream state " << istream.rdstate() << "\n");
         }
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "failed to read generation: stream state " << istream.rdstate() << "\n");
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "failed to read offset: stream state " << istream.rdstate() << "\n");
   }
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
  "],xrefSubsection[" << reinterpret_cast<unsigned long>(&xrefSubsection) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdf1_0::FileStructure::XrefSubsection &xrefSubsection)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   if(istream >> xrefSubsection.firstObjectNumber_)
   {
      LOG_DEBUG(LOG_PREFIX << "1st object " << xrefSubsection.firstObjectNumber_ << "\n");
      pdf1_0::Integer entryNumber;
      if(istream >> entryNumber)
      {
         LOG_DEBUG(LOG_PREFIX << "entry number " << entryNumber << "\n");
         for(auto i = 0; i < entryNumber; ++i)
         {
            pdf1_0::FileStructure::XrefEntry entry;
            if(istream >> entry)
            {
               xrefSubsection.entries_.push_back(entry);
            }
         }
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
   "],xrefSection[" << reinterpret_cast<unsigned long>(&xrefSection) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_0::FileStructure::XrefSection &xrefSection)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   auto lastStreamPos = istream.tellg();
   std::string xrefLine;
   if(istream >> xrefLine)
   {
      LOG_DEBUG(LOG_PREFIX << "xref line is " << xrefLine << "\n");
      if(xrefLine == "xref")
      {
         lastStreamPos = istream.tellg();
         pdf1_0::FileStructure::XrefSubsection subsection;
         while(istream >> subsection)
         {
            lastStreamPos = istream.tellg();
            if(!xrefSection.add(subsection))
            {
               istream.setstate(std::ios_base::failbit);
            }
         }
         if(!xrefSection.subsections().empty())
         {
         istream.clear();
         istream.seekg(lastStreamPos);
         }
      }
      else
      {
         istream.setstate(std::ios_base::failbit);
      }
   }
   else
   {
      
      LOG_ERROR(LOG_PREFIX << "failed to read xref: stream state " << istream.rdstate() << "\n");
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
   "],trailer[" << reinterpret_cast<unsigned long>(&trailer) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_0::FileStructure::Trailer &trailer)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   trailer.prepare4Reading();
   std::string buffer;
   if(istream >> buffer)
   {
      LOG_DEBUG(LOG_PREFIX << "trailer line is " << buffer << "\n");
      if(buffer == "trailer")
      {
         if(istream >> static_cast<pdf1_0::Dictionary &>(trailer))
         {
            if(!trailer.contains(pdf1_0::Name("Size")))
            {
               if(!trailer.contains(pdf1_0::Name("Size")))
               {
                  LOG_ERROR(LOG_PREFIX << "\"Size\" is not found\n");
               }
               istream.setstate(std::ios_base::failbit);
            }
         }
         else
         {
            LOG_ERROR(LOG_PREFIX << "failed to read dictionary: stream state " << 
               istream.rdstate() << "\n");
         }
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "invalid trailer line: " << buffer << "\n");
         istream.setstate(std::ios_base::failbit);
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "failed to read trailer line: stream state " << 
         istream.rdstate() << "\n");
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
  "],fileStruct[" << reinterpret_cast<unsigned long>(&fileStruct) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_0::FileStructure &fileStruct)
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
                  LOG_ERROR(LOG_PREFIX << "failed to seek to the two before last character offset: "
                     "stream state " << istream.rdstate() << "\n");
               }
            }
         }
         else
         {
            LOG_ERROR(LOG_PREFIX << "failed to seek to the one before last character offset: "
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
               if(eofLine != "%%EOF")
               {
                  LOG_ERROR(LOG_PREFIX << "invalid eof line: " << eofLine << "\n");
                  istream.setstate(std::ios_base::failbit);
               }
            }
            else
            {
               LOG_ERROR(LOG_PREFIX << "failed to read eof line: stream state " << 
                  istream.rdstate() << "\n");
            }
            if(istream)
            {
               assert(istream.seekg(pos));
               if(istream.peek() == '\n' || istream.peek() == '\r')
               {
                  if(istream.seekg(-1, std::ios_base::cur))
                  {
                     if(istream.peek() == '\r')
                     {
                        if(!(istream.seekg(-1, std::ios_base::cur)))
                        {
                           LOG_ERROR(LOG_PREFIX << "failed to seek to two before last character " 
                              "offset: stream state " << istream.rdstate() << "\n");
                        }
                     }
                  }
                  else
                  {
                     LOG_ERROR(LOG_PREFIX << "failed to seek to one before last character offset: "
                        "stream state " << istream.rdstate() << "\n");
                  }
               }
               while(istream && istream.peek() != '\n' && istream.peek() != '\r')
               {
                  istream.seekg(-1, std::ios_base::cur);
               }
               if(istream)
               {
                  pdf1_0::Integer lastXrefOffset;
                  if(istream >> lastXrefOffset)
                  {
                     auto xrefOffset = lastXrefOffset;
                     while(xrefOffset != -1)
                     {
                        istream.seekg(int(xrefOffset));
                        xrefOffset = -1;
                        while(std::isspace(istream.peek()))
                        {
                           static_cast<void>(istream.get());
                        }
                        pos = istream.tellg();
                        pdf1_0::FileStructure::XrefSection xrefSection;
                        if(istream >> xrefSection)
                        {
                           pdf1_0::FileStructure::Trailer trailer;
                           if(istream >> trailer)
                           {
                              pdf1_0::FileStructure::Version version;
                              version.xrefSection_ = xrefSection;
                              version.trailer_ = trailer;
                              fileStruct.versions_.insert(std::begin(fileStruct.versions_), version);
                              if(trailer.hasPrev())
                              {
                                 xrefOffset = trailer.prev();
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
      LOG_ERROR(LOG_PREFIX << "failed to seek to the last character offset: stream state " << 
         istream.rdstate() << "\n");
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX
