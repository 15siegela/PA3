/******************************************************************************
# Alec Siegel                                                                 #
# 1744236                                                                     #
# PA3                                                                         #
*******************************************************************************/
//-----------------------------------------------------------------------------
// BigIntegerTest.c
// Test file for BigInt ADT
//-----------------------------------------------------------------------------
#include "BigInteger.h"

int main()
{
    char* string = "111111";
    char* string2 = "111111";
    BigInteger a = stringToBigInteger(string); 
    BigInteger a2 = stringToBigInteger(string2);

    BigInteger suma = newBigInteger();
    //Simple add
    printBigInteger(stdout, a);
    printf("+\n");
    printBigInteger(stdout, a2);
    printf("=\n"); 
    add(suma, a, a2);
    printBigInteger(stdout, suma);
    printf("\n______________________\n");
    //Src1 = src2 add
    printBigInteger(stdout, a);
    printf("-\n");
    printBigInteger(stdout, a2);
    printf("=\n"); 
    subtract(suma, a, a2);
    printBigInteger(stdout, suma);
    printf("\n______________________\n");
    printBigInteger(stdout, a);
    printf("*\n");
    printBigInteger(stdout, a);
    printf("=\n"); 
    //add(a, a, a);
    multiply(suma, a, a);
    printBigInteger(stdout, suma);
    printf("\n______________________\n");
    printBigInteger(stdout, a2);
    printf("*\n");
    printBigInteger(stdout, a);
    printf("=\n"); 
    //add(a2, a, a);
    multiply(suma, a, a2);
    printBigInteger(stdout, suma);
    BigInteger tempA = newBigInteger();
    BigInteger tempB = newBigInteger();
    add(tempA, a, a);
    add(tempA, tempA, a);
    add(tempB, a2, a2);
    subtract(suma, tempA, tempB);
    printBigInteger(stdout, suma);
    printBigInteger(stdout, a);
    printf("\n______________________\n");
    //dest = src1 add
    printBigInteger(stdout, a);
    printf("+\n");
    printBigInteger(stdout, a2);
    printf("=\n"); 
    add(a, a, a2);
    printBigInteger(stdout, a);
    printf("\n______________________\n");

    //reset a and a2
    a = stringToBigInteger(string);
    a2 = stringToBigInteger(string2);
    //simple subtract
    
    printBigInteger(stdout, a);
    printf("-\n");
    printBigInteger(stdout, a2);
    printf("=\n");
    subtract(suma, a, a2);
    printBigInteger(stdout, suma);
    printf("\n______________________\n");
    
    //Suma = A-A
    printBigInteger(stdout, a);
    printf("-\n");
    printBigInteger(stdout, a);
    printf("=\n"); 
    subtract(suma, a, a);
    printBigInteger(stdout, suma);
    printf("\n______________________\n");
    
    //dest = src1 * src2
    printBigInteger(stdout, a);
    printf("*\n");
    printBigInteger(stdout, a2);
    printf("=\n"); 
    multiply(suma, a, a2);
    printBigInteger(stdout, suma);

    //scalar test
     printf("Scalar: a = 2*a\n");
    scalar(a,2);
    printBigInteger(stdout, a);

    //Test other functions
    suma = prod(a,a2);
    printf("Prod:\n");
    printBigInteger(stdout, suma);
    printf("Diff:\n");
    suma = diff(a,a2);
    printBigInteger(stdout, suma);
    printf("Sum:\n");
    suma = sum(a,a2);
    printBigInteger(stdout, suma);
    printf("Copy Test:\n");
    suma = copy(a);
    printBigInteger(stdout, suma);

    printf("Compare:\n");
    suma = copy(a2);
    int cmp = compare(a, suma);
    printf("Should be 1:%d\n", cmp);

    printf("Equals:\n");
    suma = copy(a2);
    cmp = equals(suma, a2);
    printf("Should be 1:%d\n", cmp);

    printf("Make Zero:\n");
    suma = copy(a2);
    
    makeZero(suma);
    printf("Should be 0:\n");
    printBigInteger(stdout, suma);

    printf("Sign: a(1):%d, a2(1):%d\n", sign(a), sign(a2));
    negate(a);
    printf("Neg(a):\n");
    printf("Sign: a(-1):%d, a2(1):%d\n", sign(a), sign(a2));
    freeBigInteger(&a);
    freeBigInteger(&a2);
    freeBigInteger(&suma);
    return 0;
}
