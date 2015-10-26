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
	Node *head;

  head=createTree();
  
  //at node 60
  TEST_ASSERT_EQUAL(60,head->data);
  TEST_ASSERT_EQUAL(30,head->left->data);
  TEST_ASSERT_EQUAL(110,head->right->data);
  
  //at node 30
  TEST_ASSERT_EQUAL(20,head->left->left->data);
  TEST_ASSERT_NULL(head->left->right);
  
  //at node 20
  TEST_ASSERT_NULL(head->left->left->left);
  TEST_ASSERT_NULL(head->left->left->right);
  
  //at node 110
  TEST_ASSERT_EQUAL(80,head->right->left->data);
  TEST_ASSERT_EQUAL(150,head->right->right->data);
    
  //at node 80
  TEST_ASSERT_EQUAL(70,head->right->left->left->data);
  TEST_ASSERT_EQUAL(90,head->right->left->right->data);
      
  //at node 90
  TEST_ASSERT_NULL(head->right->left->right->left);
  TEST_ASSERT_EQUAL(100,head->right->left->right->right->data);
  
  //at node 70
  TEST_ASSERT_NULL(head->right->left->left->left);
  TEST_ASSERT_NULL(head->right->left->left->right);
  
  //at node 150
  TEST_ASSERT_EQUAL(130,head->right->right->left->data);
  TEST_ASSERT_NULL(head->right->right->left->right);
  
  //at node 1300
  TEST_ASSERT_NULL(head->right->right->left->left);
  TEST_ASSERT_NULL(head->right->right->left->right);
}


