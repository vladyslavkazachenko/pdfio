#pragma once

#include "dictionary.h"
#include "array.h"
#include "integer.h"
#include "indirect_reference.h"

namespace pdfio
{
	
namespace pdf1_0
{
	
/*! \brief PDF page object.*/
class DocumentPage: public Dictionary
{
public:
	/*! \brief Constructs the page initializing base dictionary.*/
	inline DocumentPage()
	{
		insert<Array<Integer>>(Name("MediaBox"));
		get<Array<Integer>>(Name("MediaBox")).resize(4);
		insert<IndirectReference>(Name("Parent"));
		insert<Dictionary>(Name("Resources"));
	}
	/*! \brief Returns value of the page's "MediaBox".*/
	inline const Array<Integer> &mediaBox() const
	{
		return get<Array<Integer>>(Name("MediaBox"));
	}
	/*! \brief Returns value of the page's "MediaBox".*/
	inline Array<Integer> &mediaBox()
	{
		return get<Array<Integer>>(Name("MediaBox"));
	}
	/*! \brief Returns value of the page's "Parent".*/
	inline const IndirectReference &parent() const
	{
		return get<IndirectReference>(Name("Parent"));
	}
	/*! \brief Returns value of the page's "Parent".*/
	inline IndirectReference &parent()
	{
		return get<IndirectReference>(Name("Parent"));
	}
	/*! \brief Returns value of the page's "Resources".*/
	inline const Dictionary &resources() const
	{
		return get<Dictionary>(Name("Resources"));
	}
	/*! \brief Returns value of the page's "Resources".*/
	inline Dictionary &resources()
	{
		return get<Dictionary>(Name("Resources"));
	}
	/*! \brief Checks whether the page has "Contents".*/
	inline bool hasContents() const
	{
		return contains(Name("Contents"));
	}
	/*! \brief Returns value of the page's "Contents".*/
	inline const IndirectReference &contents() const
	{
		return get<IndirectReference>(Name("Contents"));
	}
	/*! \brief Returns value of the page's "Contents".*/
	inline IndirectReference &contents()
	{
		if(!hasContents())
		{
			insert<IndirectReference>(Name("Contents"));
		}
		return get<IndirectReference>(Name("Contents"));
	}
	/*! \brief Checks whether the page has "CropBox".*/
	inline bool hasCropBox() const
	{
		return false;
	}
	/*! \brief Checks whether the page has "Rotate".*/
	inline bool hasRotate() const
	{
		return false;
	}
	/*! \brief Checks whether the page has "Thumb".*/
	inline bool hasThumb() const
	{
		return false;
	}
	/*! \brief Checks whether the page has "Annots".*/
	inline bool hasAnnots() const
	{
		return false;
	}
};

}

}