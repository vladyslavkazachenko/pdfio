#include "document_reader.h"

#include <future>

#include "pdfio/pdf1_0/document_page_tree_root_node.h"

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
   return true;
}

int DocumentReader::pageMode()
{
   return PageMode2Int(catalog_.pageMode());
}

const std::vector<DocumentReader::Page> &DocumentReader::pages() const
{
   if(!hasCachedPages_)
   {
      DocumentPageTreeRootNode root;
      if(!getObject(catalog_.pages().objectNumber(), catalog_.pages().generationNumber(), root))
      {
         return pages_;
      }
      hasCachedPages_ = false;
      visitPageTreeNode(root);
   }
   return pages_;
}

void DocumentReader::visitPageTreeNode(const DocumentPageTreeNode &node) const
{
   if(node.get<Name>(Name("Type")) == "Pages")
   {
      auto &rootTreenode = static_cast<const DocumentPageTreeRootNode &>(node);
      auto kids = rootTreenode.kids();
      for(size_t i = 0; i < kids.size(); ++i)
      {
         DocumentPageTreeRootNode child;
         if(getObject(kids[i].objectNumber(), kids[i].generationNumber(), child))
         {
            visitPageTreeNode(child);
         }
         else
         {
            Page page(*this, kids[i]);
            pages_.push_back(page);
         }
      }
   }
}

std::vector<DocumentReader::Page> DocumentReader::children(const DocumentPageTreeNode &node) const
{
   std::vector<Page> result;
   if(node.get<Name>(Name("Type")) == "Pages")
   {
      auto &rootTreenode = static_cast<const DocumentPageTreeRootNode &>(node);
      auto kids = rootTreenode.kids();
      std::vector<std::future<std::vector<Page>>> futures;
      for(size_t i = 0; i < kids.size(); ++i)
      {
         auto f = std::async(i < 2 ? std::launch::async : std::launch::deferred, [this, &kids, i]()
            {
               DocumentPageTreeRootNode child;
               if(getObject(kids[i].objectNumber(), kids[i].generationNumber(), child))
               {
                  return children(child);
               }
               return std::vector<Page>({Page(*this, kids[i])});
            });
         futures.push_back(std::move(f));
      }
      for(auto &future : futures)
      {
         auto f = future.get();
         for(auto a : f)
         {
            result.push_back(a);
         }
      }
   }
   return result;
}

DocumentReader::Page::Page(const DocumentReader &parent, const IndirectReference &pageRef)
: parent_(parent)
, pageRef_(pageRef)
{
   
}

const Array<Real> &DocumentReader::Page::mediaBox() const
{
   if(!hasCache_)
   {
      if(!parent_.getObject(pageRef_.objectNumber(), pageRef_.generationNumber(), cachedValue_))
      {
         cachedValue_.mediaBox().resize(4);
      }
      hasCache_ = true;
   }
   return cachedValue_.mediaBox();
}
   
}

}