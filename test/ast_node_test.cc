#include <gtest/gtest.h>
#include "ast_node.h"

namespace {
	class ASTNodeTest : public ::testing::Test {};

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
		EXPECT_EQ(cd, fd->FindEnclosingNode(ASTNode::ClassDefinition));
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
		EXPECT_EQ(NULL, fd->FindEnclosingNode(ASTNode::Conditional));
	}

}
