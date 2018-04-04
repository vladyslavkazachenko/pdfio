#include "read_file_structure.h"

#include <string>
#include <cassert>

#include "pdfio/log.h"
#include "read_integer.h"
#include "read_dictionary.h"
#include "pdfio/pdf1_0/istream/read_file_structure.h"

namespace pdf1_7 = pdfio::pdf1_7;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
	":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
	"],fileStruct[" << reinterpret_cast<unsigned long>(&fileStruct) << "]:"

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

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
	":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
	"],fileStruct[" << reinterpret_cast<unsigned long>(&fileStruct) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_7::FileStructure &fileStruct)
{
	LOG_DEBUG(LOG_PREFIX << "enter\n");
	if(istream.seekg(-1, std::ios_base::end))
	{
		if(istream.peek() == '\n' || istream.peek() == '\r')
		{
			LOG_DEBUG(LOG_PREFIX << "skipping character " << istream.peek() << "\n");
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
				LOG_DEBUG(LOG_PREFIX << "skipping character " << istream.peek() << "\n");
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
						LOG_DEBUG(LOG_PREFIX << "skipping character " << istream.peek() << "\n");
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
						LOG_DEBUG(LOG_PREFIX << "skipping character " << istream.peek() << "\n");
						istream.seekg(-1, std::ios_base::cur);
					}
					if(istream)
					{
						pdf1_7::Integer lastXrefOffset;
						if(istream >> lastXrefOffset)
						{
							LOG_DEBUG(LOG_PREFIX << "last xref offset " << lastXrefOffset << "\n");
							istream.seekg(int(lastXrefOffset));
							pdf1_0::FileStructure::XrefSection xrefSection;
							if(istream >> xrefSection)
							{
								pdf1_7::FileStructure::Trailer trailer;
								if(istream >> trailer)
								{
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
	else
	{
		LOG_ERROR(LOG_PREFIX << "failed to seek to the last character offset: stream state " << 
			istream.rdstate() << "\n");
	}
	LOG_DEBUG(LOG_PREFIX << "leave\n");
	return istream;
}

#undef LOG_PREFIX