#pragma once

#include "indirect_reference.h"
#include "dictionary.h"

namespace pdfio
{
	
namespace pdf1_0
{
	
/*! \brief PDF catalog.*/
class DocumentCatalog: public Dictionary
{
public:
	/*! \brief Default constructor. Initializes base dictionary with required entries.*/
	DocumentCatalog()
	{
		insert<IndirectReference>(Name("Pages"));
	}
	/*! \brief Returns value by key "Pages".*/
	inline const IndirectReference &pages() const
	{
		return get<IndirectReference>(Name("Pages"));
	}
	/*! \brief Returns value by key "Pages".*/
	inline IndirectReference &pages()
	{
		return get<IndirectReference>(Name("Pages"));
	}
	/*! \brief Checks whether internal dictionary contains entry with key "Outlines".*/
	inline bool hasOutlines() const
	{
		return contains(Name("Outlines"));
	}
	/*! \brief Returns value by key "Outlines".*/
	inline const IndirectReference &outlines() const
	{
		return get<IndirectReference>(Name("Outlines"));
	}
	/*! \brief Returns value by key "Outlines".*/
	inline IndirectReference &outlines()
	{
		if(!hasOutlines())
		{
			insert<IndirectReference>(Name("Outlines"));
		}
		return get<IndirectReference>(Name("Outlines"));
	}
	/*! \brief Checks whether internal dictionary contains entry with key "PageMode".*/
	inline bool hasPageMode() const
	{
		return contains(Name("PageMode"));
	}
	/*! \brief Returns value by key "PageMode".*/
	inline const Name &pageMode() const
	{
		return get<Name>(Name("PageMode"));
	}
	/*! \brief Returns value by key "PageMode".*/
	inline Name &pageMode()
	{
		if(!hasPageMode())
		{
			insert<Name>(Name("PageMode"));
		}
		return get<Name>(Name("PageMode"));
	}
	/*! \brief Initializes internal dictionary with required and optional entries.*/
	inline void prepare4Read()
	{
		insert<Name>(Name("Type"));
		insert<IndirectReference>(Name("Pages"));
		insert<IndirectReference>(Name("Outlines"));
		insert<Name>(Name("PageMode"));
	}
};
	
}

}	