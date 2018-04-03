#include <sstream>

#include "pdfio/pdf1_0/document_page_tree_root_node.h"
#include "pdfio/pdf1_0/istream/read_indirect_object.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DocumentPageTreeRootNodeTestSuite, emptyStream)
{
	pdf1_0::IndirectObject root{pdf1_0::DocumentPageTreeRootNode()};
	std::istringstream istream;
	EXPECT_FALSE(istream >> root);
}

TEST(DocumentPageTreeRootNodeTestSuite, ok)
{
	pdf1_0::IndirectObject root{pdf1_0::DocumentPageTreeRootNode()};
	std::istringstream istream(
"2 0 obj\r\
<<\r\
/Type /Pages\r\
/Kids [ 4 0 R 10 0 R 24 0 R ]\r\
/Count 3\r\
>>\r\
endobj");
	EXPECT_TRUE(istream >> root);
	EXPECT_TRUE(root.objectNumber() == 2);
	EXPECT_TRUE(root.generationNumber() == 0);
	EXPECT_EQ(3, root.get<pdf1_0::DocumentPageTreeRootNode>().kids().size());
	EXPECT_TRUE(root.get<pdf1_0::DocumentPageTreeRootNode>().kids()[0].objectNumber() == 4);
	EXPECT_TRUE(root.get<pdf1_0::DocumentPageTreeRootNode>().kids()[0].generationNumber() == 0);
	EXPECT_TRUE(root.get<pdf1_0::DocumentPageTreeRootNode>().kids()[1].objectNumber() == 10);
	EXPECT_TRUE(root.get<pdf1_0::DocumentPageTreeRootNode>().kids()[1].generationNumber() == 0);
	EXPECT_TRUE(root.get<pdf1_0::DocumentPageTreeRootNode>().kids()[2].objectNumber() == 24);
	EXPECT_TRUE(root.get<pdf1_0::DocumentPageTreeRootNode>().kids()[2].generationNumber() == 0);
	EXPECT_TRUE(root.get<pdf1_0::DocumentPageTreeRootNode>().count() == 3);
}

TEST(DocumentPageTreeRootNodeTestSuite, noType)
{
	pdf1_0::IndirectObject root{pdf1_0::DocumentPageTreeRootNode()};
	std::istringstream istream(
"2 0 obj\r\
<<\r\
/Kids [ 4 0 R 10 0 R 24 0 R ]\r\
/Count 3\r\
>>\r\
endobj");
	EXPECT_FALSE(istream >> root);
}

TEST(DocumentPageTreeRootNodeTestSuite, wrongType)
{	
	pdf1_0::IndirectObject root{pdf1_0::DocumentPageTreeRootNode()};
	std::istringstream istream(
"2 0 obj\r\
<<\r\
/Type /whatever\r\
/Kids [ 4 0 R 10 0 R 24 0 R ]\r\
/Count 3\r\
>>\r\
endobj");
	EXPECT_FALSE(istream >> root);
}

TEST(DocumentPageTreeRootNodeTestSuite, noKids)
{
	pdf1_0::IndirectObject root{pdf1_0::DocumentPageTreeRootNode()};
	std::istringstream istream(
"2 0 obj\r\
<<\r\
/Type /Pages\r\
/Count 3\r\
>>\r\
endobj");
	EXPECT_FALSE(istream >> root);
}

TEST(DocumentPageTreeRootNodeTestSuite, noCount)
{
	pdf1_0::IndirectObject root{pdf1_0::DocumentPageTreeRootNode()};
	std::istringstream istream(
"2 0 obj\r\
<<\r\
/Type /Pages\r\
/Kids [ 4 0 R 10 0 R 24 0 R ]\r\
>>\r\
endobj");
	EXPECT_FALSE(istream >> root);
}