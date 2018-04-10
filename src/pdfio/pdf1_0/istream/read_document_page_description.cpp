#include "read_document_page_description.h"

#include <vector>
#include <sstream>

namespace pdf1_0 = pdfio::pdf1_0;

namespace
{
	enum class Cmd
	{
		kMove,
		kLine,
		kStroke,
		kWidth,
		kRectangle,
		kFill,
		kFillAndStroke,
		kCloseFillAndStroke,
		kCurve,
		kRgbFill,
		kRgbStroke,
		kDash,
		kGrayFill,
		kClip,
		kSave,
		kRestore,
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
		if(str == "re")
		{
			return Cmd::kRectangle;
		}
		if(str == "B")
		{
			return Cmd::kFillAndStroke;
		}
		if(str == "b")
		{
			return Cmd::kCloseFillAndStroke;
		}
		if(str == "c")
		{
			return Cmd::kCurve;
		}
		if(str == "rg")
		{
			return Cmd::kRgbFill;
		}
		if(str == "RG")
		{
			return Cmd::kRgbStroke;
		}
		if(str == "d")
		{
			return Cmd::kDash;
		}
		if(str == "g")
		{
			return Cmd::kGrayFill;
		}
		if(str == "W")
		{
			return Cmd::kClip;
		}
		if(str == "q")
		{
			return Cmd::kSave;
		}
		if(str == "Q")
		{
			return Cmd::kRestore;
		}
		return Cmd::kUnknown;
	}
}

std::istream &operator>>(std::istream &istream, pdf1_0::DocumentPageDescription &description)
{
	std::vector<std::string> tokens;
	std::string token;
	while(!istream.eof())
	{
		std::skipws(istream);
		char ch;
		istream >> std::skipws >> ch;
		istream.unget();
		if(ch == '%')
		{
			tokens.clear();
			char buffer[256];
			istream.getline(buffer, 256, '\n');
			continue;
		}
		if(ch == '[')
		{
			tokens.clear();
			static_cast<void>(istream.get());
			char cc;
			std::string s1;
			while((istream >> cc) && cc != ']')
			{
				s1 += cc;
				s1 += " ";
			}
			std::stringstream ss(s1);
			while(ss)
			{
				std::string s;
				if(ss >> s)
				{
					tokens.push_back(s);
				}
			}
			continue;
		}
		if(istream >> token)
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
			case Cmd::kRectangle:
				if(tokens.size() >= 4)
				{
					std::stringstream ssh(*(tokens.rbegin()));
					pdf1_0::Real h;
					if(ssh >> h)
					{
						std::stringstream ssw(*(tokens.rbegin() + 1));
						pdf1_0::Real w;
						if(ssw >> w)
						{
							std::stringstream ssy(*(tokens.rbegin() + 2));
							pdf1_0::Real y;
							if(ssy >> y)
							{
								std::stringstream ssx(*(tokens.rbegin() + 3));
								pdf1_0::Real x;
								if(ssx >> x)
								{
									description.rectangle(x, y, w, h);
								}
							}
						}
					}
				}
				tokens.clear();
				break;
			case Cmd::kFill:
				description.fill();
				tokens.clear();
				break;
			case Cmd::kFillAndStroke:
				description.fillAndStroke();
				tokens.clear();
				break;
			case Cmd::kCloseFillAndStroke:
				description.closepathFillAndStroke();
				tokens.clear();
				break;
			case Cmd::kCurve:
				if(tokens.size() >= 6)
				{
					std::stringstream ssy3(*(tokens.rbegin()));
					pdf1_0::Integer y3;
					if(ssy3 >> y3)
					{
						std::stringstream ssx3(*(tokens.rbegin() + 1));
						pdf1_0::Integer x3;
						if(ssx3 >> x3)
						{
							std::stringstream ssy2(*(tokens.rbegin() + 2));
							pdf1_0::Integer y2;
							if(ssy2 >> y2)
							{
								std::stringstream ssx2(*(tokens.rbegin() + 3));
								pdf1_0::Integer x2;
								if(ssx2 >> x2)
								{
									std::stringstream ssy1(*(tokens.rbegin() + 4));
									pdf1_0::Integer y1;
									if(ssy1 >> y1)
									{
										std::stringstream ssx1(*(tokens.rbegin() + 5));
										pdf1_0::Integer x1;
										if(ssx1 >> x1)
										{
											description.curve(x1, y1, x2, y2, x3, y3);
										}
									}
								}
							}
						}
					}
				}
				tokens.clear();
				break;
			case Cmd::kRgbFill:
				if(tokens.size() >= 3)
				{
					std::stringstream ssb(*(tokens.rbegin()));
					double b;
					if(ssb >> b)
					{
						std::stringstream ssg(*(tokens.rbegin() + 1));
						double g;
						if(ssg >> g)
						{
							std::stringstream ssr(*(tokens.rbegin() + 2));
							double r;
							if(ssr >> r)
							{
								description.setrgbcolorFill(r, g, b);
							}
						}
					}
				}
				tokens.clear();
				break;
			case Cmd::kRgbStroke:
				if(tokens.size() >= 3)
				{
					std::stringstream ssb(*(tokens.rbegin()));
					double b;
					if(ssb >> b)
					{
						std::stringstream ssg(*(tokens.rbegin() + 1));
						double g;
						if(ssg >> g)
						{
							std::stringstream ssr(*(tokens.rbegin() + 2));
							double r;
							if(ssr >> r)
							{
								description.setrgbcolorStroke(r, g, b);
							}
						}
					}
				}
				tokens.clear();
				break;
			case Cmd::kDash:
				if(tokens.size() >= 1)
				{
					std::stringstream ssp(*(tokens.rbegin()));
					pdf1_0::Integer p;
					if(ssp >> p)
					{
						tokens.pop_back();
						std::vector<pdf1_0::Integer> array;
						for(auto i : tokens)
						{
							std::stringstream ssa(i);
							pdf1_0::Integer a;
							if(ssa >> a)
							{
								array.push_back(a);
							}
						}
						description.setdash(p, array);
					}
				}
				tokens.clear();
				break;
			case Cmd::kGrayFill:
				if(tokens.size() >= 1)
				{
					std::stringstream ssgray(*(tokens.rbegin()));
					double gray;
					if(ssgray >> gray)
					{
						description.setgrayFill(gray);
					}
				}
				tokens.clear();
				break;
			case Cmd::kClip:
				description.clip();
				tokens.clear();
				break;
			case Cmd::kSave:
				description.save();
				tokens.clear();
				break;
			case Cmd::kRestore:
				description.restore();
				tokens.clear();
				break;
			default:
				tokens.push_back(token);
			}
		}
	}
	if(!istream.fail())
	{
		istream.clear();
	}
	return istream;
}