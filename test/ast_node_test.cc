#include <gtest/gtest.h>
#include "ast_node.h"

namespace {
	class ASTNodeTest : public ::testing::Test {
	};

	TEST_F(ASTNodeTest, ShouldAppendNodeToNodeWithNoChildren)
	{
		SourceFileNode *sf = new SourceFileNode;
		ClassDefinitionNode *cd = new ClassDefinitionNode("TestClass");

		sf->AppendChild(cd);

		EXPECT_EQ(sf->firstChild, cd);
		EXPECT_EQ(cd->parent, sf);

		EXPECT_EQ(NULL, cd->nextSibling);
		EXPECT_EQ(NULL, cd->prevSibling);
		EXPECT_EQ(NULL, cd->firstChild);
	}

	TEST_F(ASTNodeTest, ShouldAppendNodeToNodeWithChildren)
	{
		SourceFileNode *sf = new SourceFileNode;
		ClassDefinitionNode *cd1 = new ClassDefinitionNode("TestClass1");
		ClassDefinitionNode *cd2 = new ClassDefinitionNode("TestClass2");

		sf->AppendChild(cd1);
		sf->AppendChild(cd2);

		EXPECT_EQ(sf->firstChild, cd1);
		EXPECT_EQ(cd2->parent, sf);

		EXPECT_EQ(NULL, cd1->prevSibling);
		EXPECT_EQ(cd1->nextSibling, cd2);
		EXPECT_EQ(cd2->prevSibling, cd1);
		EXPECT_EQ(NULL, cd2->nextSibling);
	}

	TEST_F(ASTNodeTest, ShouldAppendNullNode)
	{
		SourceFileNode *sf = new SourceFileNode;
		ClassDefinitionNode *cd1 = new ClassDefinitionNode("TestClass1");

		sf->AppendChild(cd1);
		sf->AppendChild(NULL);

		EXPECT_EQ(sf->firstChild, cd1);
		EXPECT_EQ(cd1->parent, sf);

		EXPECT_EQ(NULL, cd1->prevSibling);
		EXPECT_EQ(NULL, cd1->nextSibling);
	}

	TEST_F(ASTNodeTest, ShouldPrependNodeToNodeWithNoChildren)
	{
		SourceFileNode *sf = new SourceFileNode;
		ClassDefinitionNode *cd1 = new ClassDefinitionNode("TestClass1");

		sf->InsertFirstChild(cd1);

		EXPECT_EQ(cd1->parent, sf);
		EXPECT_EQ(sf->firstChild, cd1);

		EXPECT_EQ(NULL, cd1->nextSibling);
		EXPECT_EQ(NULL, cd1->prevSibling);
	}

	TEST_F(ASTNodeTest, ShouldPrependToNodeWithChildren)
	{
		SourceFileNode *sf = new SourceFileNode;
		ClassDefinitionNode *cd1 = new ClassDefinitionNode("TestClass1");
		ClassDefinitionNode *cd2 = new ClassDefinitionNode("TestClass2");

		sf->AppendChild(cd1);
		sf->InsertFirstChild(cd2);

		EXPECT_EQ(sf->firstChild, cd2);
		EXPECT_EQ(cd2->parent, sf);

		EXPECT_EQ(NULL, cd2->prevSibling);
		EXPECT_EQ(cd2->nextSibling, cd1);
		EXPECT_EQ(cd1->prevSibling, cd2);
		EXPECT_EQ(NULL, cd1->nextSibling);
	}

	TEST_F(ASTNodeTest, ShouldHandlePrependingOfNullNode)
	{
		SourceFileNode *sf = new SourceFileNode;
		ClassDefinitionNode *cd1 = new ClassDefinitionNode("TestClass1");

		sf->AppendChild(cd1);
		sf->InsertFirstChild(NULL);

		EXPECT_EQ(sf->firstChild, cd1);
		EXPECT_EQ(cd1->parent, sf);

		EXPECT_EQ(NULL, cd1->prevSibling);
		EXPECT_EQ(NULL, cd1->nextSibling);
	}

	TEST_F(ASTNodeTest, ShouldDetachNodeFromParentWithOnlyChild)
	{
		SourceFileNode *sf = new SourceFileNode;
		ClassDefinitionNode *cd1 = new ClassDefinitionNode("TestClass1");

		sf->AppendChild(cd1);
		sf->DetachChild(cd1);

		EXPECT_EQ(NULL, sf->firstChild);

		EXPECT_EQ(NULL, cd1->parent);
		EXPECT_EQ(NULL, cd1->prevSibling);
		EXPECT_EQ(NULL, cd1->nextSibling);
	}

	TEST_F(ASTNodeTest, ShouldDetachFirstNodeFromParentWithMultipleChildren)
	{
		SourceFileNode *sf = new SourceFileNode;
		ClassDefinitionNode *cd1 = new ClassDefinitionNode("TestClass1");
		ClassDefinitionNode *cd2 = new ClassDefinitionNode("TestClass2");

		sf->AppendChild(cd1);
		sf->AppendChild(cd2);
		sf->DetachChild(cd1);

		EXPECT_EQ(cd2, sf->firstChild);

		EXPECT_EQ(NULL, cd2->prevSibling);
		EXPECT_EQ(NULL, cd2->nextSibling);

		EXPECT_EQ(NULL, cd1->parent);
		EXPECT_EQ(NULL, cd1->prevSibling);
		EXPECT_EQ(NULL, cd1->nextSibling);
	}

	TEST_F(ASTNodeTest, ShouldDetachLastNodeFromParentWithMultipleChildren)
	{
		SourceFileNode *sf = new SourceFileNode;
		ClassDefinitionNode *cd1 = new ClassDefinitionNode("TestClass1");
		ClassDefinitionNode *cd2 = new ClassDefinitionNode("TestClass2");

		sf->AppendChild(cd1);
		sf->AppendChild(cd2);
		sf->DetachChild(cd2);

		EXPECT_EQ(cd1, sf->firstChild);

		EXPECT_EQ(NULL, cd1->prevSibling);
		EXPECT_EQ(NULL, cd1->nextSibling);

		EXPECT_EQ(NULL, cd2->parent);
		EXPECT_EQ(NULL, cd2->prevSibling);
		EXPECT_EQ(NULL, cd2->nextSibling);
	}

	TEST_F(ASTNodeTest, ShouldDetachNullNodeFromParent)
	{
		SourceFileNode *sf = new SourceFileNode;
		ClassDefinitionNode *cd1 = new ClassDefinitionNode("TestClass1");

		sf->AppendChild(cd1);
		sf->DetachChild(NULL);

		EXPECT_EQ(cd1, sf->firstChild);

		EXPECT_EQ(sf, cd1->parent);
		EXPECT_EQ(NULL, cd1->prevSibling);
		EXPECT_EQ(NULL, cd1->nextSibling);
	}

	TEST_F(ASTNodeTest, ShouldNotDetachNodeFromNonParentNode)
	{
		ClassDefinitionNode *cd1 = new ClassDefinitionNode("TestClass1");
		ClassDefinitionNode *cd2 = new ClassDefinitionNode("TestClass2");
		MethodAssignmentNode *ma = new MethodAssignmentNode("method");

		cd1->AppendChild(ma);
		cd2->DetachChild(ma);

		EXPECT_EQ(cd1, ma->parent);
		EXPECT_EQ(ma, cd1->firstChild);

		EXPECT_EQ(NULL, cd2->firstChild);
	}

	TEST_F(ASTNodeTest, ShouldFindEnclosingNode)
	{
		SourceFileNode *sf = new SourceFileNode;
		ClassDefinitionNode *cd = new ClassDefinitionNode("TestClass");
		sf->AppendChild(cd);

		ConstantAssignmentNode *ia = new ConstantAssignmentNode("function");
		cd->AppendChild(ia);

		FunctionDefNode *fd = new FunctionDefNode();
		ia->AppendChild(fd);

		// It should find the enclosing node if it exists;
		EXPECT_EQ(cd, fd->FindEnclosingNode(typeid(ClassDefinitionNode).name()));
	}

	TEST_F(ASTNodeTest, ShouldNotFindNonExistingEnclosingNode)
	{
		SourceFileNode *sf = new SourceFileNode;
		ClassDefinitionNode *cd = new ClassDefinitionNode("TestClass");
		sf->AppendChild(cd);

		ConstantAssignmentNode *ia = new ConstantAssignmentNode("function");
		cd->AppendChild(ia);

		FunctionDefNode *fd = new FunctionDefNode();
		ia->AppendChild(fd);

		// It should return NULL if it doesn't
		EXPECT_EQ(NULL, fd->FindEnclosingNode(typeid(ConditionalNode).name()));
	}

}
