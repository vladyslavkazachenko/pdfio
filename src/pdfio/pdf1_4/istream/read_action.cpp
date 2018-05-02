#include "read_action.h"

#include "pdfio/log.h"
#include "read_dictionary.h"

namespace pdf1_4 = pdfio::pdf1_4;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
  "],action[" << reinterpret_cast<unsigned long>(&action) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_4::Action &action)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   action.prepare4Reading();
   static_cast<void>(istream >> static_cast<pdf1_4::Dictionary &>(action));
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}
