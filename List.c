/******************************************************************************
# Alec Siegel                                                                 #
# 1744236                                                                     #
# PA3                                                                         #
*******************************************************************************/

//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj
{
  long data;
  struct NodeObj *next;
  struct NodeObj *previous;
} NodeObj;

// private Node type
typedef NodeObj *Node;

// private ListObj type
typedef struct ListObj
{
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;

} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object.
// Initializes next, previous, and data fields.
// Private.
Node newNode(long data)
{
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->next = NULL;
  N->previous = NULL;
  return (N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node *pN)
{
  if (pN != NULL && *pN != NULL)
  {
    free(*pN);
    *pN = NULL;
  }
}
// newList()
// Returns reference to new empty List object.
List newList(void)
{
  List B;
  B = malloc(sizeof(ListObj));
  B->front = B->back = B->cursor = NULL;
  B->length = 0;
  B->index = -1;
  return (B);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List *pL)
{
  if (pL != NULL && *pL != NULL)
  {
    clear(*pL);
    free(*pL);
    *pL = NULL;
  }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L)
{
  if (L == NULL)
  {
    fprintf(stderr, "List Error: calling length() on NULL List reference\n");
    exit(1);
  }
  return (L->length);
}
// index()
// Returns index of L if defined, -1 otherwise.
int index(List L) { return (L == NULL ? -1 : L->index); }
// front()
// returns front element of L
// Pre: length()>0
long front(List L)
{
  if (length(L) <= 0)
  {
    fprintf(stderr, "List Error: calling front() on empty List reference\n");
    exit(1);
  }
  return L->front->data;
}
// back()
// returns back element of L
// Pre: length()>0
long back(List L)
{
  if (length(L) <= 0)
  {
    fprintf(stderr, "List Error: calling back() on empty List reference\n");
    exit(1);
  }
  return L->back->data;
}
// get()
// Returns cursor element of L.
// Pre: length()>0, index()>=0
long get(List L)
{
  if (length(L) <= 0)
  {
    fprintf(stderr,"List Error: calling get() on an empty List reference\n");
    exit(1);
  }
  if (index(L) < 0)
  {
    fprintf(stderr, "List Error: calling get() on List with undefinied index\n");
    exit(1);
  }
  return L->cursor->data;
}
// listEquals()
// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
int listEquals(List A, List B)
{
  
  if (A == NULL || B == NULL)
  {
    fprintf(stderr, "List Error: calling listEquals() on NULL List reference\n");
    exit(1);
  }
  List C = A;
  List D= B;
  int eq;
  eq = (C->length == D->length);                                              //compare lengths first
  for (moveFront(C), moveFront(D); eq && C->cursor; moveNext(C), moveNext(D)) //while no differences have been found
  {
    eq = (C->cursor->data == D->cursor->data); //compare data in each node
  }
  return eq;
}

// Manipulation procedures ----------------------------------------------------
// clear()
// Resets L to its original empty state.
void clear(List L)
{
  while (length(L) > 0)
  {
    moveFront(L);
    delete (L);
    //printf("Length: %d\n", length(L));
  }
  L->length = 0;
  L->index = -1;
}
// moveFront()
// If L is non-empty, sets cursor under the front
// element, otherwise does nothing
void moveFront(List L)
{
  if (length(L) > 0)
  {
    L->cursor = L->front;
    L->index = 0;
  }
}
// moveBack()
// If L is non-empty, sets cursor under the back
// element, otherwise does nothing
void moveBack(List L)
{
  if (length(L) > 0)
  {
    L->cursor = L->back;
    L->index = (length(L) - 1);
  }
}
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and
// at front, cursor becomes undefined; if cursor is
// undefined do nothing
void movePrev(List L)
{
  if (L->cursor == NULL)
  {
    return;
  }
  else if (L->cursor == L->front)
  {
    L->cursor = NULL;
    L->index = -1;
  }
  else
  {
    L->cursor = L->cursor->previous;
    L->index--;
  }
}
// moveNext()
// If L->cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and
// at back, cursor becomes undefined; if cursor is
// undefined do nothing
void moveNext(List L)
{
  if (L->cursor == NULL)
  {
    return;
  }
  if (L->cursor == L->back)
  {
    L->cursor = NULL;
    L->index = -1;
  }
  else
  {
    L->cursor = L->cursor->next;
    L->index++;
  }
}
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, long data)
{
  if (length(L) == 0)
  {
    L->front = newNode(data);
    L->back = L->front;
    L->length = 1;
  }
  else
  {
    Node temp = L->front;
    L->front = newNode(data);
    temp->previous = L->front;
    L->front->next = temp;
    L->length++;
    L->index++;
  }
}
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, long data)
{
  if (length(L) == 0)
  {
    L->back = newNode(data);
    L->front = L->back;
    L->length = 1;
  }
  else
  {
    Node temp = L->back;
    L->back = newNode(data);
    temp->next = L->back;
    L->back->previous = temp;
    L->length++;
  }
}
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, long data)
{
  if (length(L) <= 0)
  {
    fprintf(stderr, "List Error: calling insertBefore() on an empty List reference\n");
    exit(1);
  }
  if (index(L) < 0)
  {
    fprintf(stderr, 
        "List Error: calling insertBefore() on List with undefinied index\n");
    exit(1);
  }
  Node temp = newNode(data);
  temp->previous = L->cursor->previous;
  L->cursor->previous = temp;
  temp->next = L->cursor;
  if (temp->previous)
  {
    temp->previous->next = temp;
  }
  else
  {
    L->front = temp;
  }
  L->length++;
  L->index++;
}
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, long data)
{
  if (length(L) <= 0)
  {
    fprintf(stderr, "List Error: calling insertAfter() on an empty List reference\n");
    exit(1);
  }
  if (index(L) < 0)
  {
    fprintf(stderr, "List Error: calling insertAfter() on List with undefinied index\n");
    exit(1);
  }
  Node temp = newNode(data);
  temp->next = L->cursor->next;
  L->cursor->next = temp;
  temp->previous = L->cursor;
  if (temp->next)
  {
    temp->next->previous = temp;
  }
  else
  {
    L->back = temp;
  }
  L->length++;
}
// Delete the front element.
// Pre: length()>0
void deleteFront(List L)
{
  if (length(L) <= 0)
  {
    fprintf(stderr, "List Error: calling deleteFront() on an empty List reference\n");
    exit(1);
  }
  if (L->front == NULL)
  {
    return;
  }
  Node temp = L->front;
  L->front = L->front->next;
  if (L->front && L->front->next == NULL)
  {
    L->back = L->front;
  }
  L->length--;
  ;
  freeNode(&temp);
  if (index >= 0)
  {
    L->index--;
  }
}
// Delete the back element
// Pre: length()>0
void deleteBack(List L)
{

  if (length(L) <= 0)
  {
    fprintf(stderr, "List Error: calling deleteBack() on an empty List reference\n");
    exit(1);
  }
  if (L->back == NULL)
  {
    return;
  }
  if (L->cursor == L->back)
  {
    L->cursor = NULL;
    L->index = -1;
  }
  Node temp = L->back;
  L->back = L->back->previous;
  if (L->back && L->back->previous == NULL)
  {
    L->front = L->back;
  }
  L->length--;
  freeNode(&temp);
}
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete (List L)
{
  if (length(L) <= 0)
  {
    fprintf(stderr, "List Error: calling delete() on an empty List reference\n");
    exit(1);
  }
  if (index(L) < 0)
  {
    fprintf(stderr, "List Error: calling delete() on List with undefinied index\n");
    exit(1);
  }
  if (L->cursor == NULL)
  {
    return;
  }
  if (L->front == L->cursor)
  {
    L->front = L->cursor->next;
  }
  if (L->back == L->cursor)
  {
    L->back = L->cursor->previous;
  }
  //if cursor element has a previous element
  if (L->cursor->previous)
  {
    L->cursor->previous->next = L->cursor->next; //previous element next now points to element after cursor element
  }
  //if cursor element has a next element
  if (L->cursor->next)
  {
    L->cursor->next->previous = L->cursor->previous; //next element previous now points to element before cursor element
  }
  L->length--;
  freeNode(&L->cursor);
  
  //cursor becomes undefined
  L->index = -1;
  L->cursor = NULL;
}
// set()
// Overwrites the cursor element with x.
//Pre: length()>0, index()>=0
void set(List L, long x)
{
  L->cursor->data = x;
}
// Other operations -----------------------------------------------------------
// PrintList()
// Prints to the file pointed to by out, a
// string representation of L
void printList(FILE *out, List L)
{
  List A = L;
  for (moveFront(A); A->cursor; moveNext(L))
  {
    fprintf(out, "%ld ", get(A));
  }
}
// copyList()
// Returns a new List representing the same integer
// sequence as L.
List copyList(List L)
{
  Node temp = L->front;
  List A = newList();
  while (temp)
  {
    append(A, temp->data);
    temp = temp->next;
  }
  A->cursor = NULL;
  A->index = 0;
  return A;
}
//concatList()
// Returns a new List which is the concatenation of
// A and B.
List concatList(List A, List B)
{
  List a = A;
  List b = B;
  List C = newList();
  for (moveFront(a); a->cursor; moveNext(a))
  {
    append(C, a->cursor->data);
  }
  for (moveFront(b); b->cursor; moveNext(b))
  {
    append(C, b->cursor->data);
  }
  C->length = a->length + b->length;
  return C;
}
