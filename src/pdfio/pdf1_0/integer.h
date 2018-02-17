#pragma once

namespace pdfio
{
	
namespace pdf1_0
{
	/*! \brief PDF integer object.*/
	class Integer
	{
	public:
		/*! \brief Default constructor.*/
		Integer() = default;
		/*! \brief Initializes integer by long long value.*/
		inline explicit Integer(long long value)
		: value_(value)
		{
			
		}
		/*! \brief Compares integer with long long value.*/
		inline bool operator==(long long value) const
		{
			return value_ == value;
		}
		/*! \brief Compares integer with Integer value.*/
		inline bool operator==(const Integer &other) const
		{
			return value_ == other.value_;
		}
		/*! \brief Assigns long long value to integer.*/
		inline Integer &operator=(long long value)
		{
			value_ = value;
			return *this;
		}
		
	private:
		long long value_ = 0;
	};
}

}