#pragma once

namespace pdfio
{
	
namespace pdf1_0
{
	/*! \brief Basic struct for Dictionary, Array and IndirectObject.*/
	struct GenericObject
	{
		/*! \brief Contructs the GenericObject with the typeId.*/
		inline GenericObject(int typeId)
		: typeId_(typeId)
		{
			
		}
		/*! \brief Destructs the GenericObject.*/
		virtual ~GenericObject() = default;
		/*! \brief Returns type id of the T.*/
		template <typename T> static int TypeId();
		/*! \brief Identifies the GenericObject type id.*/
		const int typeId_;
	};
	/*! \brief Holds an object of the type T.*/
	template <typename T> struct GenericObjectAdaptor: GenericObject
	{
		/*! \brief Contructs the GenericObjectAdaptor with the object.*/
		GenericObjectAdaptor(const T &object)
		: GenericObject(GenericObject::TypeId<T>())
		, object_(object)
		{
			
		}
		/*! \brief Internal the T object.*/
		T object_;
	};
}

}