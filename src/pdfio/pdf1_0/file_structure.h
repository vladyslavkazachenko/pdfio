#pragma once

#include <vector>

#include "integer.h"
#include "dictionary.h"
#include "indirect_reference.h"

namespace pdfio
{
	
namespace pdf1_0
{
	
/*! \brief PDF File Structure.*/
struct FileStructure
{
	/*! \brief PDF File Cross-Reference Subsection Entry.*/
	struct XrefEntry
	{
		Integer offset_ = 0;
		Integer generation_ = 0;
		bool inUseFlag_ = true;
	};
	/*! \brief PDF File Cross-Reference Subsection.*/
	struct XrefSubsection
	{
		Integer firstObjectNumber_ = 0;
		std::vector<XrefEntry> entries_;
	};
	/*! \brief PDF File Cross-Reference Section.*/
	class XrefSection
	{
	public:
		const std::vector<XrefSubsection> &subsections() const
		{
			return subsections_;
		}
		bool add(const XrefSubsection &subsection)
		{
			subsections_.push_back(subsection);
			return true;
		}
		
	private:
		std::vector<XrefSubsection> subsections_;
	};
	
	/*! \brief PDF File Trailer.*/
	class Trailer : public virtual Dictionary
	{
	public:
		/*! \brief Constructs the Trailer by adding Integer value with key "Size"
		 *into the parent Dictionary.*/
		Trailer()
		{
			insert<Integer>(kSize);
		}
		/*! \brief Returns value by key "Size".*/
		inline const Integer &size() const
		{
			return get<Integer>(kSize);
		}
		/*! \brief Returns value by key "Size".*/
		inline Integer &size()
		{
			return get<Integer>(kSize);
		}
		/*! \brief Checks whether parent Dictionary contains entry with key "Prev".*/
		inline bool hasPrev() const
		{
			return contains(kPrev);
		}
		/*! \brief Returns value by key "Prev".*/
		inline const Integer &prev() const
		{
			return get<Integer>(kPrev);
		}
		/*! \brief Returns value by key "Prev".*/
		inline Integer &prev()
		{
			if(!hasPrev())
			{
				insert<Integer>(kPrev);
			}
			return get<Integer>(kPrev);
		}
		/*! \brief Checks whether parent Dictionary contains entry with key "Root".*/
		inline bool hasRoot() const
		{
			return contains(kRoot);
		}
		/*! \brief Returns value by key "Root".*/
		inline const IndirectReference &root() const
		{
			return get<IndirectReference>(kRoot);
		}
		/*! \brief Returns value by key "Root".*/
		inline IndirectReference &root()
		{
			return get<IndirectReference>(kRoot);
		}
		/*! \brief Checks whether parent Dictionary contains entry with key "Info".*/
		inline bool hasInfo() const
		{
			return contains(kInfo);
		}
		/*! \brief Returns value by key "Info".*/
		inline const IndirectReference &info() const
		{
			return get<IndirectReference>(kInfo);
		}
		/*! \brief Returns value by key "Info".*/
		inline IndirectReference &info()
		{
			if(!hasInfo())
			{
				insert<IndirectReference>(kInfo);
			}
			return get<IndirectReference>(kInfo);
		}
		/*! \brief Adds optional entries into the parent Dictionary.*/
		inline void prepare4Reading()
		{
			insert<Integer>(kPrev);
			insert<IndirectReference>(kRoot);
			insert<IndirectReference>(kInfo);
		}
		
	private:
		const std::string kSize = "Size";
		const std::string kPrev = "Prev";
		const std::string kRoot = "Root";
		const std::string kInfo = "Info";
	};
};
	
}

}