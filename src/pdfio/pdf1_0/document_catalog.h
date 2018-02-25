#pragma once

#include "indirect_object.h"
#include "indirect_reference.h"
#include "dictionary.h"

namespace pdfio
{
	
namespace pdf1_0
{
	
/*! \brief PDF catalog.*/
class DocumentCatalog: public IndirectObject
{
public:
	/*! \brief Default constructor. Initializes internal dictionary with required entries.*/
	DocumentCatalog()
	{
		Dictionary dictionary;
		dictionary.insert<IndirectReference>(Name("Pages"));
		set(dictionary);
	}
	/*! \brief Returns value by key "Pages".*/
	inline const IndirectReference &pages() const
	{
		return get<Dictionary>().get<IndirectReference>(Name("Pages"));
	}
	/*! \brief Returns value by key "Pages".*/
	inline IndirectReference &pages()
	{
		return get<Dictionary>().get<IndirectReference>(Name("Pages"));
	}
	/*! \brief Checks whether internal dictionary contains entry with key "Outlines".*/
	inline bool hasOutlines() const
	{
		return get<Dictionary>().contains(Name("Outlines"));
	}
	/*! \brief Returns value by key "Outlines".*/
	inline const IndirectReference &outlines() const
	{
		return get<Dictionary>().get<IndirectReference>(Name("Outlines"));
	}
	/*! \brief Returns value by key "Outlines".*/
	inline IndirectReference &outlines()
	{
		if(!hasOutlines())
		{
			get<Dictionary>().insert<IndirectReference>(Name("Outlines"));
		}
		return get<Dictionary>().get<IndirectReference>(Name("Outlines"));
	}
	/*! \brief Checks whether internal dictionary contains entry with key "PageMode".*/
	inline bool hasPageMode() const
	{
		return get<Dictionary>().contains(Name("PageMode"));
	}
	/*! \brief Returns value by key "PageMode".*/
	inline const Name &pageMode() const
	{
		return get<Dictionary>().get<Name>(Name("PageMode"));
	}
	/*! \brief Returns value by key "PageMode".*/
	inline Name &pageMode()
	{
		if(!hasPageMode())
		{
			get<Dictionary>().insert<Name>(Name("PageMode"));
		}
		return get<Dictionary>().get<Name>(Name("PageMode"));
	}
	/*! \brief Initializes internal dictionary with required and optional entries.*/
	inline void prepare4Read()
	{
		Dictionary dictionary;
		dictionary.insert<Name>(Name("Type"));
		dictionary.insert<IndirectReference>(Name("Pages"));
		dictionary.insert<IndirectReference>(Name("Outlines"));
		dictionary.insert<Name>(Name("PageMode"));
		set(dictionary);
	}
};
	
}

}	