#pragma once

#include "generic_object.h"
#include "name.h"
#include "integer.h"
#include "indirect_reference.h"
#include "dictionary.h"

namespace pdfio
{
	
namespace pdf1_0
{
	enum class GenericObjectType
	{
		kName,
		kInteger,
		kIndirectReference,
		kDictionary,
	};
	/*! \brief Returns type id of Name.*/
	template <> inline int GenericObject::TypeId<Name>()
	{
		return static_cast<int>(GenericObjectType::kName);
	}
	/*! \brief Returns type id of Integer.*/
	template <> inline int GenericObject::TypeId<Integer>()
	{
		return static_cast<int>(GenericObjectType::kInteger);
	}
	/*! \brief Returns type id of IndirectReference.*/
	template <> inline int GenericObject::TypeId<IndirectReference>()
	{
		return static_cast<int>(GenericObjectType::kIndirectReference);
	}
	/*! \brief Returns type id of Dictionary.*/
	template <> inline int GenericObject::TypeId<Dictionary>()
	{
		return static_cast<int>(GenericObjectType::kDictionary);
	}
}
	
}