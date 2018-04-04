#include "read_file_structure.h"

#include "pdfio/log.h"
#include "read_integer.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
  "],xrefEntry[" << reinterpret_cast<unsigned long>(&xrefEntry) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_0::FileStructure::XrefEntry &xrefEntry)
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