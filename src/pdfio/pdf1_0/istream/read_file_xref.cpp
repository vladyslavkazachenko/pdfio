#include "read_file_xref.h"

#include <iostream>

namespace pdf1_0 = pdfio::pdf1_0;

inline std::istream &operator>>(std::istream &istream, pdf1_0::FileXref::Entry &entry)
{
	if(istream >> entry.byteOffset())
	{
		if(istream >> entry.generationNumber())
		{
			char inUseFlag = 0;
			if(istream >> inUseFlag)
			{
				if(inUseFlag == 'n' || inUseFlag == 'f')
				{
					entry.isInUse() = (inUseFlag == 'n');
				}
				else
				{
					std::cerr << __PRETTY_FUNCTION__ << ":invalid in-use/free flag\n";
				}
			}
			else
			{
				std::cerr << __PRETTY_FUNCTION__ << ":failed to read in-use/free flag\n";
			}
		}
		else
		{
			std::cerr << __PRETTY_FUNCTION__ << ":failed to read generation number\n";
		}
	}
	return istream;
}

inline std::istream &operator>>(std::istream &istream, pdf1_0::FileXref::Subsection &subsection)
{
	if(istream >> subsection.objectNumber())
	{
		pdf1_0::Integer entriesNumber;
		if(istream >> entriesNumber)
		{
			for(auto entryCounter = 0; entryCounter < entriesNumber && istream; ++entryCounter)
			{
				pdf1_0::FileXref::Entry entry;
				if(istream >> entry)
				{
					subsection.entries().push_back(entry);
				}
			}
		}
	}
	return istream;
}

inline std::istream &operator>>(std::istream &istream, pdf1_0::FileXref::Section &section)
{
	auto streamPosition = istream.tellg();
	section.subsections().clear();
	while(istream)
	{
		pdf1_0::FileXref::Subsection subsection;
		if(istream >> subsection)
		{
			streamPosition = istream.tellg();
			section.subsections().push_back(subsection);
		}
	}
	if(!istream.bad())
	{
		istream.clear();
		istream.seekg(streamPosition);
	}
	else
	{
		std::cerr << __PRETTY_FUNCTION__ << ":failed to read subsection\n";
	}
	return istream;
}

std::istream &operator>>(std::istream &istream, pdf1_0::FileXref &fileXref)
{
	std::string buffer;
	if(istream >> buffer)
	{
		if(buffer == "xref")
		{
			if(!(istream >> fileXref.section()))
			{
				std::cerr << __PRETTY_FUNCTION__ << ":failed to read section\n";
			}
		}
		else
		{
			std::cerr << __PRETTY_FUNCTION__ << ":string is not \"xref\"\n";
			istream.setstate(std::ios_base::failbit);
		}
	}
	else
	{
		std::cerr << __PRETTY_FUNCTION__ << ":failed to read \"xref\"\n";
	}
	return istream;
}