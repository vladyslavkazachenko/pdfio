#include "pdfio/pdf1_0/document_page_tree_root_node.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DocumentPageTreeRootNodeTestSuite, defaultCtor)
{
	pdf1_0::DocumentPageTreeRootNode root;
	EXPECT_TRUE(root.kids().empty());
	EXPECT_TRUE(root.count() == 0);
}

TEST(DocumentPageTreeRootNodeTestSuite, assignment)
{
	pdf1_0::DocumentPageTreeRootNode root;
	root.kids().resize(1);
	root.kids()[0].objectNumber() = 123;
	root.kids()[0].generationNumber() = 1;
	root.count() = 5;
	EXPECT_FALSE(root.kids().empty());
	EXPECT_TRUE(root.kids()[0].objectNumber() == 123);
	EXPECT_TRUE(root.kids()[0].generationNumber() == 1);
	EXPECT_TRUE(root.count() == 5);
}