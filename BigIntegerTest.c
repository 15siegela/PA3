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
    char* string2 = "-0041085449";
    char* string = "7402779357";
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
    //add(a, a, a);
    multiply(suma, a, a2);
    printBigInteger(stdout, suma);
    BigInteger tempA = newBigInteger();
    BigInteger tempB = newBigInteger();
    add(tempA, a, a);
    add(tempA, tempA, a);
    add(tempB, a2, a2);
    subtract(suma, tempA, tempB);
    printBigInteger(stdout, suma);
    // printBigInteger(stdout, a);
    // printf("\n______________________\n");
    // //dest = src1 add
    // printBigInteger(stdout, a);
    // printf("+\n");
    // printBigInteger(stdout, a2);
    // printf("=\n"); 
    // add(a, a, a2);
    // printBigInteger(stdout, a);
    // printf("\n______________________\n");

    // a = stringToBigInteger(string);
    // a2 = stringToBigInteger(string2);
    // //simple subtract
    
    // printBigInteger(stdout, a);
    // printf("-\n");
    // printBigInteger(stdout, a2);
    // printf("=\n");
    // subtract(suma, a, a2);
    // printBigInteger(stdout, suma);
    // printf("\n______________________\n");
    
    
    
    // //Src1 = src2 sub
    // printBigInteger(stdout, a);
    // printf("-\n");
    // printBigInteger(stdout, a);
    // printf("=\n"); 
    // subtract(suma, a, a);
    // printBigInteger(stdout, suma);
    // printf("\n______________________\n");
    
    // //dest = src1 * src2
    // printBigInteger(stdout, a);
    // printf("*\n");
    // printBigInteger(stdout, a2);
    // printf("=\n"); 
    // multiply(suma, a, a2);
    // printBigInteger(stdout, suma);
    
    freeBigInteger(&a);
    freeBigInteger(&a2);
    freeBigInteger(&suma);
    return 0;
}
