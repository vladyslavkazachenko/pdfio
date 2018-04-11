#include "pdfio/pdf1_0/istream/include.h"
#include "read_file_structure.h"
#include "read_array.h"
#include "read_document_catalog.h"

using namespace pdfio;
using namespace pdfio::pdf1_7;

ReadHandlerRegistrator<pdfio::pdf1_7::FileStructure::XrefStream> xrefStreamRegistrator(
   [](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<pdfio::pdf1_7::FileStructure::XrefStream> &>(o).object_;
   });
   
ReadHandlerRegistrator<pdfio::pdf1_7::Array<pdfio::pdf1_7::Dictionary>> arrDictRegistrator(
   [](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<pdfio::pdf1_7::Array<pdfio::pdf1_7::Dictionary>> &>(o).object_;
   });
   
ReadHandlerRegistrator<pdfio::pdf1_7::Array<pdfio::pdf1_7::DocumentCatalog::OutputIntent>> outputIntentRegistrator(
   [](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<pdfio::pdf1_7::Array<pdfio::pdf1_7::DocumentCatalog::OutputIntent>> &>(o).object_;
   });

   
ReadHandlerRegistrator<pdfio::pdf1_7::DocumentCatalog> docCatalog1_7Registrator(
   [](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<pdfio::pdf1_7::DocumentCatalog> &>(o).object_;
   });