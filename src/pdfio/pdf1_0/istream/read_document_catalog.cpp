#include "read_document_catalog.h"

#include "read_dictionary.h"
#include "pdfio/log.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << \
  reinterpret_cast<unsigned long>(&istream) << "],catalog[" << \
  reinterpret_cast<unsigned long>(&catalog) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdf1_0::DocumentCatalog &catalog)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   catalog.prepare4Read();
   if(istream >> static_cast<pdf1_0::Dictionary &>(catalog))
   {
      if(catalog.contains(pdf1_0::DocumentCatalog::kKeyType))
      {
         if(catalog.get<pdf1_0::Name>(
            pdf1_0::DocumentCatalog::kKeyType) == 
            pdf1_0::DocumentCatalog::kValueType)
         {
            if(!catalog.contains(pdf1_0::DocumentCatalog::kKeyPages))
            {
               LOG_ERROR(LOG_PREFIX << 
                  "catalog doesn't contain \"Pages\"\n");
               istream.setstate(std::ios_base::failbit);
            }
         }
         else
         {
            LOG_ERROR(LOG_PREFIX << "invalid \"Type\" value:" << 
               std::string(catalog.get<pdf1_0::Name>(
               pdf1_0::DocumentCatalog::kKeyType)) << "\n");
            istream.setstate(std::ios_base::failbit);
         }
      }
      else
      {
         LOG_ERROR(LOG_PREFIX << "catalog doesn't contain \"Type\"\n");
         istream.setstate(std::ios_base::failbit);
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}

#undef LOG_PREFIX
