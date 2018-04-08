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

/*! \brief PDF stream object.*/
class Stream: public virtual Dictionary
{
public:
	/*! \brief Constructs the stream initializing base std::istream and base dictionary.*/
	Stream();
	/*! \brief Returns value by key "Length".*/
	const Integer &length() const;
	/*! \brief Returns value by key "Length".*/
	Integer &length();
	/*! \brief Checks whether the parent Dictionary contains entry with key "DecodeParms".*/
	bool hasDecodeParms() const;
	/*! \brief Returns value by key "DecodeParms".*/
	const Dictionary &decodeParms() const;
	/*! \brief Returns value by key "DecodeParms".*/
	Dictionary &decodeParms();
	/*! \brief Checks whether the parent Dictionary contains entry with key "Filter".*/
	bool hasFilter() const;
	/*! \brief Returns value by key "Filter".*/
	const Name &filter() const;
	/*! \brief Returns value by key "Filter".*/
	Name &filter();
	
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
	/*! \brief Inserts optianal entries to the parent Dictionary.*/
	void prepare4Reading();
	
	static const Name kKeyLength;
	static const Name kKeyDecodeParms;
	static const Name kKeyFilter;
	static const Name kKeyColumns;
	static const Name kKeyPredictor;
	
private:
	std::shared_ptr<std::stringbuf> buffer_;
	std::shared_ptr<std::iostream> iostream_;
};

}

}