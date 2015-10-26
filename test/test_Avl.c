#include "unity.h"
#include "Avl.h"
#include "Node.h"
#include "ErrorObject.h"
#include "CException.h"

void setUp()
{
}

void tearDown()
{
}

void test_throw_err_if_existance_of_two_same_data()
{
  int balanceFactor;
  ErrorObject *err;
  
  Node *head;
  Node *node20=createNode(NULL,20,NULL);
  
  Node *newNode=createNode(NULL,20,NULL);
  
  head=node20;
  
  Try{
    balanceFactor=avlAdd(&head,newNode);
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("The newNode data has already in the avl tree",err->errorMsg);
  }
    
}  


/**
 *          20               20                     
 *                  =>         \
 *                              40
 */
void test_function_avlAdd_given_new_Node_should_add_into_tree1()
{
  int balanceFactor;
  
  Node *head;
  Node *node20=createNode(NULL,20,NULL);
  
  Node *newNode=createNode(NULL,40,NULL);
  
  head=node20;
  
  balanceFactor=avlAdd(&head,newNode);
  
  TEST_ASSERT_EQUAL(1,balanceFactor);
  TEST_ASSERT_EQUAL_PTR(newNode,head->right);
}

/**
 *          20                20                     
 *         /         =>      /  \
 *       10                10    40
 */
void test_function_avlAdd_given_new_Node_should_add_into_tree2()
{
  int balanceFactor;
  
  Node *head;
  Node *node10=createNode(NULL,10,NULL);
  Node *node20=createNode(node10,20,NULL);
  
  Node *newNode=createNode(NULL,40,NULL);
  
  head=node20;
  
  balanceFactor=avlAdd(&head,newNode);
  
  TEST_ASSERT_EQUAL(0,balanceFactor);
  TEST_ASSERT_EQUAL_PTR(newNode,head->right);
}

/**
 *          20                20                     
 *            \      =>      /  \
 *             30          10    30      
 */
void test_function_avlAdd_given_new_Node_should_add_into_tree3()
{
  int balanceFactor;
  
  Node *head;
  Node *node30=createNode(NULL,30,NULL);
  Node *node20=createNode(NULL,20,node30);
  
  Node *newNode=createNode(NULL,10,NULL);
  
  head=node20;
  
  balanceFactor=avlAdd(&head,newNode);
  
  TEST_ASSERT_EQUAL(0,balanceFactor);
  TEST_ASSERT_EQUAL_PTR(newNode,head->left);
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
  Node *node10=createNode(NULL,10,NULL);
  Node *node30=createNode(NULL,30,NULL);
  Node *node20=createNode(node10,20,node30);
  
  Node *newNode=createNode(NULL,40,NULL);
  Node *newNode1=createNode(NULL,50,NULL);
  Node *newNode2=createNode(NULL,60,NULL);
  
  head=node20;
  
  TEST_ASSERT_EQUAL_PTR(head,node20);
  TEST_ASSERT_EQUAL_PTR(node10,head->left);
  TEST_ASSERT_EQUAL_PTR(node30,head->right);
  
  balanceFactor=avlAdd(&head,newNode);
  
  TEST_ASSERT_EQUAL(1,balanceFactor);
  TEST_ASSERT_EQUAL_PTR(newNode,head->right->right);
  TEST_ASSERT_NULL(head->right->left);
  
  balanceFactor=0;
}

  
  
  
