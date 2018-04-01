#pragma once

#include <functional>
#include <cassert>

#include "integer.h"

namespace pdfio
{
  
namespace pdf1_0
{
  
/*! \brief PDF page object.*/
struct DocumentPageDescription
{
	std::function<void(Integer x, Integer y)> movetoHandler_;
	std::function<void(Integer x, Integer y)> linetoHandler_;
	std::function<void()> strokeHandler_;
	std::function<void(Integer w)> setlinewidthHandler_;
	
	inline void moveto(Integer x, Integer y)
	{
		assert(movetoHandler_);
		movetoHandler_(x, y);
	}
	inline void lineto(Integer x, Integer y)
	{
		assert(linetoHandler_);
		linetoHandler_(x, y);
	}
	inline void stroke()
	{
		assert(strokeHandler_);
		strokeHandler_();
	}
	inline void setlinewidth(Integer w)
	{
		assert(setlinewidthHandler_);
		setlinewidthHandler_(w);
	}
};

} //pdf1_0

} //pdfio