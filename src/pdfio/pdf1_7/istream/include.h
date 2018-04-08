#include "pdfio/pdf1_0/istream/include.h"
#include "read_file_structure.h"

using namespace pdfio;
using namespace pdfio::pdf1_7;

ReadHandlerRegistrator<pdfio::pdf1_7::FileStructure::XrefStream> xrefStreamRegistrator(
	[](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<pdfio::pdf1_7::FileStructure::XrefStream> &>(o).object_;
   });