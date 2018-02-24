#pragma once

#include "indirect_object.h"
#include "indirect_reference.h"
#include "dictionary.h"

namespace pdfio
{
	
namespace pdf1_0
{
	
/*! \brief PDF catalog.*/
class DocumentCatalog
{
public:
	/*! \brief Default constructor. Initializes internal dictionary with required entries.*/
	DocumentCatalog()
	{
		Dictionary dictionary;
		dictionary.insert<IndirectReference>(Name("Pages"));
		object_.set(dictionary);
	}
	/*! \brief Returns value by key "Pages".*/
	inline const IndirectReference &pages() const
	{
		return object_.get<Dictionary>().get<IndirectReference>(Name("Pages"));
	}
	/*! \brief Returns value by key "Pages".*/
	inline IndirectReference &pages()
	{
		return object_.get<Dictionary>().get<IndirectReference>(Name("Pages"));
	}
	/*! \brief Checks whether internal dictionary contains entry with key "Outlines".*/
	inline bool hasOutlines() const
	{
		return object_.get<Dictionary>().contains(Name("Outlines"));
	}
	/*! \brief Returns value by key "Outlines".*/
	inline const IndirectReference &outlines() const
	{
		return object_.get<Dictionary>().get<IndirectReference>(Name("Outlines"));
	}
	/*! \brief Returns value by key "Outlines".*/
	inline IndirectReference &outlines()
	{
		if(!hasOutlines())
		{
			object_.get<Dictionary>().insert<IndirectReference>(Name("Outlines"));
		}
		return object_.get<Dictionary>().get<IndirectReference>(Name("Outlines"));
	}
	/*! \brief Checks whether internal dictionary contains entry with key "PageMode".*/
	inline bool hasPageMode() const
	{
		return object_.get<Dictionary>().contains(Name("PageMode"));
	}
	/*! \brief Returns value by key "PageMode".*/
	inline const Name &pageMode() const
	{
		return object_.get<Dictionary>().get<Name>(Name("PageMode"));
	}
	/*! \brief Returns value by key "PageMode".*/
	inline Name &pageMode()
	{
		if(!hasPageMode())
		{
			object_.get<Dictionary>().insert<Name>(Name("PageMode"));
		}
		return object_.get<Dictionary>().get<Name>(Name("PageMode"));
	}
private:
	IndirectObject object_;
};
	
}

}	