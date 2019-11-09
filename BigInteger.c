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
void normalize(BigInteger A)
{
    List L = A->mag;
    if (length(L) == 0)
    {
        return;
    }
    moveBack(L);
    if(index(L) == -1)
    {
        A->sign = 0;
        return;
    }
    int eq = 1;
    if(length(L))
    {
        for(moveFront(L); index(L) != -1; moveNext(L))
        {
            if (get(L) == 0)
            {
                eq = 0;
                break;
            }
        }
        if (!eq)
        {
            clear(L);
            A->sign = 0;
            return;
        }
    }
    while (index(L) > 0)
    {
        if (get(L) < 0)
        {
            set(L, BASE + get(L));
            movePrev(L);
            set(L, get(L) - 1);
        }
        movePrev(L);
    }
    moveBack(L);
    while (index(L) > 0)
    {
        if (get(L) >= BASE)
        {
            set(L, get(L) - BASE);
            movePrev(L);
            set(L, get(L) + 1);
        }
        movePrev(L);
    }
    if(index(L) == 0)
    {
        if (get(L) < 0)
        {
            negate(A);
            set(L, (get(L)*-1));
        }
    }

}
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
void freeBigInteger(BigInteger *pN)
{
    BigInteger a = *pN;
    if (*pN)
    {
        freeList(&(a->mag));
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
    if (sign(A) > sign(B))
    {
        return 1;
    }
    if (sign(A) < sign(B))
    {
        return -1;
    }
    if ((sign(A) == sign(B)) == 0)
    {
        return 0;
    }
    return 0;
}
// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B)
{
    if (A->sign != B->sign)
    {
        return 0;
    }
    if (length(A->mag) != length(B->mag))
    {
        return 0;
    }
    if (A->sign != B->sign)
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
    N->sign = sign(N) * -1;
}
// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char *s)
{
    if (!s)
    {
        fprintf(stderr, "BigInteger Error: calling stringToBigInteger on null string");
        exit(EXIT_FAILURE);
    }
    BigInteger temp = newBigInteger();
    int sLen = strlen(s);
    char uS[sLen];
    if (s[0] == '-')
    {
        temp->sign = -1;
        strcpy(uS, s + 1);
    }
    else if (s[0] == '+')
    {
        temp->sign = 1;
        strcpy(uS, s + 1);
    }
    else if (isdigit(s[0]))
    {
        temp->sign = 1;
        strcpy(uS, s);
    }
    else
    {
        fprintf(stderr, "BigInteger Error: calling stringToBigInteger on invalid string");
        exit(EXIT_FAILURE);
    }
    sLen = strlen(uS);
    long ret;
    int index = sLen;
    if(sLen <= POWER)
    {
        char entry[sLen];
        memcpy(entry, uS, sLen);
        ret = strtol(entry, NULL, 10);
        prepend(temp->mag, ret);
        return temp;
    }
   
    while (index > 0)
    {
        char entry[POWER - 1];
        memcpy(entry, uS + index - POWER, POWER);
        ret = strtol(entry, NULL, 10);
        prepend(temp->mag, ret);
        index -= POWER;
        if (index < POWER)
        {
            char entry2[index];
            memcpy(entry2, uS, index);
            ret = strtol(entry2, NULL, 10);
            prepend(temp->mag, ret);
            break;
        }
    }
    return temp;
}
// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N)
{
    BigInteger temp = newBigInteger();
    freeList(&(temp->mag));
    temp->mag = copyList(N->mag);
    temp->sign = N->sign;
    return temp;
}
// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B)
{
    int aBsame = 0;
    int srcDestSame = 0;
    if(sign(A) == 0 || sign(B) == 0) //zero check
    {
        if (sign(A) != 0)
        {

            S = copy(A);
            return;
        }
        else
        {
            S = copy(B);
            return;
        }  
    }
    if (A == B) //check if A and B are the same object
    {
        aBsame = 1;
    }
    if (S == A) //create new big int if required
    {
        S = newBigInteger();
        srcDestSame = 1;
    }
    else if(S == B)
    {
        S = newBigInteger();
        srcDestSame = -1;
    }
    if (length(S->mag) > 0)
    {
        clear(S->mag);
    }
    S->sign = 1;
    moveBack(A->mag);
    moveBack(B->mag);
    while (index(A->mag) > -1 || index(B->mag) > -1)
    {
        if (index(B->mag) == -1)
        {
            while (index(A->mag) > -1)
            {
                prepend(S->mag, get(A->mag));
                movePrev(A->mag);
            }
            break;
        }
        if (index(A->mag) == -1)
        {
            while (index(B->mag) > -1)
            {
                prepend(S->mag, get(B->mag));
                movePrev(B->mag);
            }
            break;
        }
        prepend(S->mag, (get(A->mag) + get(B->mag)));
        movePrev(A->mag);
        if (!aBsame)
        {
            movePrev(B->mag);
        }
    }
    normalize(S);
   
    if (srcDestSame) //handle dest = src
    {   
        if (srcDestSame > 0)
        {
            freeBigInteger(&A);
            A = copy(S);
        }
        else
        {
           freeBigInteger(&B);
           B = copy(S);
        }      
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
    int same = 0;
    int srcDestSame = 0;
    if(sign(A) == 0 || sign(B) == 0) //zero check
    {
        if (sign(A) != 0)
        {
            D = copy(A);
            return;
        }
        else
        {
            D = copy(B);
            return;
        }  
    }
    if (A == B) //src1 = src2
    {
        same = 1;
    }

    if (D == A) //Dest = src1
    {
        D = newBigInteger();
        srcDestSame = 1;
    }
    else if(D == B) //Dest = src2
    {
        D = newBigInteger();
        srcDestSame = -1;
    }
    if (length(D->mag) > 0)
    {
        clear(D->mag);
    }
    moveBack(A->mag);
    moveBack(B->mag);
    while (index(A->mag) > -1 || index(A->mag) > -1)
    {
        if (index(B->mag) == -1)
        {
            while (index(A->mag) > -1)
            {
                prepend(D->mag, get(A->mag));
                movePrev(A->mag);
            }
            continue;
        }
        if (index(A->mag) == -1)
        {
            while (index(B->mag) > -1)
            {
                prepend(D->mag, (-1 * get(B->mag)));
                movePrev(B->mag);
            }
            continue;
        }
        prepend(D->mag, (get(A->mag) - get(B->mag)));
        movePrev(A->mag);
        if (!same)
        {
            movePrev(B->mag);
        }
    }
    normalize(D);
    if (srcDestSame) //handle dest = src
    {
        if (srcDestSame > 0)
        {
            freeBigInteger(&A);
            A = copy(D);
        }
        else
        {
            freeBigInteger(&B);
            B = copy(D);
        }      
    }
}
// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B)
{
    BigInteger temp = newBigInteger();
    subtract(temp, A, B);
    return temp;
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
void printBigInteger(FILE *out, BigInteger N)
{
    if(sign(N) == 0)
    {
        fprintf(out, "0");
        return;
    }
    for (moveFront(N->mag); index(N->mag) > -1; moveNext(N->mag))
    {
        if (index(N->mag) != 0)
        {
            fprintf(out, "%0*ld ", POWER, get(N->mag));
        }
        else
        {
            fprintf(out, "%ld ", get(N->mag));
        } 
    }
    
    fprintf(out, "\n");
}
