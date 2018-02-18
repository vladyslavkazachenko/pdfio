#pragma once

#include "name.h"
#include "integer.h"
#include "indirect_reference.h"

namespace pdfio
{
	
namespace pdf1_0
{
	/*! \brief Basic struct for polimorphic context for Name, Integer and IndirectReference.*/
	struct GenericObject
	{
		/*! \brief Distinguishes types.*/
		enum class TypeId
		{
			kName,
			kInteger,
			kIndirectReference,
		};
		/*! \brief Contructs the GenericObject with the typeId.*/
		inline GenericObject(TypeId typeId)
		: typeId_(typeId)
		{
			
		}
		/*! \brief Destructs the GenericObject.*/
		virtual ~GenericObject() = default;
		/*! \brief Defines T type information.*/
		template <typename T> struct TypeInfo{};
		/*! \brief Identifies the GenericObject type id.*/
		const TypeId typeId_;
	};
	/*! \brief Defines Name type information.*/
	template <> struct GenericObject::TypeInfo<Name>
	{
		/*! \brief Returns TypeId for Name.*/
		static TypeId Id()
		{
			return  TypeId::kName;
		}
	};
	/*! \brief Defines Integer type information.*/
	template <> struct GenericObject::TypeInfo<Integer>
	{
		/*! \brief Returns TypeId for Integer.*/
		static TypeId Id()
		{
			return  TypeId::kInteger;
		}
	};
	/*! \brief Defines IndirectReference type information.*/
	template <> struct GenericObject::TypeInfo<IndirectReference>
	{
		/*! \brief Returns TypeId for IndirectReference.*/
		static TypeId Id()
		{
			return  TypeId::kIndirectReference;
		}
	};
	/*! \brief Holds an object of the type T.*/
	template <typename T> struct GenericObjectAdaptor: GenericObject
	{
		/*! \brief Contructs the GenericObjectAdaptor with the object.*/
		GenericObjectAdaptor(const T &object)
		: GenericObject(TypeInfo<T>::Id())
		, object_(object)
		{
			
		}
		/*! \brief Internal the T object.*/
		T object_;
	};
}

}