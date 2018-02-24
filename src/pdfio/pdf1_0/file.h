#pragma once

#include "file_header.h"
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
	/*! \brief Returns header of the file.*/
	inline const FileHeader &header() const
	{
		return header_;
	}
	/*! \brief Returns header of the file.*/
	inline FileHeader &header()
	{
		return header_;
	}
	
private:
	FileHeader header_;
	FileVersion latestVersion_;
};

}

}