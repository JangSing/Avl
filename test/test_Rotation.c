#include "unity.h"
#include "Rotation.h"
#include "Node.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_function_left_Rotation()
{
  Tree *tree;
  
  tree=initiallizeTree();
  tree=createTree(tree);
  
  leftRotation(tree,tree->head);
  
  TEST_ASSERT_EQUAL(110,tree->head->data);
  TEST_ASSERT_EQUAL(60,tree->head->left->data);
  TEST_ASSERT_EQUAL(150,tree->head->right->data);

  TEST_ASSERT_EQUAL(30,tree->head->left->left->data);
  TEST_ASSERT_EQUAL(80,tree->head->left->right->data);

  TEST_ASSERT_EQUAL(20,tree->head->left->left->left->data);
  TEST_ASSERT_NULL(tree->head->left->left->right);
  
  TEST_ASSERT_NULL(tree->head->left->left->left->left);
  TEST_ASSERT_NULL(tree->head->left->left->left->right);
  
  TEST_ASSERT_EQUAL(70,tree->head->left->right->left->data);
  TEST_ASSERT_EQUAL(90,tree->head->left->right->right->data);
  
  TEST_ASSERT_NULL(tree->head->left->right->left->left);
  TEST_ASSERT_NULL(tree->head->left->right->left->right);
  
  TEST_ASSERT_EQUAL(100,tree->head->left->right->right->right->data);
  TEST_ASSERT_NULL(tree->head->left->right->right->left);
  
  TEST_ASSERT_NULL(tree->head->left->right->right->right->left);
  TEST_ASSERT_NULL(tree->head->left->right->right->right->right);
  
  TEST_ASSERT_EQUAL(130,tree->head->right->left->data); 
  TEST_ASSERT_NULL(tree->head->right->right); 
  
  TEST_ASSERT_NULL(tree->head->right->left->left);
  TEST_ASSERT_NULL(tree->head->right->left->right);
  
}

void test_function_right_left_Rotation()
{
  Tree *tree;
  
  tree=initiallizeTree();
  tree=createTree(tree);
  
  rightLeftRotation(tree,tree->head,tree->head->right);
  
  TEST_ASSERT_EQUAL(80,tree->head->data);
  TEST_ASSERT_EQUAL(60,tree->head->left->data);
  TEST_ASSERT_EQUAL(110,tree->head->right->data);

  TEST_ASSERT_EQUAL(30,tree->head->left->left->data);
  TEST_ASSERT_EQUAL(70,tree->head->left->right->data);

  TEST_ASSERT_EQUAL(20,tree->head->left->left->left->data);
  TEST_ASSERT_NULL(tree->head->left->left->right);
  
  // TEST_ASSERT_NULL(tree->head->left->left->left->left);
  // TEST_ASSERT_NULL(tree->head->left->left->left->right);
  
  TEST_ASSERT_EQUAL(90,tree->head->right->left->data);
  TEST_ASSERT_EQUAL(150,tree->head->right->right->data);
  
  TEST_ASSERT_EQUAL(100,tree->head->right->left->right->data);
  TEST_ASSERT_NULL(tree->head->right->left->left);
  
  TEST_ASSERT_EQUAL(130,tree->head->right->right->left->data);
  TEST_ASSERT_NULL(tree->head->right->right->right);
  
}

