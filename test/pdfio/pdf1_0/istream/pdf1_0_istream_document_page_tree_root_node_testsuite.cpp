#include <sstream>

#include "pdfio/pdf1_0/istream/read_document_page_tree_root_node.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DocumentPageTreeRootNodeTestSuite, emptyStream)
{
	pdf1_0::DocumentPageTreeRootNode root;
	std::istringstream istream;
	EXPECT_FALSE(istream >> root);
}

TEST(DocumentPageTreeRootNodeTestSuite, ok)
{
	pdf1_0::DocumentPageTreeRootNode root;
	std::istringstream istream(
"2 0 obj\r\
<<\r\
/Type /Pages\r\
/Kids [ 4 0 R 10 0 R 24 0 R ]\r\
/Count 3\r\
>>\r\
endobj");
	EXPECT_TRUE(istream >> root);
	EXPECT_TRUE(root.objectNumber() == 2ll);
	EXPECT_TRUE(root.generationNumber() == 0ll);
	EXPECT_EQ(3, root.kids().size());
	EXPECT_TRUE(root.kids()[0].objectNumber() == 4ll);
	EXPECT_TRUE(root.kids()[0].generationNumber() == 0ll);
	EXPECT_TRUE(root.kids()[1].objectNumber() == 10ll);
	EXPECT_TRUE(root.kids()[1].generationNumber() == 0ll);
	EXPECT_TRUE(root.kids()[2].objectNumber() == 24ll);
	EXPECT_TRUE(root.kids()[2].generationNumber() == 0ll);
	EXPECT_TRUE(root.count() == 3ll);
}

TEST(DocumentPageTreeRootNodeTestSuite, noType)
{
	pdf1_0::DocumentPageTreeRootNode root;
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
	pdf1_0::DocumentPageTreeRootNode root;
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
	pdf1_0::DocumentPageTreeRootNode root;
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
	pdf1_0::DocumentPageTreeRootNode root;
	std::istringstream istream(
"2 0 obj\r\
<<\r\
/Type /Pages\r\
/Kids [ 4 0 R 10 0 R 24 0 R ]\r\
>>\r\
endobj");
	EXPECT_FALSE(istream >> root);
}