#include <gtest/gtest.h>
#include "ast_node.h"

namespace {
	class ClassDefinitionNodeTest : public ::testing::Test
	{
	};

	TEST_F(ClassDefinitionNodeTest, ShouldReturnCorrectVariableOffsets)
	{
		ClassDefinitionNode *cd = new ClassDefinitionNode("TestClass");

		cd->AddClassVariable("@test1");
		cd->AddClassVariable("@test2");

		EXPECT_EQ(0, cd->ClassVariablePosition("@test1"));
		EXPECT_EQ(1, cd->ClassVariablePosition("@test2"));

		// And when the class var can't be found...
		EXPECT_EQ(-1, cd->ClassVariablePosition("@nonexistent"));

	}
}
