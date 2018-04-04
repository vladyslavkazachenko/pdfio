#include "read_file_structure.h"

#include <string>

#include "read_integer.h"
#include "read_dictionary.h"
#include "pdfio/log.h"

namespace pdf1_7 = pdfio::pdf1_7;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
  "],xrefEntry[" << reinterpret_cast<unsigned long>(&xrefEntry) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_7::FileStructure::XrefEntry &xrefEntry)
{
  LOG_DEBUG(LOG_PREFIX << "enter\n");
  if(istream >> xrefEntry.offset_)
  {
    if(istream >> xrefEntry.generation_)
    {
      char inUseFlag;
      if(istream >> inUseFlag)
      {
        LOG_DEBUG(LOG_PREFIX << "in use flag: " << inUseFlag << "\n");
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
  LOG_DEBUG(LOG_PREFIX << "leave\n");
  return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
  "],xrefSubsection[" << reinterpret_cast<unsigned long>(&xrefSubsection) << "]:"

std::istream &operator>>(std::istream &istream, 
  pdf1_7::FileStructure::XrefSubsection &xrefSubsection)
{
  LOG_DEBUG(LOG_PREFIX << "enter\n");
  if(istream >> xrefSubsection.firstObjectNumber_)
  {
    LOG_DEBUG(LOG_PREFIX << "1st object " << xrefSubsection.firstObjectNumber_ << "\n");
    pdf1_7::Integer entryNumber;
    if(istream >> entryNumber)
    {
      LOG_DEBUG(LOG_PREFIX << "entry number " << entryNumber << "\n");
      for(auto i = 0; i < entryNumber; ++i)
      {
        pdf1_7::FileStructure::XrefEntry entry;
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

std::istream &operator>>(std::istream &istream, pdf1_7::FileStructure::XrefSection &xrefSection)
{
  std::string xrefLine;
  if(istream >> xrefLine)
  {
    if(xrefLine == "xref")
    {
      auto lastStreamPos = istream.tellg();
      pdf1_7::FileStructure::XrefSubsection subsection;
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
  return istream;
}

std::istream &operator>>(std::istream &istream, pdf1_7::FileStructure::Trailer &trailer)
{
  trailer.prepare4Reading();
  std::string buffer;
  if(istream >> buffer)
  {
    if(buffer == "trailer")
    {
      if(istream >> trailer.dictionary())
      {
        if(trailer.dictionary().contains(pdf1_0::Name("Size")))
        {
          if(istream >> buffer)
          {
            if(buffer == "startxref")
            {
              std::size_t xrefOffset;
              if(istream >> xrefOffset)
              {
                if(istream >> buffer)
                {
                  if(buffer != "%%EOF")
                  {
                    istream.setstate(std::ios_base::failbit);
                  }
                }
                else
                {
                  
                }
              }
              else
              {
                
              }
            }
            else
            {
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
          istream.setstate(std::ios_base::failbit);
        }
      }
      else
      {
        
      }
    }
    else
    {
      istream.setstate(std::ios_base::failbit);
    }
  }
  else
  {

  }
  return istream;
}
#include <iostream>
std::istream &operator>>(std::istream &istream, pdf1_7::FileStructure &fileStruct)
{
  istream.seekg(-1, std::ios_base::end);
  if(istream.peek() == '\n' || istream.peek() == '\r')
  {std::cerr << "istream.peek1:" << istream.peek() << "\n";
    istream.seekg(-1, std::ios_base::cur);
    if(istream.peek() == '\r')
    {std::cerr << "istream.peek2:" << istream.peek() << "\n";
      istream.seekg(-1, std::ios_base::cur);
    }
    while(istream && istream.peek() != '\n' && istream.peek() != '\r')
    {std::cerr << "istream.peekx:" << istream.peek() << "\n";
      istream.seekg(-1, std::ios_base::cur);
    }
    if(istream)
    {
      auto pos = istream.tellg();
      std::string eofLine;
      if(istream >> eofLine)
      {std::cerr << "eofLine:" << eofLine << "\n";
        if(eofLine != "%%EOF")
        {
          istream.setstate(std::ios_base::failbit);
        }
      }
      if(istream)
      {
        istream.seekg(pos);
        if(istream.peek() == '\n' || istream.peek() == '\r')
        {std::cerr << "istream.peek3:" << istream.peek() << "\n";
          istream.seekg(-1, std::ios_base::cur);
          if(istream.peek() == '\r')
          {std::cerr << "istream.peek4:" << istream.peek() << "\n";
            istream.seekg(-1, std::ios_base::cur);
          }
          while(istream && istream.peek() != '\n' && istream.peek() != '\r')
          {std::cerr << "istream.peeky:" << istream.peek() << "\n";
            istream.seekg(-1, std::ios_base::cur);
          }
          if(istream)
          {
            /*pdf1_7::Integer*/int lastXrefOffset;
            if(istream >> lastXrefOffset)
            {std::cerr << "lastXrefOffset:" << lastXrefOffset << "\n";
            istream.seekg(lastXrefOffset);
            std::string bb; istream >> bb ; std::cerr << "bb=" << bb << "\n";istream.seekg(lastXrefOffset);
              pdf1_7::FileStructure::XrefSection xrefSection;
              if(istream >> xrefSection)
              {std::cerr << "yes1\n";
                pdf1_7::FileStructure::Trailer trailer;
                if(istream >> trailer)
                {std::cerr << "yes2\n";
                  pdf1_7::FileStructure::Version version;
                  version.xrefSection_ = xrefSection;
                  version.trailer_ = trailer;
                  fileStruct.versions_.push_back(version);
                }
              }
            }
          }
        }
      }
    }
  }
  return istream;
}