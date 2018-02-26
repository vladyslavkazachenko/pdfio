#pragma once

#include "indirect_object.h"
#include "array.h"
#include "indirect_reference.h"
#include "dictionary.h"

namespace pdfio
{
	
namespace pdf1_0
{
	
/*! \brief PDF page object.*/
class DocumentPage: public IndirectObject
{
public:
	/*! \brief Constructs the page initializing internal dictionary.*/
	inline DocumentPage()
	{
		Dictionary dictionary;
		dictionary.insert<Array<Integer>>(Name("MediaBox"));
		dictionary.get<Array<Integer>>(Name("MediaBox")).resize(4);
		dictionary.insert<IndirectReference>(Name("Parent"));
		dictionary.insert<Dictionary>(Name("Resources"));
		IndirectObject::set(dictionary);
	}
	/*! \brief Returns value of the page's "MediaBox".*/
	inline const Array<Integer> &mediaBox() const
	{
		return IndirectObject::get<Dictionary>().get<Array<Integer>>(Name("MediaBox"));
	}
	/*! \brief Returns value of the page's "MediaBox".*/
	inline Array<Integer> &mediaBox()
	{
		return IndirectObject::get<Dictionary>().get<Array<Integer>>(Name("MediaBox"));
	}
	/*! \brief Returns value of the page's "Parent".*/
	inline const IndirectReference &parent() const
	{
		return IndirectObject::get<Dictionary>().get<IndirectReference>(Name("Parent"));
	}
	/*! \brief Returns value of the page's "Parent".*/
	inline IndirectReference &parent()
	{
		return IndirectObject::get<Dictionary>().get<IndirectReference>(Name("Parent"));
	}
	/*! \brief Returns value of the page's "Resources".*/
	inline const Dictionary &resources() const
	{
		return IndirectObject::get<Dictionary>().get<Dictionary>(Name("Resources"));
	}
	/*! \brief Returns value of the page's "Resources".*/
	inline Dictionary &resources()
	{
		return IndirectObject::get<Dictionary>().get<Dictionary>(Name("Resources"));
	}
	/*! \brief Checks whether the page has "Contents".*/
	inline bool hasContents() const
	{
		return IndirectObject::get<Dictionary>().contains(Name("Contents"));
	}
	/*! \brief Returns value of the page's "Contents".*/
	inline const IndirectReference &contents() const
	{
		return IndirectObject::get<Dictionary>().get<IndirectReference>(Name("Contents"));
	}
	/*! \brief Returns value of the page's "Contents".*/
	inline IndirectReference &contents()
	{
		if(!hasContents())
		{
			IndirectObject::get<Dictionary>().insert<IndirectReference>(Name("Contents"));
		}
		return IndirectObject::get<Dictionary>().get<IndirectReference>(Name("Contents"));
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