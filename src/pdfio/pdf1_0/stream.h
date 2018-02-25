#pragma once

#include <iostream>
#include <sstream>

#include "integer.h"
#include "dictionary.h"

namespace pdfio
{
	
namespace pdf1_0
{
	
/*! \brief PDF stream object.*/
class Stream: public std::iostream, public Dictionary
{
public:
	/*! \brief Constructs the stream initializing base std::istream and base dictionary.*/
	Stream()
	: std::iostream(&buffer_)
	{
		Dictionary::insert<Integer>(Name("Length"));
	}
	/*! \brief Returns value by key "Length".*/
	inline const Integer &length() const
	{
		return Dictionary::get<Integer>(Name("Length"));
	}
	/*! \brief Returns value by key "Length".*/
	inline Integer &length()
	{
		return Dictionary::get<Integer>(Name("Length"));
	}
	
private:
	std::stringbuf buffer_;
};

}

}