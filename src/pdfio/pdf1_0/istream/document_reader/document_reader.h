#pragma once

#include <tuple>
#include <functional>
#include <map>

#include "pdfio/pdf1_0/document_page.h"
#include "pdfio/pdf1_0/document_catalog.h"
#include "pdfio/pdf1_0/document_pages_tree.h"
#include "file_reader.h"

namespace pdfio
{

namespace pdf1_0
{
	
class DocumentReader
{
public:
	class Page
	{
	public:
      typedef std::tuple<Integer, Integer, Integer, Integer> MediaBox;
      void setRef(const IndirectReference &ref);
      const IndirectReference &ref() const;
      void setFileReader(FileReader &fileReader);
      bool getParent(IndirectReference &parent) const;

		bool getMediaBox(MediaBox &mediaBox) const;
		
	private:
      bool checkImp() const;
      
      IndirectReference ref_;
      FileReader *fileReader_ = nullptr;
		mutable DocumentPagesTree imp_;
		mutable bool isImpReady_ = false;
	};
	class PageTree
	{
	public:
      void setRoot(const IndirectReference &root);
      void setFileReader(FileReader &fileReader);
      
      bool getPageNumber(std::size_t &pageNumber) const;
	   bool getFirstPage(Page &page);
      bool getNextPage(const Page &page, Page &nextPage, bool &isLast);
      
   private:
      bool getFirstPage(const IndirectReference &node, Page &page);
      bool getNextPage(const IndirectReference &currentRef, 
         const IndirectReference &parentRef, Page &nextPage, 
         bool &isLast);
      
      IndirectReference root_;
      FileReader *fileReader_ = nullptr;
	};
   
   bool loadFile(const std::string &fullFilePath);
   bool getPageTree(PageTree &pageTree) const;
   
   mutable FileReader fileReader_;
   mutable DocumentCatalog catalog_;
};
	
}	

}
