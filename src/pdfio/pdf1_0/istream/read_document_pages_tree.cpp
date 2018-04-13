#include "read_document_pages_tree.h"

#include "pdfio/log.h"
#include "read_dictionary.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
   "],pagesTree[" << reinterpret_cast<unsigned long>(&pagesTree) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_0::DocumentPagesTree &pagesTree)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   pagesTree.prepare4Reading();
   pdf1_0::Dictionary &dictionary = static_cast<pdf1_0::Dictionary &>(pagesTree);
   if(istream >> dictionary)
   {
      if(dictionary.contains(pdf1_0::DocumentPagesTree::kKeyType))
      {
         if(dictionary.get<pdf1_0::Name>(pdf1_0::DocumentPagesTree::kKeyType) == 
            pdf1_0::DocumentPagesTree::kNamePages)
         {
            if(dictionary.contains(pdf1_0::DocumentPagesTree::kKeyKids))
            {
               if(dictionary.contains(pdf1_0::DocumentPagesTree::kKeyCount))
               {
                  
               }
               else
               {
                  LOG_ERROR(LOG_PREFIX << "\"Count\" is not found\n");
                  istream.setstate(std::ios_base::failbit);
               }
            }
            else
            {
               LOG_ERROR(LOG_PREFIX << "\"Kids\" is not found\n");
               istream.setstate(std::ios_base::failbit);
            }
         }
         else
         {
            
         }
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "\"Type\" is not found\n");
         istream.setstate(std::ios_base::failbit);
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX