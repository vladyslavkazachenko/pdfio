#pragma once

#include "generic_object.h"
#include "name.h"
#include "integer.h"
#include "indirect_reference.h"
#include "dictionary.h"
#include "indirect_object.h"
#include "array.h"
#include "document_page.h"
#include "document_catalog.h"

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
	kDocumentPageResources,
	kDocumentPageResourceDictionary,
	kDocumentCatalog,
};
/*! \brief Returns type id of Name.*/
template <> int GenericObject::TypeId<Name>();
/*! \brief Returns type id of Integer.*/
template <> int GenericObject::TypeId<Integer>();
/*! \brief Returns type id of IndirectReference.*/
template <> int GenericObject::TypeId<IndirectReference>();
/*! \brief Returns type id of Dictionary.*/
template <> int GenericObject::TypeId<Dictionary>();
/*! \brief Returns type id of IndirectObject.*/
template <> int GenericObject::TypeId<IndirectObject>();
/*! \brief Returns type id of Array<IndirectReference>.*/
template <> int GenericObject::TypeId<Array<IndirectReference>>();
/*! \brief Returns type id of Array<Integer>.*/
template <> int GenericObject::TypeId<Array<Integer>>();
/*! \brief Returns type id of DocumentPage::ResourceDictionary.*/
template <> int GenericObject::TypeId<DocumentPage::ResourceDictionary>();
/*! \brief Returns type id of DocumentPage::Resources.*/
template <> int GenericObject::TypeId<DocumentPage::Resources>();
/*! \brief Returns type id of DocumentCatalog.*/
template <> int GenericObject::TypeId<DocumentCatalog>();

}
	
}