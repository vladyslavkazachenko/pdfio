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
	Stream()
	: buffer_(std::make_shared<std::stringbuf>())
	, iostream_(std::make_shared<std::iostream>(buffer_.get()))
	{
		insert<Integer>(Name("Length"));
	}
	/*! \brief Returns value by key "Length".*/
	inline const Integer &length() const
	{
		return get<Integer>(Name("Length"));
	}
	/*! \brief Returns value by key "Length".*/
	inline Integer &length()
	{
		return get<Integer>(Name("Length"));
	}
	/*! \brief Checks whether the parent Dictionary contains entry with key "DecodeParms".*/
	inline bool hasDecodeParms() const
	{
		return contains(kDecodeParms);
	}
	/*! \brief Returns value by key "DecodeParms".*/
	inline const Dictionary &decodeParms() const
	{
		return get<Dictionary>(kDecodeParms);
	}
	/*! \brief Returns value by key "DecodeParms".*/
	inline Dictionary &decodeParms()
	{
		if(!hasDecodeParms())
		{
			insert<Dictionary>(kDecodeParms);
		}
		return get<Dictionary>(kDecodeParms);
	}
	/*! \brief Checks whether the parent Dictionary contains entry with key "Filter".*/
	inline bool hasFilter() const
	{
		return contains(kFilter);
	}
	/*! \brief Returns value by key "Filter".*/
	inline const Name &filter() const
	{
		return get<Name>(kFilter);
	}
	/*! \brief Returns value by key "Filter".*/
	inline Name &filter()
	{
		if(!hasDecodeParms())
		{
			insert<Name>(kFilter);
		}
		return get<Name>(kFilter);
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
	}
	
	const Name kDecodeParms = Name("DecodeParms");
	const Name kColumns = Name("Columns");
	const Name kPredictor = Name("Predictor");
	const Name kFilter = Name("Filter");
	
private:
	std::shared_ptr<std::stringbuf> buffer_;
	std::shared_ptr<std::iostream> iostream_;
};

}

}