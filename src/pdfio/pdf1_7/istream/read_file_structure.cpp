#include "read_file_structure.h"

#include <string>

#include "read_integer.h"
#include "read_dictionary.h"

namespace pdf1_7 = pdfio::pdf1_7;

std::istream &operator>>(std::istream &istream, pdf1_7::FileStructure::XrefEntry &xrefEntry)
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
						istream.setstate(std::ios_base::failbit);
					}
				}
			}
		}
	}
	return istream;
}

std::istream &operator>>(std::istream &istream, 
	pdf1_7::FileStructure::XrefSubsection &xrefSubsection)
{
	if(istream >> xrefSubsection.firstObjectNumber_)
	{
		pdf1_7::Integer entryNumber;
		if(istream >> entryNumber)
		{
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