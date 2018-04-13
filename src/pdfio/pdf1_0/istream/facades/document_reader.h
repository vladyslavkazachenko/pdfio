#pragma once

#include <vector>
#include <map>
#include <memory>

#include "file_reader.h"
#include "pdfio/pdf1_0/array.h"
#include "pdfio/pdf1_0/real.h"
#include "pdfio/pdf1_0/indirect_reference.h"
#include "pdfio/pdf1_0/document_page.h"
#include "pdfio/pdf1_0/document_page_tree_node.h"

namespace pdfio
{
   
namespace pdf1_0
{
   
class DocumentReader
{
public:
   enum class PageMode
   {
      kUseNone,
      kUseOutlines,
      kUseThumbs,
   };
   
   bool loadFile(const std::string &fullFilePath);
   template <typename T> bool getObject(Integer objectNumber, Integer generation, T &object) const
   {
      return fileReader_.getObject(objectNumber, generation, object);
   }
   
   bool getPageMode(int &pageMode) const;
   bool getPageNumber(std::size_t &pageNumber) const;
   bool getPageMediaBox(std::size_t index, Integer &x_ll, Integer &y_ll, Integer &x_ur, Integer &y_ur) const;
   
private:
   bool buildPageTree(const IndirectReference &nodeRef, std::vector<IndirectReference> &pages) const;
   
   mutable FileReader fileReader_;
   DocumentCatalog catalog_;
   mutable bool hasCachedPages_ = false;
   mutable std::vector<IndirectReference> pages_;
};
   
}
   
}