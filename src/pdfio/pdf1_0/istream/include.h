#include "read_name.h"
#include "read_indirect_reference.h"
#include "read_dictionary.h"
#include "read_hexstring.h"
#include "read_array.h"
#include "read_stream.h"
#include "read_document_catalog.h"
#include "read_document_page_tree_root_node.h"
#include "read_document_page.h"
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
   
ReadHandlerRegistrator<DocumentPageTreeRootNode> docRootRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<DocumentPageTreeRootNode> &>(o).object_;
   });
   
ReadHandlerRegistrator<Array<IndirectReference>> arrIndirRefRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Array<IndirectReference>> &>(o).object_;
   });
   
ReadHandlerRegistrator<DocumentPage::Resources> docPageResRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<DocumentPage::Resources> &>(o).object_;
   });
   
ReadHandlerRegistrator<DocumentPage::ResourceDictionary> docPageResDictRegistrator(
   [](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<DocumentPage::ResourceDictionary> &>(o).object_;
   });
	
ReadHandlerRegistrator<Array<Real>> arrRealRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Array<Real>> &>(o).object_;
   });
	
ReadHandlerRegistrator<DocumentPage::Contents> docPageContentsRegistrator(
   [](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<DocumentPage::Contents> &>(o).object_;
   });
	
ReadHandlerRegistrator<Array<Name>> arrNameRegistrator([](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<Array<Name>> &>(o).object_;
   });
	
ReadHandlerRegistrator<DocumentPage> docPageRegistrator(
   [](std::istream &i, GenericObject &o)
   {
      i >> static_cast<GenericObjectAdaptor<DocumentPage> &>(o).object_;
   });