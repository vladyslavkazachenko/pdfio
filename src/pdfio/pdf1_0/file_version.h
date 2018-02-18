#pragma once

#include <vector>

#include "file_xref.h"
#include "file_trailer.h"

namespace pdfio
{
	
namespace pdf1_0
{
	/*! \brief PDF file version.*/
	class FileVersion
	{
	public:
		/*! \brief Constructs the file version.*/
		inline FileVersion()
		{
			
		}
		/*! \brief Returns byte offset of the file version.*/
		inline const std::size_t &beginOffset() const
		{
			return beginOffset_;
		}
		/*! \brief Returns byte offset of the beginning of the file version.*/
		inline std::size_t &beginOffset()
		{
			return beginOffset_;
		}
		/*! \brief Returns byte offset of the end of the file version.*/
		inline const std::size_t &endOffset() const
		{
			return endOffset_;
		}
		/*! \brief Returns byte offset of the file version.*/
		inline std::size_t &endOffset()
		{
			return endOffset_;
		}
		/*! \brief Returns cross reference table of the file version.*/
		inline const FileXref &xref() const
		{
			return xref_;
		}
		/*! \brief Returns cross reference table of the file version.*/
		inline FileXref &xref()
		{
			return xref_;
		}
		/*! \brief Returns trailer of the file version.*/
		inline const FileTrailer &trailer() const
		{
			return trailer_;
		}
		/*! \brief Returns trailer of the file version.*/
		inline FileTrailer &trailer()
		{
			return trailer_;
		}
		
	private:
		std::size_t beginOffset_ = 0;
		std::size_t endOffset_ = 0;
		FileXref xref_;
		FileTrailer trailer_;
	};
}

}