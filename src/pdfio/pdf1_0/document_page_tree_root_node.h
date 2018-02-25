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
class DocumentPageTreeRootNode
{
public:
	/*! \brief Contructs the object initializing the internal indirect object.*/
	DocumentPageTreeRootNode()
	{
		Dictionary dictionary;
		dictionary.insert<Name>(Name("Type"));
		dictionary.insert<Array<IndirectReference>>(Name("Kids"));
		dictionary.insert<Integer>(Name("Count"));
		object_.set(dictionary);
	}
	/*! \brief Returns value by key "Kids".*/
	inline const Array<IndirectReference> &kids() const
	{
		return object_.get<Dictionary>().get<Array<IndirectReference>>(Name("Kids"));
	}
	/*! \brief Returns value by key "Kids".*/
	inline Array<IndirectReference> &kids()
	{
		return object_.get<Dictionary>().get<Array<IndirectReference>>(Name("Kids"));
	}
	/*! \brief Returns value by key "Count".*/
	inline const Integer &count() const
	{
		return object_.get<Dictionary>().get<Integer>(Name("Count"));
	}
	/*! \brief Returns value by key "Count".*/
	inline Integer &count()
	{
		return object_.get<Dictionary>().get<Integer>(Name("Count"));
	}
	/*! \brief Returns internal indirect object.*/
	inline IndirectObject &object()
	{
		return object_;
	}
	
private:
	IndirectObject object_;
};

}

}