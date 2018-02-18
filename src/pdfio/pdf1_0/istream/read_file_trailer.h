#pragma once

#include <iostream>

#include "pdfio/pdf1_0/file_trailer.h"
#include "read_dictionary.h"

namespace pdf1_0 = pdfio::pdf1_0;
/*! \brief Reads the fileTrailer from the istream*/
std::istream &operator>>(std::istream &istream, pdf1_0::FileTrailer &fileTrailer)
{
	std::string buffer;
	if(istream >> buffer)
	{
		if(buffer == "trailer")
		{
			if(istream >> fileTrailer.dictionary())
			{
				if(fileTrailer.dictionary().contains(pdf1_0::Name("Size")) && 
					fileTrailer.dictionary().contains(pdf1_0::Name("Root")))
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
										std::cerr << __PRETTY_FUNCTION__ << ":string is not \"%%OEF\"\n";
										istream.setstate(std::ios_base::failbit);
									}
								}
								else
								{
									std::cerr << __PRETTY_FUNCTION__ << ":failed to read eof\n";
								}
							}
							else
							{
								std::cerr << __PRETTY_FUNCTION__ << ":failed to read xref offset\n";
							}
						}
						else
						{
							std::cerr << __PRETTY_FUNCTION__ << ":string is not \"startxref\"\n";
							istream.setstate(std::ios_base::failbit);
						}
					}
					else
					{
						std::cerr << __PRETTY_FUNCTION__ << ":failed to read \"startxref\"\n";
						istream.setstate(std::ios_base::failbit);
					}
				}
				else
				{
					if(!fileTrailer.dictionary().contains(pdf1_0::Name("Size")))
					{
						std::cerr << __PRETTY_FUNCTION__ << ":\"Size\" is not found\n";
					}
					else
					{
						std::cerr << __PRETTY_FUNCTION__ << ":\"Root\" is not found\n";
					}
					istream.setstate(std::ios_base::failbit);
				}
			}
			else
			{
				std::cerr << __PRETTY_FUNCTION__ << ":failed to read dictionary\n";
			}
		}
		else
		{
			std::cerr << __PRETTY_FUNCTION__ << ":string is not \"trailer\"\n";
			istream.setstate(std::ios_base::failbit);
		}
	}
	else
	{
		std::cerr << __PRETTY_FUNCTION__ << ":failed to read \"trailer\"\n";
	}
	return istream;
}