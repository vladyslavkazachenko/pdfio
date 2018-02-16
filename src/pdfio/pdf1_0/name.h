#pragma once

#include <string>

namespace pdfio
{
	
namespace pdf1_0
{
	/*! \brief PDF name object.*/
	class Name
	{
	public:
		/*! \brief Default constructor*/
		Name() = default;
		/*! \brief Initializes name by std::string value*/
		inline explicit Name(const std::string &value)
		: value_(value)
		{
			
		}
		/*! \brief Compares name with std::string value*/
		inline bool operator==(const std::string &value)
		{
			return value_ == value;
		}
		/*! \brief Compares name with Name value*/
		inline bool operator==(const Name &other)
		{
			return value_ == other.value_;
		}
		/*! \brief Assigns std::string value to name*/
		inline Name &operator=(const std::string &value)
		{
			value_ = value;
			return *this;
		}
		
	private:
		std::string value_;
	};
}
	
}