#pragma once

#include <map>
#include <memory>
#include <set>

#include "name.h"
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
		/*! \brief Returns generic object by the key.*/
		inline GenericObject &get(const Name &key)
		{
			return *(entries_[key]);
		}
		/*! \brief Returns all the entries' keys.*/
		inline std::set<Name> keys() const
		{
			std::set<Name> keys;
			for(auto entry : entries_)
			{
				keys.insert(entry.first);
			}
			return keys;
		}
		/*! \brief Removes entry by the key.*/
		inline void remove(const Name &key)
		{
			return static_cast<void>(entries_.erase(key));
		}
	private:
		std::map<Name, std::shared_ptr<GenericObject>> entries_;
	};
}

}