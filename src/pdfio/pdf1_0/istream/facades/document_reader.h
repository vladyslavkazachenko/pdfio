#pragma once

#include <vector>

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
   
   class Page
   {
   public:
      Page(const DocumentReader &parent, const IndirectReference &pageRef);
      const Array<Real> &mediaBox() const;
      
   private:
      const DocumentReader &parent_;
      const IndirectReference pageRef_;
      mutable bool hasCache_ = false;
      mutable DocumentPage cachedValue_;
   };
   
   bool loadFile(const std::string &fullFilePath);
   template <typename T> bool getObject(Integer objectNumber, Integer generation, T &object) const
   {
      return fileReader_.getObject(objectNumber, generation, object);
   }
   
   int pageMode();
   const std::vector<Page> &pages() const;
   
private:
   void visitPageTreeNode(const DocumentPageTreeNode &node) const;
   std::vector<Page> children(const DocumentPageTreeNode &node) const;
   
   mutable FileReader fileReader_;
   DocumentCatalog catalog_;
   mutable bool hasCachedPages_ = false;
   mutable std::vector<Page> pages_;
};
   
}
   
}