#include "document_reader.h"

#include <future>

#include "pdfio/pdf1_0/document_page_tree_root_node.h"
#include "pdfio/pdf1_0/document_pages_tree.h"

namespace pdfio
{
   
namespace pdf1_0
{
   
namespace
{
   
int PageMode2Int(const Name &pageMode)
{
   if(pageMode == "UseOutlines")
   {
      return static_cast<int>(DocumentReader::PageMode::kUseOutlines);
   }
   if(pageMode == "UseThumbs")
   {
      return static_cast<int>(DocumentReader::PageMode::kUseThumbs);
   }
   return static_cast<int>(DocumentReader::PageMode::kUseNone);
}
   
}
   
bool DocumentReader::loadFile(const std::string &fullFilePath)
{
   if(!fileReader_.loadFile(fullFilePath))
   {
      return false;
   }
   if(!fileReader_.getDocumentCatalog(catalog_))
   {
      return false;
   }
   if(!buildPageTree(catalog_.pages(), pages_))
   {
      return false;
   }
   return true;
}

bool DocumentReader::getPageMode(int &pageMode) const
{
   pageMode = PageMode2Int(catalog_.pageMode());
   return true;
}

bool DocumentReader::getPageNumber(std::size_t &pageNumber) const
{
   pageNumber = pages_.size();
   return true;
}

bool DocumentReader::buildPageTree(const IndirectReference &nodeRef, std::vector<IndirectReference> &pages) const
{
   bool result = true;
   DocumentPagesTree node;
   if(!getObject(nodeRef.objectNumber(), nodeRef.generationNumber(), node))
   {
      return false;
   }
   if(node.isTree())
   {
      auto kids = node.kids();
      std::vector<IndirectReference> pages1;
      auto future1 = std::async(std::launch::async, [this, &kids, &pages1]()
         {
            bool result = true;
            for(size_t i = 0; i < kids.size() / 2; ++i)
            {
               result = result && buildPageTree(kids[i], pages1);
            }
            return result;
         });
      std::vector<IndirectReference> pages2;
      auto future2 = std::async(std::launch::async, [this, &kids, &pages2]()
         {
            bool result = true;
            for(size_t i = kids.size() / 2; i < kids.size(); ++i)
            {
               result = result && buildPageTree(kids[i], pages2);
            }
            return result;
         });
      result = result && future1.get() && future2.get();
      if(result)
      {
         for(auto i : pages1)
         {
            pages.push_back(i);
         }
         for(auto i : pages2)
         {
            pages.push_back(i);
         }
      }
   }
   else
   {
      pages.push_back(nodeRef);
   }
   return result;
}

bool DocumentReader::getPageMediaBox(std::size_t index, 
   Integer &x_ll, Integer &y_ll, Integer &x_ur, Integer &y_ur) const
{
   DocumentPagesTree node;
   if(!getObject(pages_[index].objectNumber(), pages_[index].generationNumber(), node))
   {
      return false;
   }
   x_ll = node.mediaBox()[0];
   y_ll = node.mediaBox()[1];
   x_ur = node.mediaBox()[2];
   y_ur = node.mediaBox()[3];
   return true;
}
   
}

}