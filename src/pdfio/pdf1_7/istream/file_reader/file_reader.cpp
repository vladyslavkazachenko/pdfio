#include "file_reader.h"

#include "pdfio/pdf1_7/istream/include.h"

namespace pdfio
{
	
namespace pdf1_7
{
	
bool FileReader::loadFile(const std::string &fullFilePath)
{
	stream_.open(fullFilePath.c_str(), std::ios_base::binary | std::ios_base::in);
	if(!stream_.is_open())
	{
		return false;
	}
	if(!(stream_ >> fileStruct_))
	{
		return false;
	}
	return true;
}

bool FileReader::getDocumentCatalog(DocumentCatalog &docCatalog)
{
	int i = fileStruct_.versions_.size() - 1;
	for(; i >= 0; --i)
	{
		if(fileStruct_.versions_[i].trailer_.hasRoot())
		{
			break;
		}
	}
	if(i < 0)
	{
		return false;
	}
	auto &trailer = fileStruct_.versions_[i].trailer_;
	return getObject(trailer.root().objectNumber(), trailer.root().generationNumber(), docCatalog);
}

std::streampos FileReader::findObject(Integer objectNumber, Integer generation)
{
	for(auto version : fileStruct_.versions_)
	{
		auto &xrefSection = version.xrefSection_;
		for(size_t i = 0; i < xrefSection.subsections().size(); ++i)
		{
			const auto &subsection = xrefSection.subsections()[i];
			for(size_t j = 0; j < subsection.entries_.size(); ++j)
			{
				const auto &entry = subsection.entries_[j];				
				if((subsection.firstObjectNumber_ + static_cast<int>(j)) == objectNumber && (entry.generation_ == generation))
				{
					return static_cast<std::streampos>(entry.offset_);
				}
			}
		}
	}
	return -1;
}
	
}

}