/******************************************************************************
# Alec Siegel                                                                 #
# 1744236                                                                     #
# PA3                                                                         #
*******************************************************************************/
//-----------------------------------------------------------------------------
// Arithmetic.c
// Client file for BigInt ADT
//-----------------------------------------------------------------------------
#include "BigInteger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#define M_DATA_LEN 15000

// read each line of input file, then count
int getCount(char *buf, FILE *in)
{
    if (fgets(buf, M_DATA_LEN, in) != NULL)
    {
        int a = atoi(buf);
        return a;
    }
    else
    {
        fprintf(stderr, "There was an error processing the input file");
    }
    return 0;
}

BigInteger createBigInt(char *buf, FILE *in)
{
    if (fgets(buf, M_DATA_LEN, in) != NULL)
    {
        BigInteger a = stringToBigInteger(buf);
        return a;
    }
    else
    {
        fprintf(stderr, "There was an error processing the input file");
    }
}

int main(int argc, char **argv)
{
    // Invalid number of arguments
    if (argc != 3)
    {
        fprintf(stderr, "Error: Invalid number or arguments, expected 2, received %d\n", argc - 1);
    }
    char buf[M_DATA_LEN];
    FILE *in, *out;
    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    //failed to open input
    if (in == NULL)
    {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    //failed to open output
    if (out == NULL)
    {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    BigInteger res = newBigInteger();
    int digitsA = getCount(buf, in);
    char aBuf[digitsA+1];
    BigInteger A = createBigInt(aBuf, in);
    printBigInteger(out, A);
    int digitsB = getCount(buf, in);
    char bBuf[digitsB+1];
    BigInteger B = createBigInt(bBuf, in);
    printBigInteger(out, B);
    add(res, A, B);
    printBigInteger(out, res);
    subtract(res, A, B);
    printBigInteger(out, res);
    subtract(res, A, A);
    printBigInteger(out, res);
    BigInteger tempA = copy(A);
    BigInteger tempB = copy(B);
    scalar(tempA, 3);
    scalar(tempB, 2);
   
    subtract(res, tempA, tempB);
    printBigInteger(out, res);
    
    multiply(res, A, B);
    printBigInteger(out, res);
    
    
    multiply(tempA, A, A);
    printBigInteger(out, tempA);
    multiply(tempB, B, B);
    printBigInteger(out, tempB);
    
    multiply(tempA, tempA, tempA);
    scalar(tempA, 9);
    
    multiply(tempB, tempB, tempB);
    multiply(tempB, tempB, B);
    scalar(tempB, 16);
    
    add(res, tempA, tempB);
    printBigInteger(out, res);

    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&tempA);
    freeBigInteger(&tempB);
    freeBigInteger(&res);
}