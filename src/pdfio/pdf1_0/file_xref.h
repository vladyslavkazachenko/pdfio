#pragma once

#include <vector>

#include "integer.h"

namespace pdfio
{
	
namespace pdf1_0
{
	
/*! \brief PDF file cross reference table.*/
class FileXref
{
public:
	/*! \brief PDF file cross reference table subsection entry.*/
	class Entry
	{
	public:
		/*! \brief Returns the entry's byte offset.*/
		inline const Integer &byteOffset() const
		{
			return byteOffset_;
		}
		/*! \brief Returns the entry's byte offset.*/
		inline Integer &byteOffset()
		{
			return byteOffset_;
		}
		/*! \brief Returns the entry's generation number.*/
		inline const Integer &generationNumber() const
		{
			return generationNumber_;
		}
		/*! \brief Returns the entry's generation number.*/
		inline Integer &generationNumber()
		{
			return generationNumber_;
		}
		/*! \brief Returns the entry's in-use/free flag.*/
		inline const bool &isInUse() const
		{
			return isInUse_;
		}
		/*! \brief Returns the entry's in-use/free flag.*/
		inline bool &isInUse()
		{
			return isInUse_;
		}
		
	private:
		Integer byteOffset_ = Integer();
		Integer generationNumber_ = Integer();
		bool isInUse_ = true;
	};
	/*! \brief PDF file cross reference table subsection.*/
	class Subsection
	{
	public:
		/*! \brief Returns the first entry's object number in the subsection.*/
		inline const Integer &objectNumber() const
		{
			return objectNumber_;
		}
		/*! \brief Returns the first entry's object number in the subsection.*/
		inline Integer &objectNumber()
		{
			return objectNumber_;
		}
		/*! \brief Returns the subsection entries.*/
		inline const std::vector<Entry> &entries() const
		{
			return entries_;
		}
		/*! \brief Returns the subsection entries.*/
		inline std::vector<Entry> &entries()
		{
			return entries_;
		}
		
	private:
		Integer objectNumber_ = Integer();
		std::vector<Entry> entries_;
	};
	/*! \brief PDF file cross reference table section.*/
	class Section
	{
	public:					
		/*! \brief Returns the section's subsections.*/
		inline const std::vector<Subsection> &subsections() const
		{
			return subsections_;
		}
		/*! \brief Returns the section's subsections.*/
		inline std::vector<Subsection> &subsections()
		{
			return subsections_;
		}
		
	private:
		std::vector<Subsection> subsections_;
	};
	/*! \brief Returns the cross reference table section of the xref.*/
	inline const Section &section() const
	{
		return section_;
	}
	/*! \brief Returns the cross reference table section of the xref.*/
	inline Section &section()
	{
		return section_;
	}
	
private:
	Section section_;
};

}

}