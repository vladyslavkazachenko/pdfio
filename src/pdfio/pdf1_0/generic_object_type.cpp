#include "generic_object_type.h"

using namespace pdfio::pdf1_0;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <> int GenericObject::TypeId<Name>()
{
	return static_cast<int>(GenericObjectType::kName);
}

template <> int GenericObject::TypeId<Integer>()
{
	return static_cast<int>(GenericObjectType::kInteger);
}

template <> int GenericObject::TypeId<IndirectReference>()
{
	return static_cast<int>(GenericObjectType::kIndirectReference);
}

template <> int GenericObject::TypeId<Dictionary>()
{
	return static_cast<int>(GenericObjectType::kDictionary);
}

template <> int GenericObject::TypeId<IndirectObject>()
{
	return static_cast<int>(GenericObjectType::kIndirectObject);
}

template <> int GenericObject::TypeId<Array<IndirectReference>>()
{
	return static_cast<int>(GenericObjectType::kArrayIndirectReference);
}

#endif //DOXYGEN_SHOULD_SKIP_THIS