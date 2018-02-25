#include "pdfio/pdf1_0/document_page_tree_root_node.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DocumentPageTreeRootNodeTestSuite, defaultCtor)
{
	pdf1_0::DocumentPageTreeRootNode root;
	EXPECT_TRUE(root.kids().empty());
	EXPECT_TRUE(root.count() == 0ll);
}

TEST(DocumentPageTreeRootNodeTestSuite, assignment)
{
	pdf1_0::DocumentPageTreeRootNode root;
	root.kids().resize(1);
	root.kids()[0].objectNumber() = 123ll;
	root.kids()[0].generationNumber() = 1ll;
	root.count() = 5ll;
	EXPECT_FALSE(root.kids().empty());
	EXPECT_TRUE(root.kids()[0].objectNumber() == 123ll);
	EXPECT_TRUE(root.kids()[0].generationNumber() == 1ll);
	EXPECT_TRUE(root.count() == 5ll);
}