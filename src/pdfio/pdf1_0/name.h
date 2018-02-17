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
		inline Name(const std::string &value)
		: value_(value)
		{
			
		}
		/*! \brief Compares name with std::string value*/
		inline bool operator==(const std::string &value) const
		{
			return value_ == value;
		}
		/*! \brief Compares name with Name value*/
		inline bool operator==(const Name &other) const
		{
			return value_ == other.value_;
		}
		/*! \brief Assigns std::string value to name*/
		inline Name &operator=(const std::string &value)
		{
			value_ = value;
			return *this;
		}
		/*! \brief Assigns const char * value to name*/
		inline Name &operator=(const char *value)
		{
			value_ = value;
			return *this;
		}
		/*! \brief Checks whether the name is less than other*/
		inline bool operator<(const Name &other) const
		{
			return value_ < other.value_;
		}
		
	private:
		std::string value_;
	};
}
	
}