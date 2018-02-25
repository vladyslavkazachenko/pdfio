#pragma once

#include <vector>

namespace pdfio
{
	
namespace pdf1_0
{
	
/*! \brief PDF array object.*/
template <typename T>
class Array
{
public:
	/*! \brief Constructs the array with the count elements.*/
	Array(std::size_t count = 0)
	: elements_(count)
	{
		
	}
	/*! \brief Checks whether the array is empty.*/
	inline bool empty() const
	{
		return elements_.empty();
	}
	/*! \brief Returns the array's size.*/
	inline std::size_t size() const
	{
		return elements_.size();
	}
	/*! \brief Returns the array's element by the index*/
	inline const T &operator[](std::size_t index) const
	{
		return elements_[index];
	}
	/*! \brief Returns the array's element by the index*/
	inline T &operator[](std::size_t index)
	{
		return elements_[index];
	}
	/*! \brief Increases the size of the array*/
	inline void resize(std::size_t size)
	{
		return elements_.resize(size);
	}
	
private:
	std::vector<T> elements_;
};

}

}