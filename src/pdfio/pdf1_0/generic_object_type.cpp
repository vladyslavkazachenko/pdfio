#include "generic_object_type.h"

using namespace pdfio::pdf1_0;
/*! \brief Returns type id of Name.*/
template <> int GenericObject::TypeId<Name>()
{
	return static_cast<int>(GenericObjectType::kName);
}
/*! \brief Returns type id of Integer.*/
template <> int GenericObject::TypeId<Integer>()
{
	return static_cast<int>(GenericObjectType::kInteger);
}
/*! \brief Returns type id of IndirectReference.*/
template <> int GenericObject::TypeId<IndirectReference>()
{
	return static_cast<int>(GenericObjectType::kIndirectReference);
}
/*! \brief Returns type id of Dictionary.*/
template <> int GenericObject::TypeId<Dictionary>()
{
	return static_cast<int>(GenericObjectType::kDictionary);
}
/*! \brief Returns type id of IndirectObject.*/
template <> int GenericObject::TypeId<IndirectObject>()
{
	return static_cast<int>(GenericObjectType::kIndirectObject);
}