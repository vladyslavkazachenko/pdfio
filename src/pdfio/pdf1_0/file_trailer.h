#pragma once

#include "dictionary.h"
#include "integer.h"
#include "indirect_reference.h"

namespace
{
	const std::string kSize = "Size";
	const std::string kPrev = "Prev";
	const std::string kRoot = "Root";
	const std::string kInfo = "Info";
}

namespace pdfio
{
	
namespace pdf1_0
{
	
/*! \brief PDF file trailer.*/
class FileTrailer
{
public:
	/*! \brief Default constructor. Initializes internal dictionary with required and optional entries.*/
	inline FileTrailer()
	{
		dictionary_.insert<Integer>(kSize);
		dictionary_.insert<IndirectReference>(kRoot);
	}
	/*! \brief Returns value by key "Size".*/
	inline const Integer &size() const
	{
		return dictionary_.get<Integer>(kSize);
	}
	/*! \brief Returns value by key "Size".*/
	inline Integer &size()
	{
		return dictionary_.get<Integer>(kSize);
	}
	/*! \brief Checks whether internal dictionary contains entry with key "Prev".*/
	inline bool hasPrev() const
	{
		return dictionary_.contains(kPrev);
	}
	/*! \brief Returns value by key "Prev".*/
	inline const Integer &prev() const
	{
		return dictionary_.get<Integer>(kPrev);
	}
	/*! \brief Returns value by key "Prev".*/
	inline Integer &prev()
	{
		if(!hasPrev())
		{
			dictionary_.insert<Integer>(kPrev);
		}
		return dictionary_.get<Integer>(kPrev);
	}
	/*! \brief Returns value by key "Root".*/
	inline const IndirectReference &root() const
	{
		return dictionary_.get<IndirectReference>(kRoot);
	}
	/*! \brief Returns value by key "Root".*/
	inline IndirectReference &root()
	{
		return dictionary_.get<IndirectReference>(kRoot);
	}
	/*! \brief Checks whether internal dictionary contains entry with key "Info".*/
	inline bool hasInfo() const
	{
		return dictionary_.contains(kInfo);
	}
	/*! \brief Returns value by key "Info".*/
	inline const IndirectReference &info() const
	{
		return dictionary_.get<IndirectReference>(kInfo);
	}
	/*! \brief Returns value by key "Info".*/
	inline IndirectReference &info()
	{
		if(!hasInfo())
		{
			dictionary_.insert<IndirectReference>(kInfo);
		}
		return dictionary_.get<IndirectReference>(kInfo);
	}
	/*! \brief Returns internal dictionary.*/
	inline Dictionary &dictionary()
	{
		return dictionary_;
	}
	/*! \brief Returns internal dictionary.*/
	inline const Dictionary &dictionary() const
	{
		return dictionary_;
	}
	
	inline void prepare4Reading()
	{
		dictionary_.insert<IndirectReference>(kInfo);
	}
private:
	Dictionary dictionary_;
};
	
}

}