#include "pdfio/pdf1_0/type_info.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(TypeInfoTestSuite, Name)
{
	EXPECT_EQ(pdf1_0::TypeId::kName, pdf1_0::TypeInfo<pdf1_0::Name>::Id());
}

TEST(TypeInfoTestSuite, Integer)
{
	EXPECT_EQ(pdf1_0::TypeId::kInteger, pdf1_0::TypeInfo<pdf1_0::Integer>::Id());
}

TEST(TypeInfoTestSuite, IndirectReference)
{
	EXPECT_EQ(pdf1_0::TypeId::kIndirectReference, pdf1_0::TypeInfo<pdf1_0::IndirectReference>::Id());
}