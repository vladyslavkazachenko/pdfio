#include "read_document_catalog.h"

#include "pdfio/pdf1_0/istream/read_document_catalog.h"
#include "pdfio/log.h"

namespace pdf1_7 = pdfio::pdf1_7;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
  "],catalog[" << reinterpret_cast<unsigned long>(&catalog) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_7::DocumentCatalog &catalog)
{
	LOG_DEBUG(LOG_PREFIX << "enter\n");
	static_cast<void>(istream >> static_cast<pdfio::pdf1_0::DocumentCatalog &>(catalog));
	LOG_DEBUG(LOG_PREFIX << "leave\n");
	return istream;
}