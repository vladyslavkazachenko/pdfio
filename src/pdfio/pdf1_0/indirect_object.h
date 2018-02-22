#pragma once

#pragma once

#include <memory>

#include "integer.h"
#include "generic_object.h"

namespace pdfio
{
	
namespace pdf1_0
{
	/*! \brief PDF indirect object.*/
	class IndirectObject
	{
	public:
		/*! \brief Returns the indirect object's object number.*/
		inline const Integer &objectNumber() const
		{
			return objectNumber_;
		}
		/*! \brief Returns the indirect object's object number.*/
		inline Integer &objectNumber()
		{
			return objectNumber_;
		}
		/*! \brief Returns the indirect object's generation number.*/
		inline const Integer &generationNumber() const
		{
			return generationNumber_;
		}
		/*! \brief Returns the indirect object's generation number.*/
		inline Integer &generationNumber()
		{
			return generationNumber_;
		}
		/*! \brief Initializes the indirect object's object.*/
		template <typename T>
		inline void set(const T &object = T())
		{
			object_ = std::static_pointer_cast<GenericObject>(
				std::make_shared<GenericObjectAdaptor<T>>(object));
		}
		/*! \brief Returns the indirect object's object.*/
		template <typename T>
		inline const T &get() const
		{
			return std::static_pointer_cast<GenericObjectAdaptor<T>>(object_)->object_;
		}
		/*! \brief Returns the indirect object's object.*/
		template <typename T>
		inline T &get()
		{
			return std::static_pointer_cast<GenericObjectAdaptor<T>>(object_)->object_;
		}
		/*! \brief Returns the indirect object's generic object.*/
		inline GenericObject &get()
		{
			return *object_;
		}
	private:
		Integer objectNumber_;
		Integer generationNumber_;
		std::shared_ptr<GenericObject> object_;
	};
}

}