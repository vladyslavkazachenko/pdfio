#include "read_file_structure.h"

#include "pdfio/log.h"
#include "pdfio/pdf1_0/istream/read_file_structure.h"

namespace pdf1_4 = pdfio::pdf1_4;
namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
   ":istream[" << std::hex << std::showbase << \
   reinterpret_cast<unsigned long>(&istream) << \
   "],trailer[" << reinterpret_cast<unsigned long>(&trailer) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::FileStructure::Trailer &trailer)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   trailer.prepare4Reading();
   istream >> static_cast<pdf1_0::FileStructure::Trailer &>(trailer);
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}
