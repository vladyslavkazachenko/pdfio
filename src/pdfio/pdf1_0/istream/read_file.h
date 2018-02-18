#pragma once

#include <iostream>
#include <algorithm>
#include <sstream>

#include "pdfio/pdf1_0/file.h"
#include "read_file_header.h"
#include "read_file_version.h"

namespace pdf1_0 = pdfio::pdf1_0;
/*! \brief Reads the file from the istream*/
std::istream &operator>>(std::istream &istream, pdf1_0::File &file)
{
	if(istream >> file.header())
	{
		if(istream.peek() == '\n' || istream.peek() == '\r')
		{
			if(istream.seekg(1, std::ios_base::cur))
			{
				file.latestVersion().beginOffset() = istream.tellg();
				if(istream.seekg(-1, std::ios_base::end))
				{
					if(istream.peek() == '\n')
					{
						if(istream.seekg(-1, std::ios_base::cur))
						{
							if(istream.peek() == '\r')
							{
								istream.seekg(-1, std::ios_base::cur);
							}
							std::string eof;
							while(istream && istream.peek() != '\n')
							{
								eof += istream.peek();
								istream.seekg(-1, std::ios_base::cur);
							}
							if(istream)
							{
								std::reverse(std::begin(eof), std::end(eof));
								if(eof == "%%EOF")
								{
									istream.seekg(-1, std::ios_base::cur);
									std::string xrefOffset;
									while(istream && istream.peek() != '\n')
									{
										xrefOffset += istream.peek();
										istream.seekg(-1, std::ios_base::cur);
									}
									if(istream)
									{
										std::reverse(std::begin(xrefOffset), std::end(xrefOffset));
										std::stringstream ss(xrefOffset);
										std::size_t offset;
										if(ss >> offset)
										{
											if(istream.seekg(offset))
											{
												if(!(istream >> file.latestVersion()))
												{
													std::cerr << __PRETTY_FUNCTION__ << ":failed to read latest version\n";
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
				
			}
		}
		else
		{
			
		}
	}
	else
	{
		std::cerr << "failed to read header\n";
	}
	return istream;
}