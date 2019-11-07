/******************************************************************************
# Alec Siegel                                                                 #
# 1744236                                                                     #
# PA3                                                                         #
*******************************************************************************/
//-----------------------------------------------------------------------------
// Biginteger.c
// Implementation file for BigInt ADT
//-----------------------------------------------------------------------------
#include "BigInteger.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define BASE 1000000000
#define POWER 9

// structs --------------------------------------------------------------------
// private BigIntegerObj type
typedef struct BigIntegerObj
{
  List mag;
  int sign;
} BigIntegerObj;
//Helper Functions
void normalize(BigInteger);
// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger()
{
    BigInteger B = malloc(sizeof(BigIntegerObj));
    B->mag = newList();
    B->sign = 0;
    return B;
}
// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN)
{
    if (*pN)
    {
        freeList((*pN)->mag);
        free(*pN);
        *pN = NULL; 
    }
}
// Access functions -----------------------------------------------------------
// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N)
{
   return N->sign;
}
// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B)
{
    if(sign(A) > sign(B))
    {
        return 1;
    }
    if(sign(A) < sign(B))
    {
        return -1;
    }
    if((sign(A) == sign(B)) == 0)
    {
        return 0;
    }
}
// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B)
{
    if ( A->sign != B->sign)
    {
        return 0;
    }
    if(length(A->mag) != length(B->mag))
    {
        return 0;
    }
    if(A->sign != B->sign)
    {
        return 0;
    }
   return listEquals(A->mag, B->mag);
}
// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N)
{
    clear(N->mag);
    N->sign = 0;
}
// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N)
{
    N->sign *= -1;
}
// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s)
{
    if(!s)
    {
        fprintf(stderr, "BigInteger Error: calling stringToBigInteger on null string");
        exit(EXIT_FAILURE);
    }
    BigInteger temp = newBigInteger();
    
    int sLen = strlen(s);
    //printf("String(sign): %s\n", s);
    char* uS[sLen]; 
    if(s[0] == '-')
    {
        temp->sign = -1;
        strcpy(uS, s + 1);
    }
    else if(s[0] == '+')
    {
        temp->sign = 1;
        strcpy(uS, s + 1);
    }
    else if(isdigit(s[0]))
    {
        temp->sign = 1;
        strcpy(uS, s);
    }
    else
    { 
        fprintf(stderr, "BigInteger Error: calling stringToBigInteger on invalid string");
        exit(EXIT_FAILURE);
    }
    //printf("String(no sign): %s\n", uS);
    //printf("Sign : %d\n", temp->sign);
    sLen = strlen(uS);
    int rem = sLen;
    long ret;
    char * ptr;
    char entry[POWER + 1];
    if(sLen < POWER)
    {
        ret = strtol(uS, &ptr, 10);
        append(temp->mag, ret);
        return temp;
    }
    int loc = 0;
    while (loc < sLen)
    {   
        strncpy(entry, uS[loc], POWER);
        entry[POWER] = '\n';
        ret = strtol(entry, &ptr, 10);
        append(temp->mag, ret);
        loc += POWER;
    }

    printList(stdout, temp->mag);
    return temp;
}
// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N)
{
    BigInteger temp = newBigInteger();
    temp->mag = copyList(N);
    temp->sign = N->sign;
}
// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B)
{
    moveFront(A->mag);
    moveFront(B->mag);
    clear(S);
    while(index(A->mag) > -1 || index(A->mag) > -1)
    {
         if (index(B->mag) == -1)
            {
                while (index(A->mag) > -1)
                {
                    append(S->mag, get(A->mag));
                    moveNext(A->mag);
                }
                continue;
            }
            if (index(A->mag) == -1)
            {
                while (index(B->mag) > -1)
                {
                    append(S->mag, get(B->mag));
                    moveNext(B->mag);
                }
                continue;
            }
        append(S,  (get(A->mag))  +  (get(B->mag)));
        moveNext(A->mag);
        moveNext(B->mag);
    }
}
// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B)
{
    BigInteger temp = newBigInteger();
    add(temp, A, B);
    return temp;
}
// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B)
{
    moveFront(A->mag);
    moveFront(B->mag);
    clear(D);
    while(index(A->mag) > -1 || index(A->mag) > -1)
    {
         if (index(B->mag) == -1)
            {
                while (index(A->mag) > -1)
                {
                    append(D->mag, get(A->mag));
                    moveNext(A->mag);
                }
                continue;
            }
            if (index(A->mag) == -1)
            {
                while (index(B->mag) > -1)
                {
                    append(D->mag, (-1 *get(B->mag)));
                    moveNext(B->mag);
                }
                continue;
            }
        append(D,  (get(A->mag)  -  get(B->mag)));
        moveNext(A->mag);
        moveNext(B->mag);
    }
}
// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B)
{

}
// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B);
// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B);
// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N);



