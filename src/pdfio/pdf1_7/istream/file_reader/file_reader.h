#pragma once

#include <string>
#include <fstream>

#include "pdfio/pdf1_7/file_structure.h"
#include "pdfio/pdf1_7/document_catalog.h"
#include "pdfio/pdf1_7/indirect_object.h"
#include "pdfio/pdf1_7/istream/read_indirect_object.h"

namespace pdfio
{
	
namespace pdf1_7
{
	
class FileReader
{
public:
	bool loadFile(const std::string &fullFilePath);
	bool documentCatalog(DocumentCatalog &docCatalog);
	
	template <typename T> bool getObject(Integer objectNumber, Integer generation, T &object)
	{
		auto pos = findObject(objectNumber, generation);
		if(pos == -1)
		{
			return false;
		}
		if(!stream_.seekg(pos))
		{
			return false;	
		}
		IndirectObject indirectObject;
		indirectObject.set<T>();
		if(!(stream_ >> indirectObject))
		{
			return false;
		}
		object = indirectObject.get<T>();
		return true;
	}
	
private:
	std::streampos findObject(Integer objectNumber, Integer generation);
	
	std::fstream stream_;
	FileStructure fileStruct_;
};
	
}
	
}