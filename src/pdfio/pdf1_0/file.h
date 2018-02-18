#pragma once

#include "file_version.h"

namespace pdfio
{
	
namespace pdf1_0
{
	/*! \brief PDF file.*/
	class File
	{
	public:
		/*! \brief Returns latest version of the file.*/
		inline const FileVersion &latestVersion() const
		{
			return latestVersion_;
		}
		/*! \brief Returns latest version of the file.*/
		inline FileVersion &latestVersion()
		{
			return latestVersion_;
		}
		
	private:
		FileVersion latestVersion_;
	};
}

}