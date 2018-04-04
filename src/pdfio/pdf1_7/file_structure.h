#pragma once

#include <string>
#include <vector>

#include "pdfio/pdf1_0/file_structure.h"
#include "integer.h"
#include "dictionary.h"
#include "indirect_reference.h"
#include "array.h"
#include "hexstring.h"
#include "dictionary.h"

namespace pdfio
{
	
namespace pdf1_7
{
	
namespace
{
	const std::string kSize = "Size";
	const std::string kPrev = "Prev";
	const std::string kRoot = "Root";
	const std::string kEncrypt = "Encrypt";
	const std::string kInfo = "Info";
	const std::string kId = "ID";
}

/*! \brief PDF File Structure.*/
struct FileStructure
{
	/*! \brief PDF File Header.*/
	class Header
	{
	public:
		/*! \brief Constructs the Header by initializing the version_ by the version.*/
		inline Header(const std::string &version = "")
		: version_(version)
		{
			
		}
		/*! \brief Converts the Header to std::string by returning the version_.*/
		inline operator std::string() const
		{
			return version_;
		}
		/*! \brief Assigns the version to the version_.*/
		inline Header &operator=(const std::string &version)
		{
			version_ = version;
			return *this;
		}
		/*! \brief Compares the version to the version_.*/
		inline bool operator==(const std::string &version) const
		{
			return version_ == version;
		}
		
	private:
		std::string version_;
	};

	/*! \brief PDF File Trailer.*/
	class Trailer
	{
	public:
		/*! \brief Constructs the Trailer by adding Integer value with key "Size"
		 *into the dictionary_.*/
		Trailer()
		{
			dictionary_.insert<Integer>(kSize);
		}
		/*! \brief Returns value by key "Size".*/
		inline const Integer &size() const
		{
			return dictionary_.get<Integer>(kSize);
		}
		/*! \brief Returns value by key "Size".*/
		inline Integer &size()
		{
			return dictionary_.get<Integer>(kSize);
		}
		/*! \brief Checks whether internal dictionary contains entry with key "Prev".*/
		inline bool hasPrev() const
		{
			return dictionary_.contains(kPrev);
		}
		/*! \brief Returns value by key "Prev".*/
		inline const Integer &prev() const
		{
			return dictionary_.get<Integer>(kPrev);
		}
		/*! \brief Returns value by key "Prev".*/
		inline Integer &prev()
		{
			if(!hasPrev())
			{
				dictionary_.insert<Integer>(kPrev);
			}
			return dictionary_.get<Integer>(kPrev);
		}
		/*! \brief Checks whether internal dictionary contains entry with key "Root".*/
		inline bool hasRoot() const
		{
			return dictionary_.contains(kRoot);
		}
		/*! \brief Returns value by key "Root".*/
		inline const IndirectReference &root() const
		{
			return dictionary_.get<IndirectReference>(kRoot);
		}
		/*! \brief Returns value by key "Root".*/
		inline IndirectReference &root()
		{
			return dictionary_.get<IndirectReference>(kRoot);
		}
		/*! \brief Checks whether internal dictionary contains entry with key "Encrypt".*/
		inline bool hasEncrypt() const
		{
			return dictionary_.contains(kEncrypt);
		}
		/*! \brief Checks whether internal dictionary contains entry with key "Info".*/
		inline bool hasInfo() const
		{
			return dictionary_.contains(kInfo);
		}
		/*! \brief Returns value by key "Info".*/
		inline const IndirectReference &info() const
		{
			return dictionary_.get<IndirectReference>(kInfo);
		}
		/*! \brief Returns value by key "Info".*/
		inline IndirectReference &info()
		{
			if(!hasInfo())
			{
				dictionary_.insert<IndirectReference>(kInfo);
			}
			return dictionary_.get<IndirectReference>(kInfo);
		}
		/*! \brief Checks whether internal dictionary contains entry with key "ID".*/
		inline bool hasId() const
		{
			return dictionary_.contains(kId);
		}
		/*! \brief Returns value by key "ID".*/
		inline const Array<HexString> &id() const
		{
			return dictionary_.get<pdf1_7::Array<pdf1_7::HexString>>(kId);
		}
		/*! \brief Returns value by key "ID".*/
		inline Array<HexString> &id()
		{
			if(!hasId())
			{
				pdf1_7::Array<pdf1_7::HexString> id(2);
				dictionary_.insert<pdf1_7::Array<pdf1_7::HexString>>(kId, id);
			}
			return dictionary_.get<pdf1_7::Array<pdf1_7::HexString>>(kId);
		}
		/*! \brief Returns the dictionary_.*/
		inline Dictionary &dictionary()
		{
			return dictionary_;
		}
		/*! \brief Adds optional entries into the dictionary_.*/
		inline void prepare4Reading()
		{
			dictionary_.insert<Integer>(kPrev);
			dictionary_.insert<IndirectReference>(kRoot);
			dictionary_.insert<Dictionary>(kEncrypt);
			dictionary_.insert<IndirectReference>(kInfo);
			dictionary().insert<pdf1_7::Array<pdf1_7::HexString>>(pdf1_0::Name("ID"));
		}
		
	private:
		Dictionary dictionary_;
	};
	/*! \brief PDF File Version.*/
	struct Version
	{
		pdf1_0::FileStructure::XrefSection xrefSection_;
		Trailer trailer_;
	};

	std::vector<Version> versions_;
};
	
}

}