#pragma once

#include "name.h"
#include "integer.h"
#include "indirect_reference.h"

namespace pdfio
{
	
namespace pdf1_0
{
	enum class TypeId
	{
		kName,
		kInteger,
		kIndirectReference,
	};
	/*! \brief Defines T type information.*/
	template <typename T> struct TypeInfo
	{
		/*! \brief Identifies the T.*/
		//static const TypeId Id;
	};
	/*! \brief Defines Name type information.*/
	template <> struct TypeInfo<Name>
	{
		/*! \brief Returns TypeId for Name.*/
		static TypeId Id()
		{
			return  TypeId::kName;
		}
	};
	/*! \brief Defines Integer type information.*/
	template <> struct TypeInfo<Integer>
	{
		/*! \brief Returns TypeId for Integer.*/
		static TypeId Id()
		{
			return  TypeId::kInteger;
		}
	};
	/*! \brief Defines IndirectReference type information.*/
	template <> struct TypeInfo<IndirectReference>
	{
		/*! \brief Returns TypeId for IndirectReference.*/
		static TypeId Id()
		{
			return  TypeId::kIndirectReference;
		}
	};
}

}