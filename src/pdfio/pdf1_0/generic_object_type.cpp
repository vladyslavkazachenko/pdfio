#include "generic_object_type.h"

using namespace pdfio;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <> int GenericObject::TypeId<pdf1_0::Name>()
{
  return static_cast<int>(pdf1_0::GenericObjectType::kName);
}

template <> int GenericObject::TypeId<pdf1_0::Integer>()
{
  return static_cast<int>(pdf1_0::GenericObjectType::kInteger);
}

template <> int GenericObject::TypeId<pdf1_0::IndirectReference>()
{
  return static_cast<int>(pdf1_0::GenericObjectType::kIndirectReference);
}

template <> int GenericObject::TypeId<pdf1_0::Dictionary>()
{
  return static_cast<int>(pdf1_0::GenericObjectType::kDictionary);
}

template <> int GenericObject::TypeId<pdf1_0::IndirectObject>()
{
  return static_cast<int>(pdf1_0::GenericObjectType::kIndirectObject);
}

template <> int GenericObject::TypeId<pdf1_0::Array<pdf1_0::IndirectReference>>()
{
  return static_cast<int>(pdf1_0::GenericObjectType::kArrayIndirectReference);
}

template <> int GenericObject::TypeId<pdf1_0::Array<pdf1_0::Integer>>()
{
  return static_cast<int>(pdf1_0::GenericObjectType::kArrayInteger);
}

template <> int GenericObject::TypeId<pdf1_0::Array<pdf1_0::HexString>>()
{
  return static_cast<int>(pdf1_0::GenericObjectType::kArrayHexString);
}

template <> int GenericObject::TypeId<pdf1_0::LiteralString>()
{
   return static_cast<int>(pdf1_0::GenericObjectType::kLiteralString);
}

template <> int GenericObject::TypeId<pdf1_0::String>()
{
   return static_cast<int>(pdf1_0::GenericObjectType::kString);
}

template <> int GenericObject::TypeId<pdf1_0::Array<pdf1_0::Real>>()
{
   return static_cast<int>(pdf1_0::GenericObjectType::kArrayReal);
}

template <> int GenericObject::TypeId<pdf1_0::Array<pdf1_0::Name>>()
{
   return static_cast<int>(pdf1_0::GenericObjectType::kArrayName);
}

template <> int GenericObject::TypeId<pdf1_0::DocumentCatalog>()
{
  return static_cast<int>(pdf1_0::GenericObjectType::kDocumentCatalog);
}

template <> int GenericObject::TypeId<pdf1_0::Stream::Filter>()
{
   return static_cast<int>(pdf1_0::GenericObjectType::kStreamFilter);
}

template <> int GenericObject::TypeId<pdf1_0::Stream>()
{
  return static_cast<int>(pdf1_0::GenericObjectType::kStream);
}

template <> int GenericObject::TypeId<pdf1_0::OutlineTree>()
{
   return static_cast<int>(pdf1_0::GenericObjectType::kOutlineTree);
}

template <> int GenericObject::TypeId<pdf1_0::OutlineTree::Entry>()
{
   return static_cast<int>(pdf1_0::GenericObjectType::kOutlineTreeEntry);
}

template <> int GenericObject::TypeId<pdf1_0::DocumentPagesTree>()
{
   return static_cast<int>(pdf1_0::GenericObjectType::kDocumentPagesTree);
}

template <> int GenericObject::TypeId<pdf1_0::Info>()
{
   return static_cast<int>(pdf1_0::GenericObjectType::kInfo);
}

template <> int GenericObject::TypeId<pdf1_0::Real>()
{
  return static_cast<int>(pdf1_0::GenericObjectType::kReal);
}

#endif //DOXYGEN_SHOULD_SKIP_THIS
