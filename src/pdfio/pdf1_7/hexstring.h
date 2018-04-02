#pragma once

#include <string>

namespace pdfio
{
	
namespace pdf1_7
{
	
class HexString
{
public:
	inline operator std::string()
	{
		return value_;
	}
	inline operator std::string() const
	{
		return value_;
	}
	inline bool operator==(const std::string &value) const
	{
		return value_ == value;
	}
	inline HexString &operator=(const std::string &value)
	{
		value_ = value;
		return *this;
	}
private:
	std::string value_;
};
	
}
	
}