#include "unity.h"
#include "avlAdd.h"
#include "Node.h"
#include "Rotation.h"
#include "ErrorObject.h"
#include "CException.h"
#include "CustomAssertion.h"
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
  node150=resetNode(150);
  node160=resetNode(160);
  node170=resetNode(170);
  node180=resetNode(180);
  node190=resetNode(190);
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

  //test Node ptr
  TEST_ASSERT_ROOT(NULL   ,20   ,node40   ,node20);
  TEST_ASSERT_ROOT(NULL   ,40   ,NULL     ,node40);

  //test balanceFactor
  TEST_ASSERT_BALANCE(1   ,node20);
  TEST_ASSERT_BALANCE(0   ,node40);
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

  //test Node ptr
  TEST_ASSERT_ROOT(node10   ,20   ,NULL   ,node20);
  TEST_ASSERT_ROOT(NULL     ,10   ,NULL   ,node10);

  //test balanceFactor
  TEST_ASSERT_BALANCE(-1    ,node20);
  TEST_ASSERT_BALANCE(0     ,node10);
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

  //test Node ptr
  TEST_ASSERT_ROOT(node10   ,20   ,node40   ,node20);
  TEST_ASSERT_ROOT(NULL     ,10   ,NULL     ,node10);
  TEST_ASSERT_ROOT(NULL     ,40   ,NULL     ,node40);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node20);
  TEST_ASSERT_BALANCE(0   ,node10);
  TEST_ASSERT_BALANCE(0   ,node40);
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

  //test Node ptr
  TEST_ASSERT_ROOT(node10   ,20   ,node30 ,node20);
  TEST_ASSERT_ROOT(NULL     ,10   ,NULL   ,node10);
  TEST_ASSERT_ROOT(NULL     ,30   ,NULL   ,node30);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node20);
  TEST_ASSERT_BALANCE(0   ,node10);
  TEST_ASSERT_BALANCE(0   ,node30);

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


  //test Node ptr
  TEST_ASSERT_ROOT(node30   ,60     ,node80   ,node60);
  TEST_ASSERT_ROOT(node20   ,30     ,node40   ,node30);
  TEST_ASSERT_ROOT(NULL     ,20     ,NULL     ,node20);
  TEST_ASSERT_ROOT(NULL     ,40     ,NULL     ,node40);
  TEST_ASSERT_ROOT(node70   ,80     ,node90   ,node80);
  TEST_ASSERT_ROOT(NULL     ,70     ,NULL     ,node70);
  TEST_ASSERT_ROOT(NULL     ,90     ,node100  ,node90);
  TEST_ASSERT_ROOT(NULL     ,100    ,NULL     ,node100);

  //test balanceFactor
  TEST_ASSERT_BALANCE(1   ,node60);
  TEST_ASSERT_BALANCE(0   ,node30);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(0   ,node20);
  TEST_ASSERT_BALANCE(1   ,node80);
  TEST_ASSERT_BALANCE(0   ,node70);
  TEST_ASSERT_BALANCE(1   ,node90);
  TEST_ASSERT_BALANCE(0   ,node100);
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

  //test Node ptr
  TEST_ASSERT_ROOT(node60   ,90   ,node100    ,node90);
  TEST_ASSERT_ROOT(NULL     ,60   ,NULL       ,node60);
  TEST_ASSERT_ROOT(NULL     ,100  ,NULL       ,node100);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node90);
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(0   ,node100);
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

  //test Node ptr
  TEST_ASSERT_ROOT(node40   ,50   ,node60   ,node50);
  TEST_ASSERT_ROOT(NULL     ,40   ,NULL     ,node40);
  TEST_ASSERT_ROOT(NULL     ,60   ,NULL     ,node60);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0     ,node50);
  TEST_ASSERT_BALANCE(0     ,node40);
  TEST_ASSERT_BALANCE(0     ,node60);
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

  //test Node ptr
  TEST_ASSERT_ROOT(node30   ,90   ,node110  ,node90);
  TEST_ASSERT_ROOT(node20   ,30   ,node70   ,node30);
  TEST_ASSERT_ROOT(node10   ,20   ,NULL     ,node20);
  TEST_ASSERT_ROOT(NULL     ,10   ,NULL     ,node10);
  TEST_ASSERT_ROOT(NULL     ,70   ,node80   ,node70);
  TEST_ASSERT_ROOT(NULL     ,80   ,NULL     ,node80);
  TEST_ASSERT_ROOT(node100  ,110  ,node120  ,node110);
  TEST_ASSERT_ROOT(NULL     ,100  ,NULL     ,node100);
  TEST_ASSERT_ROOT(NULL     ,120  ,node130  ,node120);
  TEST_ASSERT_ROOT(NULL     ,130  ,NULL     ,node130);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node90);
  TEST_ASSERT_BALANCE(0   ,node30);
  TEST_ASSERT_BALANCE(-1  ,node20);
  TEST_ASSERT_BALANCE(0   ,node10);
  TEST_ASSERT_BALANCE(1   ,node70);
  TEST_ASSERT_BALANCE(0   ,node80);
  TEST_ASSERT_BALANCE(1   ,node110);
  TEST_ASSERT_BALANCE(0   ,node100);
  TEST_ASSERT_BALANCE(1   ,node120);
  TEST_ASSERT_BALANCE(0   ,node130);
}

/**
 *                   100                           60
 *                  /   \                         /  \
 *                60    110                     40    100
 *               /  \     \                    / \    / \
 *             40   80     120     =>        30  50  80 110
 *            / \   /                       /       /     \
 *          30  50 70                     20       70     120
 *         /
 *        20
 */
void test_condition_Balance_factor_minus_2_minus_1_minus_1()
{
  Node *head;

  head=node100;
  avlAdd(&head,node110);
  avlAdd(&head,node60);
  avlAdd(&head,node120);
  avlAdd(&head,node80);
  avlAdd(&head,node40);
  avlAdd(&head,node70);
  avlAdd(&head,node50);
  avlAdd(&head,node30);
  avlAdd(&head,node20);

  //test Node ptr
  TEST_ASSERT_ROOT(node40     ,60     ,node100  ,node60);
  TEST_ASSERT_ROOT(node30     ,40     ,node50   ,node40);
  TEST_ASSERT_ROOT(node20     ,30     ,NULL     ,node30);
  TEST_ASSERT_ROOT(NULL       ,20     ,NULL     ,node20);
  TEST_ASSERT_ROOT(NULL       ,50     ,NULL     ,node50);
  TEST_ASSERT_ROOT(node80     ,100    ,node110  ,node100);
  TEST_ASSERT_ROOT(node70     ,80     ,NULL     ,node80);
  TEST_ASSERT_ROOT(NULL       ,70     ,NULL     ,node70);
  TEST_ASSERT_ROOT(NULL       ,110    ,node120  ,node110);
  TEST_ASSERT_ROOT(NULL       ,120    ,NULL     ,node120);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(-1  ,node40);
  TEST_ASSERT_BALANCE(-1  ,node30);
  TEST_ASSERT_BALANCE(0   ,node20);
  TEST_ASSERT_BALANCE(0   ,node50);
  TEST_ASSERT_BALANCE(0   ,node100);
  TEST_ASSERT_BALANCE(-1  ,node80);
  TEST_ASSERT_BALANCE(0   ,node70);
  TEST_ASSERT_BALANCE(1   ,node110);
  TEST_ASSERT_BALANCE(0   ,node120);

}


/**
 *               30                                   90
 *             /    \                               /    \
 *           20      90                           30      110
 *         /        /  \                         / \     /   \
 *       10       70    110        =>           20  70  100  120
 *               /      / \                    /    /          \
 *             60     100 120                10   60           130
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

  //test Node ptr
  TEST_ASSERT_ROOT(node30     ,90   ,node110  ,node90);
  TEST_ASSERT_ROOT(node20     ,30   ,node70   ,node30);
  TEST_ASSERT_ROOT(node10     ,20   ,NULL     ,node20);
  TEST_ASSERT_ROOT(NULL       ,10   ,NULL     ,node10);
  TEST_ASSERT_ROOT(node60     ,70   ,NULL     ,node70);
  TEST_ASSERT_ROOT(NULL       ,60   ,NULL     ,node60);
  TEST_ASSERT_ROOT(node100    ,110  ,node120  ,node110);
  TEST_ASSERT_ROOT(NULL       ,100  ,NULL     ,node100);
  TEST_ASSERT_ROOT(NULL       ,120  ,node130  ,node120);
  TEST_ASSERT_ROOT(NULL       ,130  ,NULL     ,node130);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node90);
  TEST_ASSERT_BALANCE(0   ,node30);
  TEST_ASSERT_BALANCE(-1  ,node20);
  TEST_ASSERT_BALANCE(0   ,node10);
  TEST_ASSERT_BALANCE(-1  ,node70);
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(1   ,node110);
  TEST_ASSERT_BALANCE(0   ,node100);
  TEST_ASSERT_BALANCE(1   ,node120);
  TEST_ASSERT_BALANCE(0   ,node130);
}

/**
 *                  100                                    60
 *                /    \                                 /   \
 *              60     110                             40    100
 *             /  \       \                           / \    /  \
 *           40    80     120      =>               30  50  80  110
 *          /  \    \                              /         \    \
 *         30  50   90                           20          90   120
 *        /
 *       20
 */
void test_condition_Balance_factor_minus_2_1_minus_1()
{
  Node *head;

  head=node100;
  avlAdd(&head,node110);
  avlAdd(&head,node60);
  avlAdd(&head,node120);
  avlAdd(&head,node80);
  avlAdd(&head,node40);
  avlAdd(&head,node90);
  avlAdd(&head,node50);
  avlAdd(&head,node30);
  avlAdd(&head,node20);

  //test Node ptr
  TEST_ASSERT_ROOT(node40   ,60    ,node100  ,node60);
  TEST_ASSERT_ROOT(node30   ,40    ,node50   ,node40);
  TEST_ASSERT_ROOT(node20   ,30    ,NULL     ,node30);
  TEST_ASSERT_ROOT(NULL     ,20    ,NULL     ,node20);
  TEST_ASSERT_ROOT(NULL     ,50    ,NULL     ,node50);
  TEST_ASSERT_ROOT(node80   ,100   ,node110  ,node100);
  TEST_ASSERT_ROOT(NULL     ,80    ,node90   ,node80);
  TEST_ASSERT_ROOT(NULL     ,90    ,NULL     ,node90);
  TEST_ASSERT_ROOT(NULL     ,110   ,node120  ,node110);
  TEST_ASSERT_ROOT(NULL     ,120   ,NULL     ,node120);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(-1  ,node40);
  TEST_ASSERT_BALANCE(-1  ,node30);
  TEST_ASSERT_BALANCE(0   ,node20);
  TEST_ASSERT_BALANCE(0   ,node50);
  TEST_ASSERT_BALANCE(0   ,node100);
  TEST_ASSERT_BALANCE(1   ,node80);
  TEST_ASSERT_BALANCE(0   ,node90);
  TEST_ASSERT_BALANCE(1   ,node110);
  TEST_ASSERT_BALANCE(0   ,node120);
}

/**
 *               30                                   60
 *             /    \                               /    \
 *           20      90                           30      90
 *         /        /   \                        / \     /  \
 *       10       60     140        =>         20  50   80  140
 *               / \     /                     /    /        /
 *             50  80  120                   10    40      120
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

  //test Node ptr
  TEST_ASSERT_ROOT(node30   ,60    ,node90   ,node60);
  TEST_ASSERT_ROOT(node20   ,30    ,node50   ,node30);
  TEST_ASSERT_ROOT(node10   ,20    ,NULL     ,node20);
  TEST_ASSERT_ROOT(NULL     ,10    ,NULL     ,node10);
  TEST_ASSERT_ROOT(node40   ,50    ,NULL     ,node50);
  TEST_ASSERT_ROOT(NULL     ,40    ,NULL     ,node40);
  TEST_ASSERT_ROOT(node80   ,90    ,node140  ,node90);
  TEST_ASSERT_ROOT(NULL     ,80    ,NULL     ,node80);
  TEST_ASSERT_ROOT(node120  ,140   ,NULL     ,node140);
  TEST_ASSERT_ROOT(NULL     ,120   ,NULL     ,node120);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(0   ,node30);
  TEST_ASSERT_BALANCE(-1  ,node20);
  TEST_ASSERT_BALANCE(0   ,node10);
  TEST_ASSERT_BALANCE(-1  ,node50);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(1   ,node90);
  TEST_ASSERT_BALANCE(0   ,node80);
  TEST_ASSERT_BALANCE(-1  ,node140);
  TEST_ASSERT_BALANCE(0   ,node120);
}

/**
 *                100                                 60
 *               /   \                              /   \
 *              40   110                          40    100
 *             /  \     \                        / \    /  \
 *           20   60    120        =>          20  50  70  110
 *            \   / \                           \       \    \
 *            30 50 70                          30      80   120
 *                   \
 *                   80
 */
void test_double_rotation_Balance_Factor_minus_2_1_1()
{
  Node *head;

  head=node100;
  avlAdd(&head,node110);
  avlAdd(&head,node40);
  avlAdd(&head,node120);
  avlAdd(&head,node60);
  avlAdd(&head,node20);
  avlAdd(&head,node70);
  avlAdd(&head,node50);
  avlAdd(&head,node30);
  avlAdd(&head,node80);

  //test Node ptr
  TEST_ASSERT_ROOT(node40   ,60    ,node100  ,node60);
  TEST_ASSERT_ROOT(node20   ,40    ,node50   ,node40);
  TEST_ASSERT_ROOT(NULL     ,20    ,node30   ,node20);
  TEST_ASSERT_ROOT(NULL     ,30    ,NULL     ,node30);
  TEST_ASSERT_ROOT(NULL     ,50    ,NULL     ,node50);
  TEST_ASSERT_ROOT(node70   ,100   ,node110  ,node100);
  TEST_ASSERT_ROOT(NULL     ,70    ,node80   ,node70);
  TEST_ASSERT_ROOT(NULL     ,80    ,NULL     ,node80);
  TEST_ASSERT_ROOT(NULL     ,110   ,node120  ,node110);
  TEST_ASSERT_ROOT(NULL     ,120   ,NULL     ,node120);

  // test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(-1  ,node40);
  TEST_ASSERT_BALANCE(1   ,node20);
  TEST_ASSERT_BALANCE(0   ,node30);
  TEST_ASSERT_BALANCE(0   ,node50);
  TEST_ASSERT_BALANCE(0   ,node100);
  TEST_ASSERT_BALANCE(1   ,node70);
  TEST_ASSERT_BALANCE(0   ,node80);
  TEST_ASSERT_BALANCE(1   ,node110);
  TEST_ASSERT_BALANCE(0   ,node120);

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

  //test Node ptr
  TEST_ASSERT_ROOT(node60   ,80    ,node90  ,node80);
  TEST_ASSERT_ROOT(NULL     ,60    ,NULL    ,node60);
  TEST_ASSERT_ROOT(NULL     ,90    ,NULL    ,node90);

  // test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node80);
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(0   ,node90);
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

  //test Node ptr
  TEST_ASSERT_ROOT(node40   ,50    ,node60  ,node50);
  TEST_ASSERT_ROOT(NULL     ,40    ,NULL    ,node40);
  TEST_ASSERT_ROOT(NULL     ,60    ,NULL    ,node60);

  // test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node50);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(0   ,node60);

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

  //test Node ptr
  TEST_ASSERT_ROOT(node30   ,60    ,node90  ,node60);
  TEST_ASSERT_ROOT(node20   ,30    ,NULL    ,node30);
  TEST_ASSERT_ROOT(NULL     ,20    ,NULL    ,node20);
  TEST_ASSERT_ROOT(node80   ,90    ,node100 ,node90);
  TEST_ASSERT_ROOT(NULL     ,80    ,NULL    ,node80);
  TEST_ASSERT_ROOT(NULL     ,100   ,NULL    ,node100);

  // test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(-1  ,node30);
  TEST_ASSERT_BALANCE(0   ,node20);
  TEST_ASSERT_BALANCE(0   ,node90);
  TEST_ASSERT_BALANCE(0   ,node80);
  TEST_ASSERT_BALANCE(0   ,node100);
}

/**
 *             90                      60
 *            /  \                    /  \
 *          40   100                40    90
 *         / \            =>       /  \    \
 *       30  60                  30   50   100
 *           /
 *          50
 */
void test_double_rotation_Balance_Factor_minus_2_minus_1_1()
{
  Node *head;

  head=node90;
  avlAdd(&head,node100);
  avlAdd(&head,node40);
  avlAdd(&head,node60);
  avlAdd(&head,node30);
  avlAdd(&head,node50);

  //test Node ptr
  TEST_ASSERT_ROOT(node40   ,60    ,node90  ,node60);
  TEST_ASSERT_ROOT(node30   ,40    ,node50  ,node40);
  TEST_ASSERT_ROOT(NULL     ,30    ,NULL    ,node30);
  TEST_ASSERT_ROOT(NULL     ,50    ,NULL    ,node50);
  TEST_ASSERT_ROOT(NULL     ,90    ,node100 ,node90);
  TEST_ASSERT_ROOT(NULL     ,100   ,NULL    ,node100);

  // test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(0   ,node30);
  TEST_ASSERT_BALANCE(0   ,node50);
  TEST_ASSERT_BALANCE(1   ,node90);
  TEST_ASSERT_BALANCE(0   ,node100);
}


/**
 *
 *                     50
 *                   /    \
 *                 30      90
 *                / \     / \
 *              20  40  80  130
 *             /       /   /   \
 *           10      70  100   150
 *                        \     /
 *                        110  140
 *
 */
void test_avlAdd_by_adding_more_data_to_the_avl_tree(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node50;
  avlAdd(&head,node30);
  avlAdd(&head,node90);
  avlAdd(&head,node20);
  avlAdd(&head,node40);
  avlAdd(&head,node80);
  avlAdd(&head,node130);
  avlAdd(&head,node10);
  avlAdd(&head,node70);
  avlAdd(&head,node100);
  avlAdd(&head,node150);
  avlAdd(&head,node110);
  avlAdd(&head,node140);

  //test Node ptr
  TEST_ASSERT_ROOT(node30   ,50    ,node90  ,node50);
  TEST_ASSERT_ROOT(node20   ,30    ,node40  ,node30);
  TEST_ASSERT_ROOT(node10   ,20    ,NULL    ,node20);
  TEST_ASSERT_ROOT(NULL     ,10    ,NULL    ,node10);
  TEST_ASSERT_ROOT(NULL     ,40    ,NULL    ,node40);
  TEST_ASSERT_ROOT(node80   ,90    ,node130 ,node90);
  TEST_ASSERT_ROOT(node70   ,80    ,NULL    ,node80);
  TEST_ASSERT_ROOT(NULL     ,70    ,NULL    ,node70);
  TEST_ASSERT_ROOT(node100  ,130   ,node150 ,node130);
  TEST_ASSERT_ROOT(NULL     ,100   ,node110 ,node100);
  TEST_ASSERT_ROOT(node140  ,150   ,NULL    ,node150);
  TEST_ASSERT_ROOT(NULL     ,140   ,NULL    ,node140);
  TEST_ASSERT_ROOT(NULL     ,110   ,NULL    ,node110);

  // test balanceFactor
  TEST_ASSERT_BALANCE(1   ,node50);
  TEST_ASSERT_BALANCE(-1  ,node30);
  TEST_ASSERT_BALANCE(-1  ,node20);
  TEST_ASSERT_BALANCE(0   ,node10);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(1   ,node90);
  TEST_ASSERT_BALANCE(-1  ,node80);
  TEST_ASSERT_BALANCE(0   ,node70);
  TEST_ASSERT_BALANCE(0   ,node130);
  TEST_ASSERT_BALANCE(1   ,node100);
  TEST_ASSERT_BALANCE(-1  ,node150);
  TEST_ASSERT_BALANCE(0   ,node140);
  TEST_ASSERT_BALANCE(0   ,node110);
}

/**
 *
 *                     50                                50
 *                   /    \                            /    \
 *                 30      90                        30      90
 *                / \     / \                       / \     / \
 *              20  40  80  130         =>        20  40  80  140
 *             /       /       \                 /       /    /  \
 *           10      70        150             10      70   130  150
 *                             /
 *                            140
 *
 */
void test_avlAdd_by_adding_more_data_data_to_the_avl_tree1(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node50;
  avlAdd(&head,node30);
  avlAdd(&head,node90);
  avlAdd(&head,node20);
  avlAdd(&head,node40);
  avlAdd(&head,node80);
  avlAdd(&head,node130);
  avlAdd(&head,node10);
  avlAdd(&head,node70);
  avlAdd(&head,node150);
  avlAdd(&head,node140);

  //test Node ptr
  TEST_ASSERT_ROOT(node30   ,50    ,node90  ,node50);
  TEST_ASSERT_ROOT(node20   ,30    ,node40  ,node30);
  TEST_ASSERT_ROOT(node10   ,20    ,NULL    ,node20);
  TEST_ASSERT_ROOT(NULL     ,10    ,NULL    ,node10);
  TEST_ASSERT_ROOT(NULL     ,40    ,NULL    ,node40);
  TEST_ASSERT_ROOT(node80   ,90    ,node140 ,node90);
  TEST_ASSERT_ROOT(node70   ,80    ,NULL    ,node80);
  TEST_ASSERT_ROOT(NULL     ,70    ,NULL    ,node70);
  TEST_ASSERT_ROOT(node130  ,140   ,node150 ,node140);
  TEST_ASSERT_ROOT(NULL     ,150   ,NULL    ,node150);
  TEST_ASSERT_ROOT(NULL     ,130   ,NULL    ,node130);

  // test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node50);
  TEST_ASSERT_BALANCE(-1  ,node30);
  TEST_ASSERT_BALANCE(-1  ,node20);
  TEST_ASSERT_BALANCE(0   ,node10);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(0   ,node90);
  TEST_ASSERT_BALANCE(-1  ,node80);
  TEST_ASSERT_BALANCE(0   ,node70);
  TEST_ASSERT_BALANCE(0   ,node140);
  TEST_ASSERT_BALANCE(0   ,node150);
  TEST_ASSERT_BALANCE(0  ,node130);


}