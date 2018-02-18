#pragma once

namespace pdfio
{
	
namespace pdf1_0
{
	/*! \brief PDF file header.*/
	class FileHeader
	{
	public:
		/*! \brief Returns PDF version's major component.*/
		inline const int &majorVersion() const
		{
			return majorVersion_;
		}
		/*! \brief Returns PDF version's major component.*/
		inline int &majorVersion()
		{
			return majorVersion_;
		}
		/*! \brief Returns PDF version's minor component.*/
		inline const int &minorVersion() const
		{
			return minorVersion_;
		}
		/*! \brief Returns PDF version's minor component.*/
		inline int &minorVersion()
		{
			return minorVersion_;
		}
		
	private:
		int majorVersion_ = 1;
		int minorVersion_ = 0;
	};
}

}