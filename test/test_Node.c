#include "unity.h"
#include "Node.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_function_create_Tree()
{
	Tree *tree;
  
  tree=initiallizeTree();
  tree=createTree(tree);
  
  //at node 60
  TEST_ASSERT_EQUAL(60,tree->head->data);
  TEST_ASSERT_EQUAL(30,tree->head->left->data);
  TEST_ASSERT_EQUAL(110,tree->head->right->data);
  
  //at node 30
  TEST_ASSERT_EQUAL(20,tree->head->left->left->data);
  TEST_ASSERT_NULL(tree->head->left->right);
  
  //at node 20
  TEST_ASSERT_NULL(tree->head->left->left->left);
  TEST_ASSERT_NULL(tree->head->left->left->right);
  
  //at node 110
  TEST_ASSERT_EQUAL(80,tree->head->right->left->data);
  TEST_ASSERT_EQUAL(150,tree->head->right->right->data);
    
  //at node 80
  TEST_ASSERT_EQUAL(70,tree->head->right->left->left->data);
  TEST_ASSERT_EQUAL(90,tree->head->right->left->right->data);
      
  //at node 90
  TEST_ASSERT_NULL(tree->head->right->left->right->left);
  TEST_ASSERT_EQUAL(100,tree->head->right->left->right->right->data);
  
  //at node 70
  TEST_ASSERT_NULL(tree->head->right->left->left->left);
  TEST_ASSERT_NULL(tree->head->right->left->left->right);
  
  //at node 150
  TEST_ASSERT_EQUAL(130,tree->head->right->right->left->data);
  TEST_ASSERT_NULL(tree->head->right->right->left->right);
  
  //at node 1300
  TEST_ASSERT_NULL(tree->head->right->right->left->left);
  TEST_ASSERT_NULL(tree->head->right->right->left->right);
}


