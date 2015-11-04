#include "unity.h"
#include "Avl.h"
#include "Node.h"
#include "ErrorObject.h"
#include "CException.h"
#include <stdlib.h>

Node  *node10, *node20, *node30, *node40, *node50, *node60, *node70, *node80, *node90;
Node  *node100, *node110, *node120, *node130, *node140, *node150, *node160, *node170;
Node  *node180, *node190;

Node *resetNode(int value){
  Node *node=malloc(sizeof(Node));

  node->data = value;
  node->balanceFactor = 0;
  node->left = NULL;
  node->right = NULL;
}

void setUp(void){
  node10=resetNode(10);
  node20=resetNode(20);
  node30=resetNode(30);
  node40=resetNode(40);
  node50=resetNode(50);
  node60=resetNode(60);
  node70=resetNode(70);
  node80=resetNode(80);
  node90=resetNode(90);
  node100=resetNode(100);
  node110=resetNode(110);
  node120=resetNode(120);
  node130=resetNode(130);
  node140=resetNode(140);
}

void tearDown()
{
}

void test_throw_err_if_existance_of_two_same_data_in_avl_tree()
{
  int balanceFactor;
  ErrorObject *err;

  Node *head;

  head=node20;

  Try{
    balanceFactor=avlAdd(&head,node20);
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("The node added has already in the avl tree",err->errorMsg);
    free(err);
  }

}

/**
 *          20               20
 *                  =>         \
 *                              40
 */
void test_function_avlAdd_given_new_Node_add_into_tree_at_right_node_should_return_1_if_left_node_is_NULL()
{
  int balanceFactor;

  Node *head;

  head=node20;

  balanceFactor=avlAdd(&head,node40);

  TEST_ASSERT_EQUAL(1,head->balanceFactor);
  TEST_ASSERT_EQUAL_PTR(node40,head->right);
}

/**
 *          20               20
 *                  =>      /
 *                        10
 */
void test_function_avlAdd_given_new_Node_add_into_tree_at_left_node_should_return_minus_1_if_right_node_is_NULL()
{
  int balanceFactor;

  Node *head;

  head=node20;

  balanceFactor=avlAdd(&head,node10);

  TEST_ASSERT_EQUAL(-1,head->balanceFactor);
  TEST_ASSERT_EQUAL_PTR(node10,head->left);
}

/**
 *          20                20
 *         /         =>      /  \
 *       10                10    40
 */
void test_function_avlAdd_given_new_Node_add_into_tree_at_right_node_should_return_0_if_left_node_is_not_NULL()
{
  int balanceFactor;

  Node *head;

  head=node20;

  balanceFactor=avlAdd(&head,node10);
  balanceFactor=avlAdd(&head,node40);

  TEST_ASSERT_EQUAL(0,head->balanceFactor);
  TEST_ASSERT_EQUAL_PTR(node40,head->right);
  TEST_ASSERT_EQUAL_PTR(node10,head->left);
}

/**
 *          20                20
 *            \      =>      /  \
 *             30          10    30
 */
void test_function_avlAdd_given_new_Node_add_into_tree_at_left_node_should_return_0_if_right_node_is_not_NULL()
{
  int balanceFactor;

  Node *head;

  head=node20;

  balanceFactor=avlAdd(&head,node30);
  balanceFactor=avlAdd(&head,node10);

  TEST_ASSERT_EQUAL(0,head->balanceFactor);
  TEST_ASSERT_EQUAL_PTR(node10,head->left);
}

/**
 *          20               20
 *         /  \     =>      /  \
 *       10    30         10    30
 *                                \
 *                                 40
 */
void test_function_avlAdd_given_new_Node_should_add_into_tree4()
{
  int balanceFactor;

  Node *head;

  head=node20;
  balanceFactor=avlAdd(&head,node10);
  balanceFactor=avlAdd(&head,node30);
  balanceFactor=avlAdd(&head,node40);

  TEST_ASSERT_EQUAL(1,head->balanceFactor);
  TEST_ASSERT_EQUAL(1,head->right->balanceFactor);
  TEST_ASSERT_EQUAL(0,head->left->balanceFactor);
  TEST_ASSERT_EQUAL(0,head->right->right->balanceFactor);
}

/**
 *           60
 *             \
 *              90
 *                \
 *                100
 *
 */
void test_add_node_into_Avltree_if_balance_factor_is_2_should_rotate_tree()
{
  int balanceFactor;

  Node *head;

  head=node60;
  balanceFactor=avlAdd(&head,node90);
  balanceFactor=avlAdd(&head,node100);

  TEST_ASSERT_NULL(head->left);
  TEST_ASSERT_EQUAL_PTR(node90,head->right);
  TEST_ASSERT_EQUAL_PTR(node100,head->right->right);
  TEST_ASSERT_EQUAL(2,head->balanceFactor);
  TEST_ASSERT_EQUAL(1,head->right->balanceFactor);
  TEST_ASSERT_EQUAL(0,head->right->right->balanceFactor);

}

/**
 *          60
 *            \
 *             90
 *            /
 *           80
 *
 */
void test_add_node_into_Avltree_if_balance_factor_is_2_should_rotate_tree1()
{
  int balanceFactor;

  Node *head;

  head=node60;
  balanceFactor=avlAdd(&head,node90);
  balanceFactor=avlAdd(&head,node80);

  TEST_ASSERT_NULL(head->left);
  TEST_ASSERT_EQUAL_PTR(node90,head->right);
  TEST_ASSERT_EQUAL_PTR(node80,head->right->left);
  TEST_ASSERT_NULL(head->right->right);
  TEST_ASSERT_EQUAL(2,head->balanceFactor);
  TEST_ASSERT_EQUAL(-1,head->right->balanceFactor);
}


/**
 *          60
 *         /
 *       40
 *        \
 *         50
 *
 */
void test_add_node_into_Avltree_if_balance_factor_is_2_should_rotate_tree2()
{
  int balanceFactor;

  Node *head;

  head=node60;
  balanceFactor=avlAdd(&head,node40);
  balanceFactor=avlAdd(&head,node50);

  TEST_ASSERT_NULL(head->right);
  TEST_ASSERT_EQUAL_PTR(node40,head->left);
  TEST_ASSERT_EQUAL_PTR(node50,head->left->right);
  TEST_ASSERT_NULL(head->left->left);
  TEST_ASSERT_EQUAL(-2,head->balanceFactor);
  TEST_ASSERT_EQUAL(1,head->left->balanceFactor);
}

/**
 *                  60
 *                 /  \
 *               30    80
 *              /  \     \
 *            20   40     90
 *                   \
 *                    50
 */
void test_add_node_into_Avltree_if_balance_factor_is_2_should_rotate_tree3()
{
  int balanceFactor;

  Node *head;

  head=node60;
  balanceFactor=avlAdd(&head,node30);
  balanceFactor=avlAdd(&head,node80);
  balanceFactor=avlAdd(&head,node20);
  balanceFactor=avlAdd(&head,node40);
  balanceFactor=avlAdd(&head,node90);
  balanceFactor=avlAdd(&head,node50);
  // balanceFactor=avlAdd(&head,node100);

  TEST_ASSERT_EQUAL(-1,head->balanceFactor);
  // TEST_ASSERT_EQUAL(0,head->left->balanceFactor);
}




