#pragma once

#include "indirect_object.h"
#include "array.h"
#include "indirect_reference.h"
#include "dictionary.h"

namespace pdfio
{
	
namespace pdf1_0
{
	
/*! \brief PDF root pages object.*/
class DocumentPageTreeRootNode: public IndirectObject
{
public:
	/*! \brief Contructs the object initializing the indirect object.*/
	DocumentPageTreeRootNode()
	{
		Dictionary dictionary;
		dictionary.insert<Name>(Name("Type"));
		dictionary.insert<Array<IndirectReference>>(Name("Kids"));
		dictionary.insert<Integer>(Name("Count"));
		set(dictionary);
	}
	/*! \brief Returns value by key "Kids".*/
	inline const Array<IndirectReference> &kids() const
	{
		return get<Dictionary>().get<Array<IndirectReference>>(Name("Kids"));
	}
	/*! \brief Returns value by key "Kids".*/
	inline Array<IndirectReference> &kids()
	{
		return get<Dictionary>().get<Array<IndirectReference>>(Name("Kids"));
	}
	/*! \brief Returns value by key "Count".*/
	inline const Integer &count() const
	{
		return get<Dictionary>().get<Integer>(Name("Count"));
	}
	/*! \brief Returns value by key "Count".*/
	inline Integer &count()
	{
		return get<Dictionary>().get<Integer>(Name("Count"));
	}
};

}

}