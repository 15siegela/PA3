/******************************************************************************
# Alec Siegel                                                                 #
# 1744236                                                                     #
# PA3                                                                         #
*******************************************************************************/

//-----------------------------------------------------------------------------
// List.c
// Test file for List ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"

int main(int argc, char *argv[])
{

   List A = newList();
   List B = newList();
   // initialize Lists A and B
   for (int i = 0; i < 100; i++)
   {
      append(A, i);
      prepend(B, i);
   }
   moveFront(A);
   moveBack(B);
   assert(index(A) == 0);
   assert(index(B) == 99);
   for (int i = 0; i < 100; i++)
   {
      long a = get(A);
      long b = get(B);
      assert(a == b);
      moveNext(A);
      movePrev(B);
   }

   assert(length(A) == length(B));
   for (int i = 0; i < 100; i++)
   {
      moveFront(A);
      moveBack(B);
      long a = get(A);
      long b = get(B);
      assert(a == b);
      deleteFront(A);
      deleteBack(B);
   }
   append(A, 2);
   prepend(A, 1);
   clear(A);
   assert(length(A) == 0);
   append(A, 2);
   prepend(A, 1);
   moveFront(A);
   delete (A);
   moveFront(A);
   delete (A);
   assert(length(A) == 0);

   clear(A);
   clear(B);
   prepend(A, 34);
   prepend(A, 4);
   prepend(A, 354);
   prepend(A, 3674);
   moveBack(A);
   insertBefore(A, 435);
   assert((index(A) == 4));
   prepend(A, 324);
   prepend(A, 33464);
   prepend(A, 3498);
   moveFront(A);
   insertBefore(A, 67);
   assert((index(A) == 1));

   clear(A);
   clear(B);
   append(A, 5);
   prepend(A, 7);
   append(A, 2);
   moveBack(A);
   insertAfter(A, 43);
   deleteBack(A);
   delete (A);
   assert(back(A) == 5);

   clear(A);
   clear(B);
   append(A, 1);
   prepend(A, 2);
   moveFront(A);
   clear(A);
   assert(index(A) == -1 && length(A) == 0);
   
   freeList(&A);
   freeList(&B);
}
