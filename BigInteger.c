/******************************************************************************
# Alec Siegel                                                                 #
# 1744236                                                                     #
# PA3                                                                         #
*******************************************************************************/
//-----------------------------------------------------------------------------
// BigInteger.c
// Implementation file for BigInt ADT
//-----------------------------------------------------------------------------
#include "BigInteger.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
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

void removeLeadZeros(BigInteger A)
{
    if(A->mag == NULL || A == NULL)
    {
        return;
    }
    while (index(A->mag) > -1)
    {
        long val = front(A->mag);
        if (val == 0)
        {
            deleteFront(A->mag);
        }
        else
        {
            return;
        }
    }
    if(length(A->mag) == 0)
    {
        A->sign = 0;
    }
}
void addPlaces(BigInteger A, int shift)
{ 
    List L = A->mag;
    moveFront(L);
    while(shift >= POWER)
    {
        append(L, 0);
        shift-=POWER;
    }
    // if(index(L) == 0 && shift >0)
    // {
    //     long int val = get(L);
    //     prepend(L, val/(pow(10, POWER-shift)));
    //     moveFront(L);
    //     moveNext(L);
    //     while(index(L) > -1)
    //     {
    //         long val = get(L);
    //         while(val == 0) //get last non zero entry
    //         {
    //             moveNext(L);
    //             if(index(L) != -1)
    //             {
    //                 val = get(L);
    //             }
    //             else
    //             {return;}
                    
                
                  
    //         }
    //         set(L, val% (int)pow(10, POWER-shift));
    //         set(L, get(L) * pow(10, shift));
    //         moveNext(L);
    //         if(index(L) == -1)
    //         {
    //             break;
    //         }
    //         val = get(L);
    //         movePrev(L);
    //         set(L, get(L) + val/(pow(10, POWER-shift)));
    //         moveNext(L);
    //     }
    // }
   
}
void normalize(BigInteger A)
{   List L = A->mag;
    moveBack(L);
    long carry = 0;
    while (index(L) > 0)
    {
        if(carry) //if carry != 0
        {
            set(L, get(L) + carry); //apply carry
        }     
        carry = get(L)/BASE;
        if(carry)
        {
            set(L, get(L) - (carry*BASE));
        }
        movePrev(L);    
    }
    if(carry)
    {
        moveFront(L);
        set(L, get(L) + carry);
        carry=0;
    }
    if(length(L) == 0)
    {
        return;
    }
    if (get(L) < 0)
    {
        negate(A);
        set(L, (get(L) * -1));
    }    
    while (front(L) >= BASE)
    {   moveFront(L);
        carry = get(L)/BASE;
        set(L, (get(L) - (carry*BASE)));
        prepend(L, carry);
    }
    
}
void scalar(BigInteger A, long num)
{
    moveBack(A->mag);
    while (index(A->mag) > -1)
    {
       set(A->mag, num*get(A->mag));
       movePrev(A->mag);
    }
    normalize(A);
}
int negCheck(BigInteger A)
{
    List L = A->mag;
    moveBack(L);
    while(index(L) > -1)
    {
        if(get(L) <= 0)
        {
            movePrev(L);
        }
        else
        {
            return -1;   
        }
        
    } 
    scalar(A, -1);
    negate(A); 
    return 1;
}

void negNormalize(BigInteger A)
{
    List L = A->mag;
    if (A == NULL || L == NULL)
    {
        return;
    }
    if (negCheck(A) == -1)
    {
        moveBack(L);
        long carry = 0;
        while(index(L) > -1)
        {
            if(carry) //if carry != 0
            {
                set(L, get(L) + carry); //apply carry
            }  
            int val = get(L);
            if(val < 0)
            { 
                carry = -1;
                set(L, val + 1*BASE);
                movePrev(L);
                continue;
            }
            movePrev(L);
            carry = 0;
        }
        if(carry)
        {
            negate(A);
        }
    }
    removeLeadZeros(A);
}

void operate(BigInteger S, BigInteger C, BigInteger D, int op)
{

    if (sign(C) == 0 || sign(D) == 0) //zero check
    {
        if (sign(C) != 0)
        {

            S = copy(C);
            return;
        }
        else
        {
            S = copy(D);
            return;
        }
    }
    BigInteger A = copy(C);
    BigInteger B = copy(D);
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
                prepend(S->mag, A->sign*get(A->mag));
                movePrev(A->mag);
            }
            break;
        }
        if (index(A->mag) == -1)
        {
            while (index(B->mag) > -1)
            {
                prepend(S->mag, B->sign* op* get(B->mag));
                movePrev(B->mag);
            }
            break;
        }
        prepend(S->mag, ((A->sign * get(A->mag)) + (B->sign * op* get(B->mag))));
        movePrev(A->mag);
        movePrev(B->mag);
    }
    removeLeadZeros(S);
    freeBigInteger(&A);
    freeBigInteger(&B);
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
BigInteger MakeBigInteger(long init)
{
    BigInteger B = malloc(sizeof(BigIntegerObj));
    B->mag = newList();
    append(B->mag, init);
    B->sign = 1;
    normalize(B);
    return B;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger *pN)
{
    BigInteger a = *pN;
    if (*pN)
    {
        if (a->mag)
        {
            freeList(&(a->mag));
        }
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
    removeLeadZeros(A);
    removeLeadZeros(B);
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
    if (length(A->mag) > length(B->mag))
    {
        return 1;
    }
    if (length(A->mag) < length(B->mag))
    {
        return -1;
    }
    moveFront(A->mag);
    moveFront(B->mag);
    while (index(A->mag) != -1)
    {
        if ((get(A->mag) == get(B->mag)))
        {
            moveNext(A->mag);
            moveNext(B->mag);
        }
        else if (get(A->mag) > get(B->mag))
        {
            return 1;
        }
        else if (get(A->mag) < get(B->mag))
        {
            return -1;
        }
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
    while(uS[0] == '0')
    {
        strcpy(uS, uS+1);
    }
    sLen = strlen(uS);
    long ret;
    int index = sLen;
    if(uS[sLen-1] == '\n')
    {
        printf("");
        index--;
    }
    if (sLen <= POWER)
    {
        ret = strtol(uS, NULL, 10);
        prepend(temp->mag, ret);
        removeLeadZeros(temp);
        return temp;
    }

    while (index > 0)
    {
        char entry[POWER];
        memcpy(entry, uS + index - POWER, POWER);
        ret = strtol(entry, NULL, 10);
        prepend(temp->mag, ret);
        index -= POWER;
        if (index < POWER && index != 0)
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
    if(N->mag)
    {
        temp->mag = copyList(N->mag);
    }
    temp->sign = sign(N);
    return temp;
}
// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B)
{
    operate(S, A, B, 1);
    negNormalize(S);
    normalize(S);
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
    operate(D, A, B, -1);
    negNormalize(D);
    normalize(D);
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
void multiply(BigInteger P, BigInteger C, BigInteger D)
{ 
    BigInteger A = copy(C);
    BigInteger B = copy(D);
    if (length(P->mag) > 0)
    {
        clear(P->mag);
    }
   
    if (A->sign == 0 || B->sign == 0)
    {
        freeBigInteger(&A);
        freeBigInteger(&B);
        return;
    }
    P->sign = 1;
    List aList =  A->mag;
    List bList = B->mag;
    removeLeadZeros(A);
    removeLeadZeros(B);
    moveBack(aList);
    moveBack(bList);
    while(index(aList) != -1)
    {
        long aVal = get(aList);
        int aShift = length(aList) - (index(aList) + 1);
        while(index(bList) != -1)
        {
            long tempVal = aVal * get(bList);
            int bShift = length(bList) - (index(bList) + 1);
            BigInteger res = MakeBigInteger(tempVal);
            addPlaces(res, (bShift + aShift)*POWER);
            add(P, P, res);
            movePrev(bList);
        }
        movePrev(aList);
        moveBack(bList);
    }
    P->sign = C->sign * D->sign;
    freeBigInteger(&A);
    freeBigInteger(&B);
}
// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B)
{
    BigInteger temp = newBigInteger();
    multiply(temp, A, B);
    return temp;
}
// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE *out, BigInteger N)
{
    //fprintf(stdout, "List: ");
    //printList(stdout, N->mag);
    //fprintf(stdout, "\n");
    if (sign(N) == 0 || front(N->mag) == 0)
    {
        fprintf(out, "0\n");
        return;
    }
    if (sign(N) == -1)
    {
        fprintf(out, "-");
    }
    for (moveFront(N->mag); index(N->mag) > -1; moveNext(N->mag))
    {
        if (index(N->mag) != 0)
        {
            fprintf(out, "%0*ld", POWER-1, get(N->mag));
        }
        else
        {
            fprintf(out, "%ld", get(N->mag));
        }
    }
    fprintf(out, "\n");
}
