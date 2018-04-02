#pragma once

#include "pdfio/pdf1_0/file_trailer.h"
#include "hexstring.h"
#include "array.h"

namespace pdfio
{
	
namespace pdf1_7
{
	
class FileTrailer: public pdf1_0::FileTrailer
{
public:
	inline FileTrailer()
	{
		
	}
	inline bool hasID() const
	{
		return dictionary().contains(pdf1_0::Name("ID"));
	}
	inline const Array<HexString> &id() const
	{
		return dictionary().get<pdf1_7::Array<pdf1_7::HexString>>(pdf1_0::Name("ID"));
	}
	inline Array<HexString> &id()
	{
		if(!hasID())
		{
			pdf1_7::Array<pdf1_7::HexString> id(2);
			dictionary().insert<pdf1_7::Array<pdf1_7::HexString>>(pdf1_0::Name("ID"), id);
		}
		return dictionary().get<pdf1_7::Array<pdf1_7::HexString>>(pdf1_0::Name("ID"));
	}
	inline void prepare4Reading()
	{
		pdf1_0::FileTrailer::prepare4Reading();
		pdf1_7::Array<pdf1_7::HexString> id(2);
		dictionary().insert<pdf1_7::Array<pdf1_7::HexString>>(pdf1_0::Name("ID"), id);
	}
};
	
}
	
}