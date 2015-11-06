#include "unity.h"
#include "Avl.h"
#include "Node.h"
#include "Rotation.h"
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
  ErrorObject *err;

  Node *head;

  head=node20;

  Try{
    avlAdd(&head,node20);
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
void test_function_avlAdd_given_only_one_node_added_at_right_Balance_Factor_should_plus_1()
{
  Node *head;

  head=node20;

  avlAdd(&head,node40);

  TEST_ASSERT_EQUAL_PTR(node20,head);
  TEST_ASSERT_EQUAL_PTR(node40,head->right);
  TEST_ASSERT_EQUAL(1,head->balanceFactor);
}

/**
 *          20               20
 *                  =>      /
 *                        10
 */
void test_function_avlAdd_given_only_one_node_added_at_left_Balance_Factor_should_minus_1()
{
  Node *head;

  head=node20;

  avlAdd(&head,node10);

  TEST_ASSERT_EQUAL_PTR(node20,head);
  TEST_ASSERT_EQUAL_PTR(node10,head->left);
  TEST_ASSERT_EQUAL(-1,head->balanceFactor);
}

/**
 *          20                20
 *         /         =>      /  \
 *       10                10    40
 */
void test_function_avlAdd_given_Node_add_into_tree_at_right_if_left_node_not_NULL_will_change_Balance_Factor()
{
  Node *head;

  head=node20;

  avlAdd(&head,node10);
  avlAdd(&head,node40);

  TEST_ASSERT_EQUAL_PTR(node20,head);
  TEST_ASSERT_EQUAL_PTR(node40,head->right);
  TEST_ASSERT_EQUAL_PTR(node10,head->left);
  TEST_ASSERT_EQUAL(0,head->balanceFactor);
}

/**
 *          20                20
 *            \      =>      /  \
 *             30          10    30
 */
void test_function_avlAdd_given_Node_add_into_tree_at_left_if_right_node_not_NULL_will_change_Balance_Factor()
{
  Node *head;

  head=node20;

  avlAdd(&head,node30);
  avlAdd(&head,node10);

  TEST_ASSERT_EQUAL_PTR(node20,head);
  TEST_ASSERT_EQUAL_PTR(node10,head->left);
  TEST_ASSERT_EQUAL_PTR(node30,head->right);
  TEST_ASSERT_EQUAL(0,head->balanceFactor);

  free(head);
}

/**
 *                   60
 *                 /   \
 *               30     80
 *              /  \    / \
 *            20   40  70  90
 *                          \
 *                           100
 */
void test_function_avlAdd_for_more_data_will_modify_Balance_Factor_correctly()
{
  Node *head;

  head=node60;
  avlAdd(&head,node30);
  avlAdd(&head,node80);
  avlAdd(&head,node20);
  avlAdd(&head,node40);
  avlAdd(&head,node70);
  avlAdd(&head,node90);
  avlAdd(&head,node100);


  TEST_ASSERT_EQUAL_PTR(node60,head);
  TEST_ASSERT_EQUAL_PTR(node30,head->left);
  TEST_ASSERT_EQUAL_PTR(node20,head->left->left);
  TEST_ASSERT_EQUAL_PTR(node40,head->left->right);

  TEST_ASSERT_EQUAL_PTR(node80,head->right);
  TEST_ASSERT_EQUAL_PTR(node70,head->right->left);
  TEST_ASSERT_EQUAL_PTR(node90,head->right->right);
  TEST_ASSERT_EQUAL_PTR(node100,head->right->right->right);

  TEST_ASSERT_EQUAL(1,head->balanceFactor);
}

/**
 *           60                      90
 *             \                    /  \
 *              90      =>        60    100
 *                \
 *                100
 *
 */
void test_condition_Balance_factor_2_0_1()
{
  Node *head;

  head=node60;
  avlAdd(&head,node90);
  avlAdd(&head,node100);

  TEST_ASSERT_EQUAL_PTR(node90,head);
  TEST_ASSERT_EQUAL_PTR(node60,head->left);
  TEST_ASSERT_EQUAL_PTR(node100,head->right);
  TEST_ASSERT_EQUAL(0,head->balanceFactor);
  TEST_ASSERT_EQUAL(0,head->right->balanceFactor);
  TEST_ASSERT_EQUAL(0,head->left->balanceFactor);
}

/**
 *           60                  50
 *          /                   /  \
 *        50         =>       40    60
 *       /
 *     40
 *
 */
void test_condition_Balance_factor_minus_2_0_minus_1()
{
  Node *head;

  head=node60;
  avlAdd(&head,node50);
  avlAdd(&head,node40);

  TEST_ASSERT_EQUAL_PTR(node50,head);
  TEST_ASSERT_EQUAL_PTR(node40,head->left);
  TEST_ASSERT_EQUAL_PTR(node60,head->right);
  TEST_ASSERT_EQUAL(0,head->balanceFactor);
  TEST_ASSERT_EQUAL(0,head->right->balanceFactor);
  TEST_ASSERT_EQUAL(0,head->left->balanceFactor);
}

/**
 *               30                                   90
 *             /    \                               /    \
 *           20      90                           30      110
 *         /        /   \                        / \     /  \
 *       10      70     110        =>          20  70  100  120
 *                \     / \                   /     \         \
 *                80  100 120               10      80        130
 *                          \
 *                          130
 */
void test_condition_Balance_factor_2_1_1()
{
  Node *head;

  head=node30;
  avlAdd(&head,node20);
  avlAdd(&head,node90);
  avlAdd(&head,node10);
  avlAdd(&head,node70);
  avlAdd(&head,node110);
  avlAdd(&head,node80);
  avlAdd(&head,node100);
  avlAdd(&head,node120);
  avlAdd(&head,node130);

  TEST_ASSERT_EQUAL_PTR(node90,head);
  TEST_ASSERT_EQUAL_PTR(node30,head->left);

  TEST_ASSERT_EQUAL_PTR(node20,head->left->left);
  TEST_ASSERT_EQUAL_PTR(node70,head->left->right);

  TEST_ASSERT_EQUAL_PTR(node10,head->left->left->left);
  TEST_ASSERT_EQUAL_PTR(node80,head->left->right->right);

  TEST_ASSERT_EQUAL_PTR(node110,head->right);

  TEST_ASSERT_EQUAL_PTR(node100,head->right->left);
  TEST_ASSERT_EQUAL_PTR(node120,head->right->right);

  TEST_ASSERT_EQUAL_PTR(node130,head->right->right->right);

  TEST_ASSERT_EQUAL(0,head->balanceFactor);
}

/**
 *               30                                   90
 *             /    \                               /    \
 *           20      90                           30      110
 *         /        /  \                         / \     /  \
 *       10       70    110        =>           20  70  100  120
 *               /      / \                    /    /         \
 *             60     100 120                10   60          130
 *                          \
 *                          130
 */
void test_condition_Balance_factor_2_minus_1_1()
{
  Node *head;

  head=node30;
  avlAdd(&head,node20);
  avlAdd(&head,node90);
  avlAdd(&head,node10);
  avlAdd(&head,node70);
  avlAdd(&head,node110);
  avlAdd(&head,node60);
  avlAdd(&head,node100);
  avlAdd(&head,node120);
  avlAdd(&head,node130);

  TEST_ASSERT_EQUAL_PTR(node90,head);
  TEST_ASSERT_EQUAL_PTR(node30,head->left);

  TEST_ASSERT_EQUAL_PTR(node20,head->left->left);
  TEST_ASSERT_EQUAL_PTR(node70,head->left->right);

  TEST_ASSERT_EQUAL_PTR(node10,head->left->left->left);
  TEST_ASSERT_EQUAL_PTR(node60,head->left->right->left);

  TEST_ASSERT_EQUAL_PTR(node110,head->right);

  TEST_ASSERT_EQUAL_PTR(node100,head->right->left);
  TEST_ASSERT_EQUAL_PTR(node120,head->right->right);

  TEST_ASSERT_EQUAL_PTR(node130,head->right->right->right);

  TEST_ASSERT_EQUAL(0,head->balanceFactor);
}

/**
 *               30                                   60
 *             /    \                               /    \
 *           20      90                           30      90
 *         /        /   \                        / \     /  \
 *       10       60     140        =>         20  50   80  140
 *               / \    /                     /    /        /
 *             50  80 120                   10    40      120
 *            /
 *           40
 */
void test_double_rotation_Balance_Factor_2_minus_1_minus_1()
{
  Node *head;

  head=node30;
  avlAdd(&head,node20);
  avlAdd(&head,node90);
  avlAdd(&head,node10);
  avlAdd(&head,node60);
  avlAdd(&head,node140);
  avlAdd(&head,node120);
  avlAdd(&head,node50);
  avlAdd(&head,node80);
  avlAdd(&head,node40);

  TEST_ASSERT_EQUAL_PTR(node60,head);

  //for left side of the tree
  TEST_ASSERT_EQUAL_PTR(node30,head->left);
  TEST_ASSERT_EQUAL_PTR(node50,head->left->right);
  TEST_ASSERT_EQUAL_PTR(node40,head->left->right->left);
  TEST_ASSERT_EQUAL_PTR(node20,head->left->left);
  TEST_ASSERT_EQUAL_PTR(node10,head->left->left->left);

  //for right side of the tree
  TEST_ASSERT_EQUAL_PTR(node90,head->right);
  TEST_ASSERT_EQUAL_PTR(node80,head->right->left);
  TEST_ASSERT_EQUAL_PTR(node140,head->right->right);
  TEST_ASSERT_EQUAL_PTR(node120,head->right->right->left);

  TEST_ASSERT_EQUAL(0,head->balanceFactor);
  TEST_ASSERT_EQUAL(1,head->right->balanceFactor);
  TEST_ASSERT_EQUAL(0,head->left->balanceFactor);
}

/**
 *          60                    80
 *            \                  /  \
 *             90     =>       60    90
 *            /
 *           80
 *
 */
void test_double_rotation_Balance_Factor_2_0_minus_1()
{
  Node *head;

  head=node60;
  avlAdd(&head,node90);
  avlAdd(&head,node80);

  TEST_ASSERT_EQUAL_PTR(node80,head);
  TEST_ASSERT_EQUAL_PTR(node90,head->right);
  TEST_ASSERT_EQUAL_PTR(node60,head->left);
  TEST_ASSERT_EQUAL(0,head->balanceFactor);
  TEST_ASSERT_EQUAL(0,head->right->balanceFactor);
  TEST_ASSERT_EQUAL(0,head->left->balanceFactor);
}

/**
 *          60               50
 *         /                /  \
 *       40        =>     40    60
 *        \
 *         50
 *
 */
void test_double_rotation_Balance_Factor_minus_2_0_1()
{
  Node *head;

  head=node60;
  avlAdd(&head,node40);
  avlAdd(&head,node50);

  TEST_ASSERT_EQUAL_PTR(node50,head);
  TEST_ASSERT_EQUAL_PTR(node40,head->left);
  TEST_ASSERT_EQUAL_PTR(node60,head->right);
  TEST_ASSERT_EQUAL(0,head->balanceFactor);
  TEST_ASSERT_EQUAL(0,head->right->balanceFactor);
  TEST_ASSERT_EQUAL(0,head->left->balanceFactor);

}

/**
 *          30                      60
 *         /  \                    /  \
 *       20    90      =>        30    90
 *            / \               /     /  \
 *          60  100           20     80  100
 *           \
 *            80
 */
void test_double_rotation_Balance_Factor_minus_2_1_minus_1()
{
  Node *head;

  head=node30;
  avlAdd(&head,node20);
  avlAdd(&head,node90);
  avlAdd(&head,node60);
  avlAdd(&head,node100);
  avlAdd(&head,node80);

  TEST_ASSERT_EQUAL_PTR(node60,head);
  TEST_ASSERT_EQUAL_PTR(node30,head->left);
  TEST_ASSERT_EQUAL_PTR(node20,head->left->left);

  TEST_ASSERT_EQUAL_PTR(node90,head->right);
  TEST_ASSERT_EQUAL_PTR(node80,head->right->left);
  TEST_ASSERT_EQUAL_PTR(node100,head->right->right);
  TEST_ASSERT_EQUAL(0,head->balanceFactor);
}


