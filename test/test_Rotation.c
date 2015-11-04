#include "unity.h"
#include "Rotation.h"
#include "Node.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void xtest_function_left_Rotation()
{
  Node *head;

  // head=createTree();

  head=leftRotation(head);

  TEST_ASSERT_EQUAL(110,head->data);
  TEST_ASSERT_EQUAL(60,head->left->data);
  TEST_ASSERT_EQUAL(150,head->right->data);

  TEST_ASSERT_EQUAL(30,head->left->left->data);
  TEST_ASSERT_EQUAL(80,head->left->right->data);

  TEST_ASSERT_EQUAL(20,head->left->left->left->data);
  TEST_ASSERT_NULL(head->left->left->right);

  TEST_ASSERT_NULL(head->left->left->left->left);
  TEST_ASSERT_NULL(head->left->left->left->right);

  TEST_ASSERT_EQUAL(70,head->left->right->left->data);
  TEST_ASSERT_EQUAL(90,head->left->right->right->data);

  TEST_ASSERT_NULL(head->left->right->left->left);
  TEST_ASSERT_NULL(head->left->right->left->right);

  TEST_ASSERT_EQUAL(100,head->left->right->right->right->data);
  TEST_ASSERT_NULL(head->left->right->right->left);

  TEST_ASSERT_NULL(head->left->right->right->right->left);
  TEST_ASSERT_NULL(head->left->right->right->right->right);

  TEST_ASSERT_EQUAL(130,head->right->left->data);
  TEST_ASSERT_NULL(head->right->right);

  TEST_ASSERT_NULL(head->right->left->left);
  TEST_ASSERT_NULL(head->right->left->right);

}

void xtest_function_right_left_Rotation()
{
  Node *head;

  // head=createTree(head);

  head=rightLeftRotation(head);

  TEST_ASSERT_EQUAL(80,head->data);
  TEST_ASSERT_EQUAL(60,head->left->data);
  TEST_ASSERT_EQUAL(110,head->right->data);

  TEST_ASSERT_EQUAL(30,head->left->left->data);
  TEST_ASSERT_EQUAL(70,head->left->right->data);

  TEST_ASSERT_EQUAL(20,head->left->left->left->data);
  TEST_ASSERT_NULL(head->left->left->right);

  TEST_ASSERT_EQUAL(90,head->right->left->data);
  TEST_ASSERT_EQUAL(150,head->right->right->data);

  TEST_ASSERT_EQUAL(100,head->right->left->right->data);
  TEST_ASSERT_NULL(head->right->left->left);

  TEST_ASSERT_EQUAL(130,head->right->right->left->data);
  TEST_ASSERT_NULL(head->right->right->right);

}

