#pragma once

#include <map>
#include <memory>

#include "generic_object.h"

namespace pdfio
{
	
namespace pdf1_0
{
	/*! \brief PDF dictionary object.*/
	class Dictionary
	{
	public:
		/*! \brief Checks whether the dictionary contains entry with key.*/
		inline bool contains(const Name &key) const
		{
			return entries_.find(key) != entries_.end();
		}
		/*! \brief Inserts entry to the dictionary with key and value.*/
		template <typename T>
		inline void insert(const Name &key, const T &value = T())
		{
			entries_[key] = std::static_pointer_cast<GenericObject>(
				std::make_shared<GenericObjectAdaptor<T>>(value));
		}
		/*! \brief Returns value by the key.*/
		template <typename T>
		inline const T &get(const Name &key) const
		{
			return std::static_pointer_cast<GenericObjectAdaptor<T>>(entries_.at(key))->object_;
		}
		/*! \brief Returns value by the key.*/
		template <typename T>
		inline T &get(const Name &key)
		{
			return std::static_pointer_cast<GenericObjectAdaptor<T>>(entries_[key])->object_;
		}
		/*! \brief Returns value's type id by the key.*/
		inline GenericObject::TypeId valueTypeId(const Name &key)
		{
			return entries_[key]->typeId_;
		}
		/*! \brief Swaps the dictionary's content with the other.*/
		inline void swap(Dictionary &other)
		{
			entries_.swap(other.entries_);
		}
	private:
		std::map<Name, std::shared_ptr<GenericObject>> entries_;
	};
}

}