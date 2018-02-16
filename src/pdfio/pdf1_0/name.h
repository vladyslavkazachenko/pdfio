#pragma once

#include <string>

namespace pdfio
{
	
namespace pdf1_0
{
	/*! \brief PDF name object.
	 */
	class Name
	{
	public:
		Name() = default;
		
		inline Name(const std::string &value)
		: value_(value)
		{
			
		}
		
		inline bool operator==(const std::string &value)
		{
			return value_ == value;
		}
		
		inline bool operator==(const Name &other)
		{
			return value_ == other.value_;
		}
		
	private:
		std::string value_;
	};
}
	
}