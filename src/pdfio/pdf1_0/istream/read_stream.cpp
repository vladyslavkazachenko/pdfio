#include "read_stream.h"

#include <sstream>

#include "read_dictionary.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::Stream &pdfStream)
{
	if(istream >> static_cast<pdf1_0::Dictionary &>(pdfStream))
	{
		if(pdfStream.contains(pdf1_0::Name("Length")))
		{
			std::string buffer;
			if(istream >> buffer)
			{
				if(buffer == "stream")
				{
					if(istream.good())
					{
						auto streamPos = istream.tellg();
						if(istream.seekg(static_cast<pdf1_0::Dictionary &>(pdfStream).get<pdf1_0::Integer>(pdf1_0::Name("Length")), std::ios_base::cur))
						{
							if(istream >> buffer)
							{
								if(buffer == "endstream")
								{
									istream.clear();
									char *streamData = new char[static_cast<pdf1_0::Dictionary &>(pdfStream).get<pdf1_0::Integer>(pdf1_0::Name("Length"))];
									auto newStreamPos = istream.tellg();
									if(istream.seekg(streamPos))
									{
										if(istream.read(streamData, static_cast<pdf1_0::Dictionary &>(pdfStream).get<pdf1_0::Integer>(pdf1_0::Name("Length"))))
										{
											if(!pdfStream.iostream().write(streamData, static_cast<pdf1_0::Dictionary &>(pdfStream).get<pdf1_0::Integer>(pdf1_0::Name("Length"))))
											{
												istream.setstate(std::ios_base::failbit);
											}
											else
											{
												if(!istream.seekg(newStreamPos))
												{
													istream.setstate(std::ios_base::failbit);
												}
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
									delete [] streamData;
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
			istream.setstate(std::ios_base::failbit);
		}
	}
	return istream;
}