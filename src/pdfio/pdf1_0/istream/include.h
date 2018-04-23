#include "read_name.h"
#include "read_indirect_reference.h"
#include "read_dictionary.h"
#include "read_hexstring.h"
#include "read_array.h"
#include "read_stream.h"
#include "read_document_catalog.h"
#include "read_outline_tree.h"
#include "read_literalstring.h"
#include "read_string.h"
#include "read_document_pages_tree.h"
#include "read_info.h"
#include "pdfio/pdf1_0/real.h"
#include "pdfio/read_generic_object.h"

using namespace pdfio;
using namespace pdfio::pdf1_0;

ReadHandlerRegistrator<Name> nameRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Name> &>(o).object_;
   });
   
ReadHandlerRegistrator<Integer> integerRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Integer> &>(o).object_;
   });
   
ReadHandlerRegistrator<IndirectReference> indirectRefRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<IndirectReference> &>(o).object_;
   });
   
ReadHandlerRegistrator<Dictionary> dictionaryRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Dictionary> &>(o).object_;
   });
   
ReadHandlerRegistrator<Array<HexString>> arrHexStringRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Array<HexString>> &>(o).object_;
   });
   
ReadHandlerRegistrator<Real> realRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Real> &>(o).object_;
   });
   
ReadHandlerRegistrator<Stream> streamRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Stream> &>(o).object_;
   });
   
ReadHandlerRegistrator<Array<Integer>> arrIntegerRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Array<Integer>> &>(o).object_;
   });
   
ReadHandlerRegistrator<DocumentCatalog> docCatalogRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<DocumentCatalog> &>(o).object_;
   });
   
ReadHandlerRegistrator<Array<IndirectReference>> arrIndirRefRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Array<IndirectReference>> &>(o).object_;
   });
   
ReadHandlerRegistrator<Array<Real>> arrRealRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Array<Real>> &>(o).object_;
   });
   
ReadHandlerRegistrator<Array<Name>> arrNameRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Array<Name>> &>(o).object_;
   });
   
ReadHandlerRegistrator<OutlineTree> outlineTreeRegistrator(
   [](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<OutlineTree> &>(o).object_;
   });
   
ReadHandlerRegistrator<OutlineTree::Entry> outlineTreeEntryRegistrator(
   [](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<OutlineTree::Entry> &>(o).object_;
   });
   
ReadHandlerRegistrator<LiteralString> literalStringRegistrator(
   [](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<LiteralString> &>(o).object_;
   });

ReadHandlerRegistrator<String> stringRegistrator(
   [](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<String> &>(o).object_;
   });
   
ReadHandlerRegistrator<DocumentPagesTree> docPagesTreeRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<DocumentPagesTree> &>(o).object_;
   });

ReadHandlerRegistrator<Info> infoRegistrator(
   [](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Info> &>(o).object_;
   });
