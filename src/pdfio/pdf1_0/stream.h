#pragma once

#include <iostream>
#include <sstream>
#include <memory>

#include "integer.h"
#include "dictionary.h"
#include "array.h"
#include "hexstring.h"
#include "indirect_reference.h"

namespace pdfio
{
	
namespace pdf1_0
{
	
namespace
{
	const Name kDecodeParms = Name("DecodeParms");
	const Name kColumns = Name("Columns");
	const Name kPredictor = Name("Predictor");
	const Name kFilter = Name("Filter");
	const Name kId = Name("ID");
	const Name kIndex = Name("Index");
	const Name kInfo = Name("Info");
}
/*! \brief PDF stream object.*/
class Stream: public Dictionary
{
public:
	/*! \brief Constructs the stream initializing base std::istream and base dictionary.*/
	Stream()
	: buffer_(std::make_shared<std::stringbuf>())
	, iostream_(std::make_shared<std::iostream>(buffer_.get()))
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
	
	inline std::iostream& iostream()
	{
		return *iostream_;
	}
	
	template <typename T>
	std::istream &operator>>(T &value)
	{
		return (*iostream_) >> value;
	}
	
	template <typename T>
	std::ostream &operator<<(T &value)
	{
		return (*iostream_) << value;
	}
	
	inline void prepare4Reading()
	{
		Dictionary decodeParms;
		decodeParms.insert<Integer>(kColumns);
		decodeParms.insert<Integer>(kPredictor);
		insert(kDecodeParms, decodeParms);
		insert<Name>(kFilter);
		insert<Array<HexString>>(kId);
		insert<Array<Integer>>(kIndex);
		insert<IndirectReference>(kInfo);
	}
	
private:
	std::shared_ptr<std::stringbuf> buffer_;
	std::shared_ptr<std::iostream> iostream_;
};

}

}