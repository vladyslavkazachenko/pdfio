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
#include "stream.h"
#include "name.h"

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
	class Trailer : public pdf1_0::FileStructure::Trailer
	{
	public:
		/*! \brief Assigns the other to the Trailer.*/
		Trailer &operator=(const Trailer &other)
		{
			dynamic_cast<Dictionary &>(*this) = dynamic_cast<const Dictionary &>(other);
			return *this;
		}
		/*! \brief Checks whether parent Dictionary contains entry with key "Encrypt".*/
		inline bool hasEncrypt() const
		{
			return contains(kEncrypt);
		}
		/*! \brief Checks whether parent Dictionary contains entry with key "ID".*/
		inline bool hasId() const
		{
			return contains(kId);
		}
		/*! \brief Returns value by key "ID".*/
		inline const Array<HexString> &id() const
		{
			return get<pdf1_7::Array<pdf1_7::HexString>>(kId);
		}
		/*! \brief Returns value by key "ID".*/
		inline Array<HexString> &id()
		{
			if(!hasId())
			{
				pdf1_7::Array<pdf1_7::HexString> id(2);
				insert<pdf1_7::Array<pdf1_7::HexString>>(kId, id);
			}
			return get<pdf1_7::Array<pdf1_7::HexString>>(kId);
		}
		/*! \brief Adds optional entries into the parent Dictionary.*/
		inline void prepare4Reading()
		{
			pdf1_0::FileStructure::Trailer::prepare4Reading();
			insert<Dictionary>(kEncrypt);
			insert<Array<HexString>>(kID);
		}
		
	private:
		const std::string kID = "ID";
	};
	/*! \brief PDF Cross-Reference Stream.*/
	class XrefStream: public Stream, public Trailer
	{
	public:
		XrefStream()
		: Dictionary()
		, Stream()
		, Trailer()
		{
			insert(kType, kXRef);
			insert<Array<Integer>>(kW);
		}
		/*! \brief Returns value by key "Type".*/
		inline const Name &type() const
		{
			return get<Name>(kType);
		}
		/*! \brief Returns value by key "Type".*/
		inline Name &type()
		{
			return get<Name>(kType);
		}
		/*! \brief Checks whether the parent Dictionary contains entry with key "Index".*/
		inline bool hasIndex() const
		{
			return contains(kIndex);
		}
		/*! \brief Returns value by key "Index".*/
		inline const Array<Integer> &index() const
		{
			return get<Array<Integer>>(kIndex);
		}
		/*! \brief Returns value by key "Index".*/
		inline Array<Integer> &index()
		{
			if(!hasIndex())
			{
				insert<Array<Integer>>(kIndex);
			}
			return get<Array<Integer>>(kIndex);
		}
		/*! \brief Returns value by key "W".*/
		inline const Array<Integer> &w() const
		{
			return get<Array<Integer>>(kW);
		}
		/*! \brief Returns value by key "W".*/
		inline Array<Integer> &w()
		{
			return get<Array<Integer>>(kW);
		}
		/*! \brief Adds optional entries into the parent Dictionary.*/
		inline void prepare4Reading()
		{
			Stream::prepare4Reading();
			Trailer::prepare4Reading();
			insert<Array<Integer>>(kIndex);
			insert<Integer>(kXRefStm);
		}
		
		const Name kXRef = Name("XRef");
		
	private:
		const Name kType = Name("Type");
		const Name kW = Name("W");
		const Name kIndex = Name("Index");
		const Name kXRefStm = Name("XRefStm");
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