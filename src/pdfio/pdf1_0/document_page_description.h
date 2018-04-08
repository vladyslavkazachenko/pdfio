#pragma once

#include <functional>
#include <cassert>
#include <vector>

#include "integer.h"
#include "real.h"

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
	std::function<void(Real x, Real y, Real w, Real h)> rectangleHandler_;
	std::function<void()> fillHandler_;
	std::function<void()> fillAndStrokeHandler_;
	std::function<void()> closepathFillAndStrokeHandler_;
	std::function<void(Integer x1, Integer y1, Integer x2, Integer y2, Integer x3, Integer y3)> curveHandler_;
	std::function<void(double r, double g, double b)> setrgbcolorFillHandler_;
	std::function<void(double r, double g, double b)> setrgbcolorStrokeHandler_;
	std::function<void(Integer phase, const std::vector<Integer> &array)> setdashHandler_;
	std::function<void(double gray)> setgrayFillHandler_;
	std::function<void()> clipHandler_;
	std::function<void()> saveHandler_;
	std::function<void()> restoreHandler_;
	
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
	inline void rectangle(Real x, Real y, Real w, Real h)
	{
		assert(rectangleHandler_);
		rectangleHandler_(x, y, w, h);
	}
	inline void fill()
	{
		assert(fillHandler_);
		fillHandler_();
	}
	inline void fillAndStroke()
	{
		assert(fillAndStrokeHandler_);
		fillAndStrokeHandler_();
	}
	inline void closepathFillAndStroke()
	{
		assert(closepathFillAndStrokeHandler_);
		closepathFillAndStrokeHandler_();
	}
	inline void curve(Integer x1, Integer y1, Integer x2, Integer y2, Integer x3, Integer y3)
	{
		assert(curveHandler_);
		curveHandler_(x1, y1, x2, y2, x3, y3);
	}
	inline void setrgbcolorFill(double r, double g, double b)
	{
		assert(setrgbcolorFillHandler_);
		setrgbcolorFillHandler_(r, g, b);
	}
	inline void setrgbcolorStroke(double r, double g, double b)
	{
		assert(setrgbcolorStrokeHandler_);
		setrgbcolorStrokeHandler_(r, g, b);
	}
	inline void setdash(Integer phase, const std::vector<Integer> &array)
	{
		assert(setdashHandler_);
		setdashHandler_(phase, array);
	}
	inline void setgrayFill(double gray)
	{
		assert(setgrayFillHandler_);
		setgrayFillHandler_(gray);
	}
	inline void clip()
	{
		assert(clipHandler_);
		clipHandler_();
	}
	inline void save()
	{
		assert(saveHandler_);
		saveHandler_();
	}
	inline void restore()
	{
		assert(restoreHandler_);
		restoreHandler_();
	}
};

} //pdf1_0

} //pdfio