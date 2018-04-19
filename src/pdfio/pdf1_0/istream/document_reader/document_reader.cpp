#include "document_reader.h"

#include <cassert>

#include "pdfio/log.h"
#include "pdfio/pdf1_0/istream/read_document_pages_tree.h"
   
namespace pdfio
{
   
namespace pdf1_0
{
   
#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << \
   "],fullFilePath[" << reinterpret_cast<unsigned long>(&fullFilePath) << "]:"
   
bool DocumentReader::loadFile(const std::string &fullFilePath)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   LOG_DEBUG(LOG_PREFIX << "fullFilePath=" << fullFilePath << "\n");
   bool result = true;
   if(fileReader_.loadFile(fullFilePath))
   {
      if(!fileReader_.getDocumentCatalog(catalog_))
      {
         result = false;
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "failed to load file " << fullFilePath << "\n");
      result = false;
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return result;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << \
   "],pageTree[" << reinterpret_cast<unsigned long>(&pageTree) << "]:"

bool DocumentReader::getPageTree(PageTree &pageTree) const
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   pageTree.setRoot(catalog_.pages());
   pageTree.setFileReader(fileReader_);
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return true;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << \
   "],root[" << reinterpret_cast<unsigned long>(&root) << "]:"

void DocumentReader::PageTree::setRoot(const IndirectReference &root)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   LOG_DEBUG(LOG_PREFIX << "root=(" << std::dec << root.objectNumber() << " " << root.generationNumber() << ")\n");
   root_ = root;
   LOG_DEBUG(LOG_PREFIX << "leave\n");
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << \
   "],fileReader[" << reinterpret_cast<unsigned long>(&fileReader) << "]:"

void DocumentReader::PageTree::setFileReader(FileReader &fileReader)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   fileReader_ = &fileReader;
   LOG_DEBUG(LOG_PREFIX << "leave\n");
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   "this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << \
   "],pageNumber[" << reinterpret_cast<unsigned long>(&pageNumber) << "]:"

bool DocumentReader::PageTree::getPageNumber(std::size_t &pageNumber) const
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   bool success = true;
   DocumentPagesTree root;
   if(fileReader_->getObject(root_.objectNumber(), root_.generationNumber(), root))
   {
      if(root.isTree())
      {
         if(root.hasCount())
         {
            pageNumber = root.count();
         }
         else
         {
            LOG_ERROR(LOG_PREFIX << "catalog pages doesn't have count\n");
            success = false;
         }
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "catalog pages is not a tree\n");
         success = false;
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "failed to get catalog pages\n");
      success = false;
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return success;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   "this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << \
   "],page[" << reinterpret_cast<unsigned long>(&page) << "]:"

bool DocumentReader::PageTree::getFirstPage(Page &page)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   auto success = getFirstPage(root_, page);
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return success;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << \
   "],nodeRef[" << reinterpret_cast<unsigned long>(&nodeRef) << \
   "],page[" << reinterpret_cast<unsigned long>(&page) << "]:"

bool DocumentReader::PageTree::getFirstPage(const IndirectReference &nodeRef, Page &page)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   LOG_DEBUG(LOG_PREFIX << "nodeRef=(" << std::dec << nodeRef.objectNumber() << " " << nodeRef.generationNumber() << ")\n");
   bool success = true;
   DocumentPagesTree node;
   if(fileReader_->getObject(nodeRef.objectNumber(), nodeRef.generationNumber(), node))
   {
      if(!node.isTree())
      {
         page.setRef(nodeRef);
         page.setFileReader(*fileReader_);
      }
      else
      {
         std::size_t i = 0;
         while(i < node.kids().size())
         {
            if(!getFirstPage(node.kids()[i], page))
            {
               ++i;
            }
            else
            {
               break;
            }
         }
         if(i == node.kids().size())
         {
            LOG_ERROR(LOG_PREFIX << "no pages found\n");
            success = false;
         }
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "failed to get node\n");
      success = false;
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return success;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << \
   "],page[" << reinterpret_cast<unsigned long>(&page) << \
   "],nextPage[" << reinterpret_cast<unsigned long>(&nextPage) << "]:"

bool DocumentReader::PageTree::getNextPage(const Page &page, Page &nextPage, bool &isLast)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   LOG_DEBUG(LOG_PREFIX << "page=(ref=" << std::dec << page.ref().objectNumber() << " " << page.ref().generationNumber() << ")\n");
   bool success = true;
   IndirectReference parentRef;
   if(page.getParent(parentRef))
   {
      success = getNextPage(page.ref(), parentRef, nextPage, isLast);
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "failed to get page parent\n");
      success = false;
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return success;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << \
   "],currentRef[" << reinterpret_cast<unsigned long>(&currentRef) << \
   "],parentRef[" << reinterpret_cast<unsigned long>(&parentRef) << \
   "],nextPage[" << reinterpret_cast<unsigned long>(&nextPage) << "]:"

bool DocumentReader::PageTree::getNextPage(const IndirectReference &currentRef, const IndirectReference &parentRef, Page &nextPage, bool &isLast)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   LOG_DEBUG(LOG_PREFIX << "currentRef=(" << std::dec << currentRef.objectNumber() << " " << currentRef.generationNumber() << 
      "),parentRef=" << parentRef.objectNumber() << " " << parentRef.generationNumber() << ")\n");
   bool success = true;
   DocumentPagesTree parent;
   if(fileReader_->getObject(parentRef.objectNumber(), parentRef.generationNumber(), parent))
   {
      if(parent.hasKids())
      {
         std::size_t i = 0;
         for(; i < parent.kids().size() && !(parent.kids()[i] == currentRef); ++i);
         if(i < parent.kids().size())
         {
            ++i;
            for(; i < parent.kids().size(); ++i)
            {
               if(getFirstPage(parent.kids()[i], nextPage))
               {
                  break;
               }
            }
            if(i == parent.kids().size())
            {
               if(parent.hasParent())
               {
                  success = getNextPage(parentRef, parent.parent(), nextPage, isLast);
               }
               else
               {
                  isLast = true;
                  success = false;
               }
            }
         }
         else
         {
            LOG_ERROR(LOG_PREFIX << "page is not found among parent kids\n");
            success = false;
         }
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "parent doesn't have kids\n");
         success = false;
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "failed to get parent\n");
      success = false;
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return success;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << \
   "],ref[" << reinterpret_cast<unsigned long>(&ref) << "]:"

void DocumentReader::Page::setRef(const IndirectReference &ref)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   LOG_DEBUG(LOG_PREFIX << "parentRef=" << std::dec << ref.objectNumber() << " " << ref.generationNumber() << ")\n");
   ref_ = ref;
   LOG_DEBUG(LOG_PREFIX << "leave\n");
}

#undef LOG_PREFIX

const IndirectReference &DocumentReader::Page::ref() const
{
   return ref_;
}

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << \
   "],fileReader[" << reinterpret_cast<unsigned long>(&fileReader) << "]:"

void DocumentReader::Page::setFileReader(FileReader &fileReader)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   fileReader_ = &fileReader;
   LOG_DEBUG(LOG_PREFIX << "leave\n");
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << \
   "],parent[" << reinterpret_cast<unsigned long>(&parent) << "]:"

bool DocumentReader::Page::getParent(IndirectReference &parent) const
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   bool success = true;
   if(checkImp())
   {
      if(imp_.hasParent())
      {
         parent = imp_.parent();
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "page doesn't have parent\n");
         success = false;
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "implementation checking failed\n");
      success = false;
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return success;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << \
   "],mediaBox[" << reinterpret_cast<unsigned long>(&mediaBox) << "]:"

bool DocumentReader::Page::getMediaBox(MediaBox &mediaBox) const
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   bool success = true;
   if(checkImp())
   {
      if(imp_.hasMediaBox())
      {
         if(imp_.mediaBox().size() == 4)
         {
            mediaBox = std::tie(imp_.mediaBox()[0], imp_.mediaBox()[1], imp_.mediaBox()[2], imp_.mediaBox()[3]);
         }
         else
         {
            LOG_ERROR(LOG_PREFIX << "media box has " << imp_.mediaBox().size() << " components\n");
            success = false;
         }
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "page doesn't have media box\n");
         success = false;
      }
   }
   else
   {
      LOG_ERROR(LOG_PREFIX << "implementation checking failed\n");
      success = false;
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return success;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":this[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(this) << "]:"

bool DocumentReader::Page::checkImp() const
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   bool success = true;
   if(!isImpReady_)
   {
      assert(fileReader_);
      if(fileReader_->getObject(ref_.objectNumber(), ref_.generationNumber(), imp_))
      {
         isImpReady_ = true;
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "failed to get page\n");
         success = false;
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return success;
}

#undef LOG_PREFIX

}

}
