#pragma once

#include <vector>

#include "integer.h"

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
};
	
}

}