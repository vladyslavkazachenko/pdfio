#pragma once

#include "dictionary.h"
#include "array.h"
#include "indirect_reference.h"
#include "integer.h"

namespace pdfio
{
	
namespace pdf1_0
{
	
/*! \brief PDF root pages object.*/
class DocumentPageTreeRootNode: public Dictionary
{
public:
	/*! \brief Contructs the object initializing the base object.*/
	DocumentPageTreeRootNode()
	{
		insert<Name>(Name("Type"));
		insert<Array<IndirectReference>>(Name("Kids"));
		insert<Integer>(Name("Count"));
	}
	/*! \brief Returns value by key "Kids".*/
	inline const Array<IndirectReference> &kids() const
	{
		return get<Array<IndirectReference>>(Name("Kids"));
	}
	/*! \brief Returns value by key "Kids".*/
	inline Array<IndirectReference> &kids()
	{
		return get<Array<IndirectReference>>(Name("Kids"));
	}
	/*! \brief Returns value by key "Count".*/
	inline const Integer &count() const
	{
		return get<Integer>(Name("Count"));
	}
	/*! \brief Returns value by key "Count".*/
	inline Integer &count()
	{
		return get<Integer>(Name("Count"));
	}
};

}

}