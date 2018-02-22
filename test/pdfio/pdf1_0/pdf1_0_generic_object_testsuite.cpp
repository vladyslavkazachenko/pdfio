#include "pdfio/pdf1_0/generic_object.h"
#include "pdfio/pdf1_0/generic_object_type.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(GenericObjectTestSuite, Name)
{
	EXPECT_EQ(static_cast<int>(pdf1_0::GenericObjectType::kName), 
		pdf1_0::GenericObjectAdaptor<pdf1_0::Name>(pdf1_0::Name()).typeId_);
}

TEST(GenericObjectTestSuite, Integer)
{
	EXPECT_EQ(static_cast<int>(pdf1_0::GenericObjectType::kInteger), 
		pdf1_0::GenericObjectAdaptor<pdf1_0::Integer>(pdf1_0::Integer()).typeId_);
}

TEST(GenericObjectTestSuite, IndirectReference)
{
	EXPECT_EQ(static_cast<int>(pdf1_0::GenericObjectType::kIndirectReference), 
		pdf1_0::GenericObjectAdaptor<pdf1_0::IndirectReference>(pdf1_0::IndirectReference()).typeId_);
}