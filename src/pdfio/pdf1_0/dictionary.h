#pragma once

#include <map>
#include <memory>

#include "type_info.h"

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
			entries_[key] = std::static_pointer_cast<Entry>(
				std::make_shared<EntryAdaptor<T>>(value));
		}
		/*! \brief Returns value by the key.*/
		template <typename T>
		inline const T &get(const Name &key) const
		{
			return std::static_pointer_cast<EntryAdaptor<T>>(entries_.at(key))->get();
		}
		/*! \brief Returns value by the key.*/
		template <typename T>
		inline T &get(const Name &key)
		{
			return std::static_pointer_cast<EntryAdaptor<T>>(entries_[key])->get();
		}
		/*! \brief Returns value's type id by the key.*/
		inline TypeId valueTypeId(const Name &key)
		{
			return entries_[key]->typeId();
		}
		/*! \brief Swaps the dictionary's content with the other.*/
		inline void swap(Dictionary &other)
		{
			entries_.swap(other.entries_);
		}
	private:
		class Entry
		{
		public:
			inline Entry(TypeId typeId)
			: typeId_(typeId)
			{
				
			}
			
			virtual ~Entry() = default;
			
			TypeId typeId() const
			{
				return typeId_;
			}
			
		private:
			const TypeId typeId_;
		};
		
		template <typename T> class EntryAdaptor: public Entry
		{
		public:
			EntryAdaptor(const T &object)
			: Entry(TypeInfo<T>::Id())
			, object_(object)
			{
				
			}
			
			const T &get() const
			{
				return object_;
			}
			
			T &get()
			{
				return object_;
			}
			
		private:
			T object_;
		};
		
		std::map<Name, std::shared_ptr<Entry>> entries_;
	};
}

}