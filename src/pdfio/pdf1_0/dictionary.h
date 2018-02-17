#pragma once

#include <map>
#include <memory>

#include "name.h"
#include "integer.h"
#include "indirect_reference.h"

namespace pdfio
{
	
namespace pdf1_0
{
	/*! \brief PDF dictionary object.*/
	class Dictionary
	{
	public:
		/*! \brief Checks whether the dictionary contains entry with key.*/
		inline bool contains(const Name &key)
		{
			return entries_.find(key) != entries_.end();
		}
		/*! \brief Inserts entry to the dictionary with key and value.*/
		template <typename T>
		inline void insert(const Name &key, const T &value)
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
		
	private:
		class Entry
		{
		public:
			enum ObjectType
			{
				kName,
				kInteger,
				kIndirectReference,
			};
			
			template <typename T> 
			static const ObjectType ObjectTypeMap;
		
			inline Entry(ObjectType objectType)
			: objectType_(objectType)
			{
				
			}
			
			virtual ~Entry() = default;
			
			ObjectType objectType() const
			{
				return objectType_;
			}
			
		private:
			ObjectType objectType_;
		};
		
		template <typename T> class EntryAdaptor: public Entry
		{
		public:
			EntryAdaptor(const T &object)
			: Entry(ObjectTypeMap<T>)
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
	
	template <>
	const Dictionary::Entry::ObjectType Dictionary::Entry::ObjectTypeMap<Name> = 
		Dictionary::Entry::kName;
	template <>
	const Dictionary::Entry::ObjectType Dictionary::Entry::ObjectTypeMap<Integer> = 
		Dictionary::Entry::kInteger;
	template <>
	const Dictionary::Entry::ObjectType Dictionary::Entry::ObjectTypeMap<IndirectReference> = 
		Dictionary::Entry::kIndirectReference;
}

}