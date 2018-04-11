#include "read_outline_tree.h"

#include "pdfio/log.h"
#include "read_dictionary.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
  "],outlineTree[" << reinterpret_cast<unsigned long>(&outlineTree) << "]:"
  
std::istream &operator>>(std::istream &istream, pdf1_0::OutlineTree &outlineTree)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   outlineTree.prepare4Reading();
   if(istream >> static_cast<pdf1_0::Dictionary &>(outlineTree))
   {
      
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
  "],outlineTreeEntry[" << reinterpret_cast<unsigned long>(&outlineTreeEntry) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_0::OutlineTree::Entry &outlineTreeEntry)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   outlineTreeEntry.prepare4Reading();
   if(istream >> static_cast<pdf1_0::OutlineTree &>(outlineTreeEntry))
   {
      
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX