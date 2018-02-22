#pragma once

#include <iostream>

#include "pdfio/pdf1_0/generic_object.h"
#include "pdfio/pdf1_0/generic_object_type.h"
#include "pdfio/pdf1_0/istream/read_name.h"
#include "pdfio/pdf1_0/istream/read_integer.h"
#include "pdfio/pdf1_0/istream/read_indirect_reference.h"

namespace pdf1_0 = pdfio::pdf1_0;
/*! \brief Reads the name from the istream*/
inline std::istream &operator>>(std::istream &istream, pdf1_0::GenericObject &object)
{
	switch(object.typeId_)
	{
	case static_cast<int>(pdf1_0::GenericObjectType::kName):
		istream >> static_cast<pdf1_0::GenericObjectAdaptor<pdf1_0::Name> &>(object).object_;
		break;
	case static_cast<int>(pdf1_0::GenericObjectType::kInteger):
		istream >> static_cast<pdf1_0::GenericObjectAdaptor<pdf1_0::Integer> &>(object).object_;
		break;
	case static_cast<int>(pdf1_0::GenericObjectType::kIndirectReference):
		istream >> static_cast<pdf1_0::GenericObjectAdaptor<pdf1_0::IndirectReference> &>(object).object_;
		break;
	default:
		istream.setstate(std::ios_base::failbit);
	};
	return istream;
}