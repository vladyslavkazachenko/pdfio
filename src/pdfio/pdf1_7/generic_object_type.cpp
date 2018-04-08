#include "generic_object_type.h"

using namespace pdfio;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <> int GenericObject::TypeId<pdf1_7::FileStructure::XrefStream>()
{
  return static_cast<int>(pdf1_7::GenericObjectType::kXrefStream);
}

template <> int GenericObject::TypeId<pdf1_7::Array<pdf1_7::Dictionary>>()
{
	return static_cast<int>(pdf1_7::GenericObjectType::kArrayDictionary);
}

template <> int GenericObject::TypeId<pdf1_7::Array<pdf1_7::DocumentCatalog::OutputIntent>>()
{
	return static_cast<int>(pdf1_7::GenericObjectType::kOutputIntents);
}

template <> int GenericObject::TypeId<pdf1_7::LiteralString>()
{
	return static_cast<int>(pdf1_7::GenericObjectType::kLiteralString);
}

template <> int GenericObject::TypeId<pdf1_7::DocumentCatalog>()
{
	return static_cast<int>(pdf1_7::GenericObjectType::kDocumentCatalog);
}

#endif //DOXYGEN_SHOULD_SKIP_THIS