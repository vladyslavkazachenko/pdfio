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
	DocumentCatalog();
	/*! \brief Returns value by key "Pages".*/
	const IndirectReference &pages() const;
	/*! \brief Returns value by key "Pages".*/
	IndirectReference &pages();
	/*! \brief Checks whether internal dictionary contains entry with key "Outlines".*/
	bool hasOutlines() const;
	/*! \brief Returns value by key "Outlines".*/
	const IndirectReference &outlines() const;
	/*! \brief Returns value by key "Outlines".*/
	IndirectReference &outlines();
	/*! \brief Checks whether internal dictionary contains entry with key "PageMode".*/
	bool hasPageMode() const;
	/*! \brief Returns value by key "PageMode".*/
	const Name &pageMode() const;
	/*! \brief Returns value by key "PageMode".*/
	Name &pageMode();
	/*! \brief Initializes internal dictionary with required and optional entries.*/
	void prepare4Read();
	
	static const Name kKeyType;
	static const Name kValueType;
	static const Name kKeyPages;
	static const Name kKeyOutlines;
	static const Name kKeyPageMode;
};
	
}

}	