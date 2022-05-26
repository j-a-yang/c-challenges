// John Yang
// NID : jo886471
// COP 3502, Spring 2017

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "KindredSpirits.h"

typedef struct list_node
{
	int data;
	struct list_node *next;
} list_node;

typedef struct LinkedList
{
	list_node *head;
	list_node *tail;
} LinkedList;

typedef struct Queue
{
	LinkedList *list;
  int count;
} Queue;

// Note: I borrowed and/or modified code provided to us by
// Dr. Szumlanski in our lessons on linked-list based queues.

// =========================================================================
// Some basic LinkedList functions to be used in LinkedList-based Queue
// application.
// =========================================================================
list_node *create_list_node(int data)
{
	list_node *n;

	if ((n = malloc(sizeof(list_node))) == NULL)
		return NULL;

	n->data = data;
	n->next = NULL;

	return n;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LinkedList *createList(void)
{
  LinkedList *list;

  if((list = calloc(1, sizeof(LinkedList))) == NULL)
    return NULL;

  return list;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
list_node *recursiveDestroyList(list_node *head)
{
  if(head == NULL)
    return NULL;

  recursiveDestroyList(head->next);
  free(head);

  return NULL;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LinkedList *destroyLinkedList(LinkedList *list)
{
  if(list == NULL)
    return NULL;

  recursiveDestroyList(list->head);
  free(list);

  return NULL;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void tailInsert(LinkedList* list, int data)
{
  if(list == NULL)
    return;

  else if(list->head == NULL)
    list->head = list->tail = create_list_node(data);

  else
    list->tail = list->tail->next = create_list_node(data);
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Removes the head of a linked list and returns the contents that
// were in the head.
int karateChop(LinkedList *list)
{
  int retVal;
  list_node *new_head;

  if(list == NULL || list->head == NULL)
    return INT_MIN;

  retVal = list->head->data;
  new_head = list->head->next;
  free(list->head);
  list->head = new_head;

  return retVal;
}

// =========================================================================
// Some basic Queue functions.
// =========================================================================
Queue *createQueue(void)
{
  Queue *q;

  if((q = malloc(sizeof(Queue))) == NULL)
    return NULL;

  q->count = 0;
  q->list = createList();

  return q;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int isEmpty(Queue *q)
{
  if(q == NULL || q->list == NULL || q->count == 0)
    return 1;

  return (q->list->head == NULL);
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void enqueue(Queue *q, int data)
{
  tailInsert(q->list, data);
  q->count++;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int dequeue(Queue *q)
{
  q->count--;
  return karateChop(q->list);
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void destroyQueue(Queue *q)
{
	destroyLinkedList(q->list);
	free(q);
}
// =========================================================================
// The following group of functions are unique/personalized
// helper functions for the kindredSpirits() function
// and the makeReflection() function.
// =========================================================================

// This is a recusive "helper function" that records a pre-order traversal
// of a binary tree in a queue.  It's designed to be called from within the
// create_pre_Queue() function.
Queue *preOrder_Queue(Queue *q, node *a)
{
  if(a == NULL)
    return NULL;

  enqueue(q, a->data);

  preOrder_Queue(q, a->left);
  preOrder_Queue(q, a->right);

	return q;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// This function takes a binary tree and returns a queue of the
// pre-order traversal of that tree.
Queue *create_pre_Queue(node *a)
{
	Queue *q;

	if(a == NULL)
    return NULL;

	q = createQueue();

	return preOrder_Queue(q, a);
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// This is a recusive "helper function" that records a post-order traversal
// of a binary tree in a queue.  It's designed to be called from within the
// create_post_Queue() function.
Queue *postOrder_Queue(Queue *q, node *a)
{
  if(a == NULL)
    return NULL;

  postOrder_Queue(q, a->left);
  postOrder_Queue(q, a->right);
  enqueue(q, a->data);

	return q;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// This function takes a binary tree and returns a queue of the
// post-order traversal of that tree.
Queue *create_post_Queue(node *a)
{
	Queue *q;

	if(a == NULL)
    return NULL;

	q = createQueue();

	return postOrder_Queue(q, a);
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// My own create node function for binary trees.
node *create_tree_node(int data)
{
  node *n;

	if((n = malloc(sizeof(node))) == NULL)
    return NULL;

	n->data = data;
	n->left = n->right = NULL;

	return n;
}
// =========================================================================
// The following functions are the ones required by Dr. Szumlanski.
// =========================================================================

// Recursive function that checks to see if two trees are reflections
// of each other.
int isReflection(node *a, node *b)
{
  // if both trees are empty, they are reflections of one another.
  if(a == NULL && b == NULL)
    return 1;

  // if only one tree is empty, they are not reflections of one another.
  else if(a == NULL || b == NULL)
    return 0;

  else if(a->data != b->data)
    return 0;

  return isReflection(a->left, b->right) && isReflection(a->right, b->left);
}
// =========================================================================
// Recursive function that takes a tree and creates a reflection of it.
node *makeReflection(node *root)
{
  node *new_root;

  if(root == NULL)
    return NULL;

  new_root = create_tree_node(root->data);
  new_root->left = makeReflection(root->right);
  new_root->right = makeReflection(root->left);

  return new_root;
}
// =========================================================================
int kindredSpirits(node *a, node *b)
{
  Queue *preQueue, *postQueue;

  // if both trees are empty, they are kindred spirits.
  if(a == NULL && b == NULL)
    return 1;

  // if only tree is empty, they are not kindred spirits.
  else if(a == NULL || b == NULL)
    return 0;

  // create two queues.
  preQueue = create_pre_Queue(a);
  postQueue = create_post_Queue(b);

  // if the amount of nodes in one tree is not the same as the other tree,
  // the trees are not kindred spirits.
  if(preQueue->count != postQueue->count)
  {
    destroyQueue(preQueue);
		destroyQueue(postQueue);
    return 0;
  }

  // Compare elements in both queues to see if they match up.
  // if everything matches up, they are kindred spirits.
  // if they don't match up, we leave the loop.
  while(!isEmpty(preQueue))
  {
    if(dequeue(preQueue) != dequeue(postQueue))
      break;

    if(isEmpty(preQueue))
    {
			destroyQueue(preQueue);
			destroyQueue(postQueue);
      return 1;
    }
  }

  // Just because the trees didn't match up during the first comparison
  // doesn't necesarrily mean they aren't kindred spirits.
  // The pre-order of tree 2 may match the post-order of tree 1.
	// So lets destroy previous queues and create two new ones; one for the
	// pre-order of tree 2 and one for the post-order of tree 1.
	destroyQueue(preQueue);
	destroyQueue(postQueue);
	preQueue = create_pre_Queue(b);
  postQueue = create_post_Queue(a);

  // Compare the new queues.  If they still don't match up here, they are not
  // kindred spirits.
  while(!isEmpty(preQueue))
  {
    if(dequeue(preQueue) != dequeue(postQueue))
    {
			destroyQueue(preQueue);
			destroyQueue(postQueue);
      return 0;
    }

  }

  // If we make it this far without returning from the function,
  // then we know the elements of both queues match up during the second
  // comparison.  We will now clean up after ourselves and return 1.
	destroyQueue(preQueue);
	destroyQueue(postQueue);
  return 1;
}
// =========================================================================
double difficultyRating(void)
{
  return 2.8;
}
// =========================================================================
double hoursSpent(void)
{
  return 15.0;
}
// =========================================================================
