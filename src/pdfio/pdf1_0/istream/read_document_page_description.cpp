#include "read_document_page_description.h"

#include <vector>
#include <sstream>

#include "read_integer.h"

namespace pdf1_0 = pdfio::pdf1_0;

namespace
{
	enum class Cmd
	{
		kMove,
		kLine,
		kStroke,
		kWidth,
		kUnknown,
	};
	
	Cmd String2Cmd(const std::string str)
	{
		if(str == "m")
		{
			return Cmd::kMove;
		}
		if(str == "l")
		{
			return Cmd::kLine;
		}
		if(str == "S")
		{
			return Cmd::kStroke;
		}
		if(str == "w")
		{
			return Cmd::kWidth;
		}
		return Cmd::kUnknown;
	}
}

std::istream &operator>>(std::istream &istream, pdf1_0::DocumentPageDescription &description)
{
	std::vector<std::string> tokens;
	std::string token;
	while(!istream.eof() && istream >> token)
	{
		switch(String2Cmd(token))
		{
		case Cmd::kMove:
			if(tokens.size() >= 2)
			{
				std::stringstream ssx(*(tokens.rbegin()));
				pdf1_0::Integer y;
				if(ssx >> y)
				{
					std::stringstream ssy(*(tokens.rbegin() + 1));
					pdf1_0::Integer x;
					if(ssy >> x)
					{
						description.moveto(x, y);
					}
				}
			}
			tokens.clear();
			break;
		case Cmd::kLine:
			if(tokens.size() >= 2)
			{
				std::stringstream ssx(*(tokens.rbegin()));
				pdf1_0::Integer y;
				if(ssx >> y)
				{
					std::stringstream ssy(*(tokens.rbegin() + 1));
					pdf1_0::Integer x;
					if(ssy >> x)
					{
						description.lineto(x, y);
					}
				}
			}
			tokens.clear();
			break;
		case Cmd::kStroke:
			description.stroke();
			tokens.clear();
			break;
		case Cmd::kWidth:
			if(tokens.size() >= 1)
			{
				std::stringstream ss(*(tokens.rbegin()));
				pdf1_0::Integer w;
				if(ss >> w)
				{
					description.setlinewidth(w);
				}
			}
			tokens.clear();
			break;
		default:
			tokens.push_back(token);
		}
	}
	if(!istream.fail())
	{
		istream.clear();
	}
	return istream;
}