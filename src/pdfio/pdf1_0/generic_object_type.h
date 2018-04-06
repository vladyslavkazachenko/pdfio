#pragma once

#include "name.h"
#include "integer.h"
#include "indirect_reference.h"
#include "dictionary.h"
#include "indirect_object.h"
#include "array.h"
#include "document_page.h"
#include "document_catalog.h"
#include "document_page_tree_root_node.h"
#include "stream.h"
#include "hexstring.h"
#include "real.h"
#include "pdfio/generic_object.h"

namespace pdfio
{
  
namespace pdf1_0
{
  
enum class GenericObjectType
{
  kName,
  kInteger,
  kIndirectReference,
  kDictionary,
  kIndirectObject,
  kArrayIndirectReference,
  kArrayInteger,
  kArrayHexString,
  kDocumentPageResources,
  kDocumentPageResourceDictionary,
  kDocumentPageProcSet,
  kDocumentCatalog,
  kDocumentPageTreeRootNode,
  kDocumentPage,
  kStream,
  kHexString,
  kReal,
};

}
/*! \brief Returns type id of Name.*/
template <> int GenericObject::TypeId<pdf1_0::Name>();
/*! \brief Returns type id of Integer.*/
template <> int GenericObject::TypeId<pdf1_0::Integer>();
/*! \brief Returns type id of IndirectReference.*/
template <> int GenericObject::TypeId<pdf1_0::IndirectReference>();
/*! \brief Returns type id of Dictionary.*/
template <> int GenericObject::TypeId<pdf1_0::Dictionary>();
/*! \brief Returns type id of IndirectObject.*/
template <> int GenericObject::TypeId<pdf1_0::IndirectObject>();
/*! \brief Returns type id of Array<IndirectReference>.*/
template <> int GenericObject::TypeId<pdf1_0::Array<pdf1_0::IndirectReference>>();
/*! \brief Returns type id of Array<Integer>.*/
template <> int GenericObject::TypeId<pdf1_0::Array<pdf1_0::Integer>>();
/*! \brief Returns type id of Array<HexString>.*/
template <> int GenericObject::TypeId<pdf1_0::Array<pdf1_0::HexString>>();
/*! \brief Returns type id of DocumentPage::Resources.*/
template <> int GenericObject::TypeId<pdf1_0::DocumentPage::Resources>();
/*! \brief Returns type id of DocumentPage::ResourceDictionary.*/
template <> int GenericObject::TypeId<pdf1_0::DocumentPage::ResourceDictionary>();
/*! \brief Returns type id of DocumentPage::ProcSet.*/
template <> int GenericObject::TypeId<pdf1_0::DocumentPage::ProcSet>();
/*! \brief Returns type id of DocumentCatalog.*/
template <> int GenericObject::TypeId<pdf1_0::DocumentCatalog>();
/*! \brief Returns type id of DocumentPageTreeRootNode.*/
template <> int GenericObject::TypeId<pdf1_0::DocumentPageTreeRootNode>();
/*! \brief Returns type id of DocumentPage.*/
template <> int GenericObject::TypeId<pdf1_0::DocumentPage>();
/*! \brief Returns type id of Stream.*/
template <> int GenericObject::TypeId<pdf1_0::Stream>();
/*! \brief Returns type id of Real.*/
template <> int GenericObject::TypeId<pdf1_0::Real>();
  
}