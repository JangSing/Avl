#include "unity.h"
#include "avlAdd.h"
#include "Node.h"
#include "Rotation.h"
#include "ErrorObject.h"
#include "CException.h"
#include "avlRemove.h"
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

void tearDown(void)
{
}


/**
 *        60       (remove 150)
 *       /  \           =>             (unchange)
 *     50    100
 */
void test_avlRemove_given_removing_node_not_in_tree_should_return_NULL(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node50);
  avlAdd(&head,node100);

  removeNode=avlRemove(&head,150,&heightChange);

  TEST_ASSERT_NULL(removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node50   ,60   ,node100  ,node60);
  TEST_ASSERT_ROOT(NULL     ,100  ,NULL     ,node100);
  TEST_ASSERT_ROOT(NULL     ,50   ,NULL     ,node50);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(0   ,node100);
  TEST_ASSERT_BALANCE(0   ,node50);
}

/**
 *        60        (remove 100)         60
 *       /  \            =>             /
 *     50    100                      50
 */
void test_avlRemove_when_removing_right_node_balance_Factor_should_subtract_1(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node50);
  avlAdd(&head,node100);

  removeNode=avlRemove(&head,100,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node100,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node50   ,60   ,NULL   ,node60);
  TEST_ASSERT_ROOT(NULL     ,50   ,NULL   ,node50);

  //test balanceFactor
  TEST_ASSERT_BALANCE(-1  ,node60);
  TEST_ASSERT_BALANCE(0   ,node50);
}

/**
 *        60                               60
 *       /  \        (remove 110)         /  \
 *     50    100          =>            50   100
 *           / \                             /
 *         90  110                         90
 */
void test_avlRemove_removing_right_node_at_the_child_with_condition_height_no_change_but_current_Balance_change(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node50);
  avlAdd(&head,node100);
  avlAdd(&head,node110);
  avlAdd(&head,node90);

  removeNode=avlRemove(&head,110,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node110,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node50   ,60   ,node100  ,node60);
  TEST_ASSERT_ROOT(NULL     ,50   ,NULL     ,node50);
  TEST_ASSERT_ROOT(node90   ,100  ,NULL     ,node100);
  TEST_ASSERT_ROOT(NULL     ,90   ,NULL     ,node90);

  //test balanceFactor
  TEST_ASSERT_BALANCE(1   ,node60);
  TEST_ASSERT_BALANCE(0   ,node50);
  TEST_ASSERT_BALANCE(-1  ,node100);
  TEST_ASSERT_BALANCE(0   ,node90);
}

/**
 *        60                                 60
 *       /  \            (remove 110)       /  \
 *     50    100              =>          50   100
 *            \
 *            110
 */
void test_avlRemove_removing_right_node_at_the_child_with_condition_height_change_and_current_Balance_change(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node50);
  avlAdd(&head,node100);
  avlAdd(&head,node110);

  removeNode=avlRemove(&head,110,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node110,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node50   ,60   ,node100  ,node60);
  TEST_ASSERT_ROOT(NULL     ,100  ,NULL     ,node100);
  TEST_ASSERT_ROOT(NULL     ,50   ,NULL     ,node50);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(0   ,node100);
  TEST_ASSERT_BALANCE(0   ,node50);
}

/**
 *        60          (remove 50)          60
 *       /  \               =>               \
 *     50    100                             100
 */
void test_avlRemove_when_removing_left_node_balance_Factor_should_add_1(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node50);
  avlAdd(&head,node100);

  removeNode=avlRemove(&head,50,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node50,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(NULL   ,60   ,node100  ,node60);
  TEST_ASSERT_ROOT(NULL   ,100  ,NULL     ,node100);

  //test balanceFactor
  TEST_ASSERT_BALANCE(1   ,node60);
  TEST_ASSERT_BALANCE(0   ,node100);
}

/**
 *        60                              60
 *       /  \       (remove 90)          /  \
 *     50    100         =>            50   100
 *           / \                              \
 *         90  110                            110
 */
void test_avlRemove_removing_left_node_at_the_child_with_condition_height_no_change_but_current_Balance_change(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node50);
  avlAdd(&head,node100);
  avlAdd(&head,node110);
  avlAdd(&head,node90);

  removeNode=avlRemove(&head,90,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node90,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node50   ,60   ,node100  ,node60);
  TEST_ASSERT_ROOT(NULL     ,50   ,NULL     ,node50);
  TEST_ASSERT_ROOT(NULL     ,100  ,node110  ,node100);
  TEST_ASSERT_ROOT(NULL     ,110  ,NULL     ,node110);

  //test balanceFactor
  TEST_ASSERT_BALANCE(1   ,node60);
  TEST_ASSERT_BALANCE(1   ,node100);
  TEST_ASSERT_BALANCE(0   ,node50);
  TEST_ASSERT_BALANCE(0   ,node110);
}

/**
 *        60                           60
 *       /  \      (remove 90)        /  \
 *     50    100        =>          50   100
 *           /
 *         90
 */
void test_avlRemove_removing_left_node_at_the_child_with_condition_height_change_and_current_Balance_change(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node50);
  avlAdd(&head,node100);
  avlAdd(&head,node90);

  removeNode=avlRemove(&head,90,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node90,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node50   ,60   ,node100  ,node60);
  TEST_ASSERT_ROOT(NULL     ,100  ,NULL     ,node100);
  TEST_ASSERT_ROOT(NULL     ,50   ,NULL     ,node50);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(0   ,node100);
  TEST_ASSERT_BALANCE(0   ,node50);
}

/**
 *              60        (remove 40)            70
 *             /  \            =>               /  \
 *           40    70                         60    80
 *                  \
 *                  80
 */
void test_avlRemove_removing_left_node_given_after_removing_the_condition_is_2_0_1_should_do_left_rotation(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node40);
  avlAdd(&head,node70);
  avlAdd(&head,node80);

  removeNode=avlRemove(&head,40,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node40,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node60   ,70   ,node80   ,node70);
  TEST_ASSERT_ROOT(NULL     ,60   ,NULL     ,node60);
  TEST_ASSERT_ROOT(NULL     ,80   ,NULL     ,node80);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node70);
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(0   ,node80);
}

/**
 *              60        (remove 40)           70
 *             /  \            =>              /  \
 *           40    80                        60    80
 *                /
 *              70
 */
void test_avlRemove_removing_left_node_given_after_removing_the_condition_is_2_0_minus_1_should_do_right_left_rotation(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node40);
  avlAdd(&head,node80);
  avlAdd(&head,node70);

  removeNode=avlRemove(&head,40,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node40,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node60   ,70   ,node80   ,node70);
  TEST_ASSERT_ROOT(NULL     ,60   ,NULL     ,node60);
  TEST_ASSERT_ROOT(NULL     ,80   ,NULL     ,node80);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node70);
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(0   ,node80);
}

/**
 *              60           (remove 70)              60
 *             /  \               =>                 /  \
 *           40    80                              40    90
 *          /     /  \                            /     /  \
 *        30    70   90                         30    80   100
 *                     \
 *                     100
 */
void test_avlRemove_removing_left_node_at_child_given_after_removing_the_condition_is_2_0_1_at_right_child_should_do_left_rotation_at_right_child(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node40);
  avlAdd(&head,node80);
  avlAdd(&head,node30);
  avlAdd(&head,node70);
  avlAdd(&head,node90);
  avlAdd(&head,node100);

  removeNode=avlRemove(&head,70,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node70,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node40   ,60   ,node90   ,node60);
  TEST_ASSERT_ROOT(node30   ,40   ,NULL     ,node40);
  TEST_ASSERT_ROOT(NULL     ,30   ,NULL     ,node30);
  TEST_ASSERT_ROOT(node80   ,90   ,node100  ,node90);
  TEST_ASSERT_ROOT(NULL     ,80   ,NULL     ,node80);
  TEST_ASSERT_ROOT(NULL     ,100  ,NULL     ,node100);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(-1  ,node40);
  TEST_ASSERT_BALANCE(0   ,node30);
  TEST_ASSERT_BALANCE(0   ,node90);
  TEST_ASSERT_BALANCE(0   ,node80);
  TEST_ASSERT_BALANCE(0   ,node100);
}

/**
 *              60           (remove 100)             60
 *             /  \               =>                 /  \
 *           40    80                              40    80
 *          /     /  \                            /     /  \
 *        30    70   90                         30    70   90
 *                     \
 *                     100
 */
void test_avlRemove_removing_right_child_if_balance_should_return_removed_node(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node40);
  avlAdd(&head,node80);
  avlAdd(&head,node30);
  avlAdd(&head,node70);
  avlAdd(&head,node90);
  avlAdd(&head,node100);

  removeNode=avlRemove(&head,100,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node100,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node40   ,60   ,node80   ,node60);
  TEST_ASSERT_ROOT(node30   ,40   ,NULL     ,node40);
  TEST_ASSERT_ROOT(NULL     ,30   ,NULL     ,node30);
  TEST_ASSERT_ROOT(node70   ,80   ,node90   ,node80);
  TEST_ASSERT_ROOT(NULL     ,70   ,NULL     ,node70);
  TEST_ASSERT_ROOT(NULL     ,90   ,NULL     ,node90);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(-1  ,node40);
  TEST_ASSERT_BALANCE(0   ,node30);
  TEST_ASSERT_BALANCE(0   ,node80);
  TEST_ASSERT_BALANCE(0   ,node70);
  TEST_ASSERT_BALANCE(0   ,node90);
}

/**
 *
 *            60                             60
 *           /  \        (remove 50)        /  \
 *         50   70           =>           40    70
 *        /
 *      40
 *
 */
void test_avlRemove_removing_intermidiate_left_child_if_right_node_equal_NULL_should_replace_by_left_node(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node50);
  avlAdd(&head,node70);
  avlAdd(&head,node40);

  removeNode=avlRemove(&head,50,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node50,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node40   ,60   ,node70   ,node60);
  TEST_ASSERT_ROOT(NULL     ,40   ,NULL     ,node40);
  TEST_ASSERT_ROOT(NULL     ,70   ,NULL     ,node70);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(0   ,node70);
}

/**
 *
 *         60                            60
 *        /  \       (remove 40)        /  \
 *      40    70          =>          50    70
 *        \
 *        50
 *
 */
void test_avlRemove_removing_intermidiate_left_child_if_left_node_equal_NULL_should_replace_by_right_node(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node40);
  avlAdd(&head,node70);
  avlAdd(&head,node50);

  removeNode=avlRemove(&head,40,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node40,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node50   ,60   ,node70   ,node60);
  TEST_ASSERT_ROOT(NULL     ,50   ,NULL     ,node50);
  TEST_ASSERT_ROOT(NULL     ,70   ,NULL     ,node70);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(0   ,node50);
  TEST_ASSERT_BALANCE(0   ,node70);
}

/**
 *
 *         60                             60
 *        /  \        (remove 70)        /  \
 *      40    70          =>           40    80
 *             \
 *              80
 *
 */
void test_avlRemove_removing_intermidiate_right_child_if_left_node_equal_NULL_should_replace_by_right_node(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node40);
  avlAdd(&head,node70);
  avlAdd(&head,node80);

  removeNode=avlRemove(&head,70,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node70,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node40   ,60   ,node80   ,node60);
  TEST_ASSERT_ROOT(NULL     ,40   ,NULL     ,node40);
  TEST_ASSERT_ROOT(NULL     ,80   ,NULL     ,node80);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(0   ,node80);
}

/**
 *
 *         60                           60
 *        /  \        (remove 80)      /  \
 *      40    80           =>        40   70
 *           /
 *          70
 */
void test_avlRemove_removing_intermidiate_right_child_if_right_node_equal_NULL_should_replace_by_left_node(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node40);
  avlAdd(&head,node80);
  avlAdd(&head,node70);

  removeNode=avlRemove(&head,80,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node80,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node40   ,60   ,node70   ,node60);
  TEST_ASSERT_ROOT(NULL     ,40   ,NULL     ,node40);
  TEST_ASSERT_ROOT(NULL     ,70   ,NULL     ,node70);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node60);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(0   ,node70);
}

/**
 *
 *         60                           70
 *        /  \         (remove 60)     /  \
 *      40    80            =>       40   80
 *           /
 *          70
 */
void test_avlRemove_1(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node40);
  avlAdd(&head,node80);
  avlAdd(&head,node70);

  removeNode=avlRemove(&head,60,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node60,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node40   ,70   ,node80   ,node70);
  TEST_ASSERT_ROOT(NULL     ,40   ,NULL     ,node40);
  TEST_ASSERT_ROOT(NULL     ,80   ,NULL     ,node80);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node70);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(0   ,node80);
}

/**
 *
 *         60                           80
 *        /  \         (remove 60)     /
 *      40    80            =>       40
 *
 *
 */
void test_avlRemove_2(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node40);
  avlAdd(&head,node80);

  removeNode=avlRemove(&head,60,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node60,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node40   ,80   ,NULL   ,node80);
  TEST_ASSERT_ROOT(NULL     ,40   ,NULL   ,node40);

  //test balanceFactor
  TEST_ASSERT_BALANCE(-1  ,node80);
  TEST_ASSERT_BALANCE(0   ,node40);
}

/**
 *
 *         60                           80
 *        /  \         (remove 60)     / \
 *      40    80            =>       40   90
 *             \
 *             90
 */
void test_avlRemove_3(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node60;
  avlAdd(&head,node40);
  avlAdd(&head,node80);
  avlAdd(&head,node90);

  removeNode=avlRemove(&head,60,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node60,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node40   ,80   ,node90 ,node80);
  TEST_ASSERT_ROOT(NULL     ,40   ,NULL   ,node40);
  TEST_ASSERT_ROOT(NULL     ,90   ,NULL   ,node90);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node80);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(0   ,node90);
}

/**
 *
 *                     50                                            50
 *                   /    \                                        /    \
 *                 30      90                                    30      90
 *                / \     / \         (remove 110)              / \     / \
 *              20  40  80  110           =>                  20  40  80  120
 *             /       /   /  \                              /       /   /  \
 *           10      70  100  130                          10      70  100  130
 *                            /
 *                          120
 *
 */
void test_avlRemove_4(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node50;
  avlAdd(&head,node30);
  avlAdd(&head,node90);
  avlAdd(&head,node20);
  avlAdd(&head,node40);
  avlAdd(&head,node80);
  avlAdd(&head,node110);
  avlAdd(&head,node10);
  avlAdd(&head,node70);
  avlAdd(&head,node100);
  avlAdd(&head,node130);
  avlAdd(&head,node120);

  removeNode=avlRemove(&head,110,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node110,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node30   ,50   ,node90   ,node50);
  TEST_ASSERT_ROOT(node20   ,30   ,node40   ,node30);
  TEST_ASSERT_ROOT(node10   ,20   ,NULL     ,node20);
  TEST_ASSERT_ROOT(NULL     ,10   ,NULL     ,node10);
  TEST_ASSERT_ROOT(NULL     ,40   ,NULL     ,node40);
  TEST_ASSERT_ROOT(node80   ,90   ,node120  ,node90);
  TEST_ASSERT_ROOT(node70   ,80   ,NULL     ,node80);
  TEST_ASSERT_ROOT(NULL     ,70   ,NULL     ,node70);
  TEST_ASSERT_ROOT(node100  ,120  ,node130  ,node120);
  TEST_ASSERT_ROOT(NULL     ,130  ,NULL     ,node130);
  TEST_ASSERT_ROOT(NULL     ,100  ,NULL     ,node100);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node50);
  TEST_ASSERT_BALANCE(-1  ,node30);
  TEST_ASSERT_BALANCE(-1  ,node20);
  TEST_ASSERT_BALANCE(0   ,node10);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(0   ,node90);
  TEST_ASSERT_BALANCE(-1  ,node80);
  TEST_ASSERT_BALANCE(0   ,node70);
  TEST_ASSERT_BALANCE(0   ,node120);
  TEST_ASSERT_BALANCE(0   ,node130);
  TEST_ASSERT_BALANCE(0   ,node100);
}

/**
 *
 *                     50                                             70
 *                   /    \                                        /     \
 *                 30      90                                    30      110
 *                / \     / \         (remove 50)               / \     /   \
 *              20  40  80  110           =>                  20  40  90    130
 *             /       /   /  \                              /       / \    /
 *           10      70  100  130                          10      80 100 120
 *                            /
 *                          120
 *
 */
void test_avlRemove_5(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node50;
  avlAdd(&head,node30);
  avlAdd(&head,node90);
  avlAdd(&head,node20);
  avlAdd(&head,node40);
  avlAdd(&head,node80);
  avlAdd(&head,node110);
  avlAdd(&head,node10);
  avlAdd(&head,node70);
  avlAdd(&head,node100);
  avlAdd(&head,node130);
  avlAdd(&head,node120);

  removeNode=avlRemove(&head,50,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node50,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node30   ,70   ,node110  ,node70);
  TEST_ASSERT_ROOT(node20   ,30   ,node40   ,node30);
  TEST_ASSERT_ROOT(node10   ,20   ,NULL     ,node20);
  TEST_ASSERT_ROOT(NULL     ,10   ,NULL     ,node10);
  TEST_ASSERT_ROOT(NULL     ,40   ,NULL     ,node40);
  TEST_ASSERT_ROOT(node90   ,110  ,node130  ,node110);
  TEST_ASSERT_ROOT(node80   ,90   ,node100  ,node90);
  TEST_ASSERT_ROOT(NULL     ,80   ,NULL     ,node80);
  TEST_ASSERT_ROOT(NULL     ,100  ,NULL     ,node100);
  TEST_ASSERT_ROOT(node120  ,130  ,NULL     ,node130);
  TEST_ASSERT_ROOT(NULL     ,120  ,NULL     ,node120);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node70);
  TEST_ASSERT_BALANCE(-1  ,node30);
  TEST_ASSERT_BALANCE(-1  ,node20);
  TEST_ASSERT_BALANCE(0   ,node10);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(0   ,node110);
  TEST_ASSERT_BALANCE(0   ,node90);
  TEST_ASSERT_BALANCE(0   ,node80);
  TEST_ASSERT_BALANCE(0   ,node100);
  TEST_ASSERT_BALANCE(-1  ,node130);
  TEST_ASSERT_BALANCE(0   ,node120);
}

/**
 *
 *                     50                                             70
 *                   /    \                                        /     \
 *                 30      90                                    30      90
 *                / \     / \         (remove 50)               / \     /   \
 *              20  40  70  110           =>                  20  40  80    110
 *                       \
 *                       80
 */
void test_avlRemove_6(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node50;
  avlAdd(&head,node30);
  avlAdd(&head,node90);
  avlAdd(&head,node20);
  avlAdd(&head,node40);
  avlAdd(&head,node70);
  avlAdd(&head,node110);
  avlAdd(&head,node80);

  removeNode=avlRemove(&head,50,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node50,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node30   ,70   ,node90   ,node70);
  TEST_ASSERT_ROOT(node20   ,30   ,node40   ,node30);
  TEST_ASSERT_ROOT(NULL     ,20   ,NULL     ,node20);
  TEST_ASSERT_ROOT(NULL     ,40   ,NULL     ,node40);
  TEST_ASSERT_ROOT(node80   ,90   ,node110  ,node90);
  TEST_ASSERT_ROOT(NULL     ,110  ,NULL     ,node110);
  TEST_ASSERT_ROOT(NULL     ,80   ,NULL     ,node80);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node70);
  TEST_ASSERT_BALANCE(0   ,node30);
  TEST_ASSERT_BALANCE(0   ,node20);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(0   ,node90);
  TEST_ASSERT_BALANCE(0   ,node110);
  TEST_ASSERT_BALANCE(0   ,node80);
}

/**
 *
 *                     50                                            50
 *                   /    \                                        /    \
 *                 30      90                                    30     100
 *                / \     / \         (remove 90)               / \     / \
 *              20  40  80  110           =>                  20  40  80  120
 *             /       /   /  \                              /       /   /  \
 *           10      70  100  130                          10      70  110  130
 *                            /
 *                          120
 *
 */
void test_avlRemove_7(void)
{
  Node *head,*removeNode;
  int heightChange=0;

  head=node50;
  avlAdd(&head,node30);
  avlAdd(&head,node90);
  avlAdd(&head,node20);
  avlAdd(&head,node40);
  avlAdd(&head,node80);
  avlAdd(&head,node110);
  avlAdd(&head,node10);
  avlAdd(&head,node70);
  avlAdd(&head,node100);
  avlAdd(&head,node130);
  avlAdd(&head,node120);

  removeNode=avlRemove(&head,90,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node90,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node30   ,50   ,node100  ,node50);
  TEST_ASSERT_ROOT(node20   ,30   ,node40   ,node30);
  TEST_ASSERT_ROOT(node10   ,20   ,NULL     ,node20);
  TEST_ASSERT_ROOT(NULL     ,10   ,NULL     ,node10);
  TEST_ASSERT_ROOT(NULL     ,40   ,NULL     ,node40);
  TEST_ASSERT_ROOT(node80   ,100  ,node120  ,node100);
  TEST_ASSERT_ROOT(node70   ,80   ,NULL     ,node80);
  TEST_ASSERT_ROOT(NULL     ,70   ,NULL     ,node70);
  TEST_ASSERT_ROOT(node110  ,120  ,node130  ,node120);
  TEST_ASSERT_ROOT(NULL     ,110  ,NULL     ,node110);
  TEST_ASSERT_ROOT(NULL     ,130  ,NULL     ,node130);

  //test balanceFactor
  TEST_ASSERT_BALANCE(0   ,node50);
  TEST_ASSERT_BALANCE(-1  ,node30);
  TEST_ASSERT_BALANCE(-1  ,node20);
  TEST_ASSERT_BALANCE(0   ,node10);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(0   ,node100);
  TEST_ASSERT_BALANCE(-1  ,node80);
  TEST_ASSERT_BALANCE(0   ,node70);
  TEST_ASSERT_BALANCE(0   ,node120);
  TEST_ASSERT_BALANCE(0   ,node110);
  TEST_ASSERT_BALANCE(0   ,node130);
}

/**
 *
 *                     50                                             50
 *                   /    \                                         /    \
 *                 30      90                                     30     100
 *                / \     / \         (remove 90)                / \     / \
 *              20  40  80  130           =>                   20  40  80  130
 *             /       /   /   \                              /       /   /  \
 *           10      70  100   150                          10      70  110  150
 *                        \     /                                            /
 *                        110  140                                         140
 *
 */
void test_avlRemove_8(void)
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

  removeNode=avlRemove(&head,90,&heightChange);

  TEST_ASSERT_EQUAL_PTR(node90,removeNode);

  //test Node ptr
  TEST_ASSERT_ROOT(node30   ,50   ,node100  ,node50);
  TEST_ASSERT_ROOT(node20   ,30   ,node40   ,node30);
  TEST_ASSERT_ROOT(node10   ,20   ,NULL     ,node20);
  TEST_ASSERT_ROOT(NULL     ,10   ,NULL     ,node10);
  TEST_ASSERT_ROOT(NULL     ,40   ,NULL     ,node40);
  TEST_ASSERT_ROOT(node80   ,100  ,node130  ,node100);
  TEST_ASSERT_ROOT(node70   ,80   ,NULL     ,node80);
  TEST_ASSERT_ROOT(NULL     ,70   ,NULL     ,node70);
  TEST_ASSERT_ROOT(node110  ,130  ,node150  ,node130);
  TEST_ASSERT_ROOT(node140  ,150  ,NULL     ,node150);
  TEST_ASSERT_ROOT(NULL     ,140  ,NULL     ,node140);

  //test balanceFactor
  TEST_ASSERT_BALANCE(1   ,node50);
  TEST_ASSERT_BALANCE(-1  ,node30);
  TEST_ASSERT_BALANCE(-1  ,node20);
  TEST_ASSERT_BALANCE(0   ,node10);
  TEST_ASSERT_BALANCE(0   ,node40);
  TEST_ASSERT_BALANCE(1   ,node100);
  TEST_ASSERT_BALANCE(-1  ,node80);
  TEST_ASSERT_BALANCE(0   ,node70);
  TEST_ASSERT_BALANCE(1   ,node130);
  TEST_ASSERT_BALANCE(-1   ,node150);
  TEST_ASSERT_BALANCE(0   ,node140);

}



