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
#define M_DATA_LEN 100

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
    printBigInteger(stdout, A);
    int digitsB = getCount(buf, in);
    char bBuf[digitsB+1];
    BigInteger B = createBigInt(bBuf, in);
    printBigInteger(stdout, B);
    add(res, A, B);
    printBigInteger(stdout, res);
    subtract(res, A, B);
    printBigInteger(stdout, res);
    subtract(res, A, A);
    printBigInteger(stdout, res);
    BigInteger tempA = newBigInteger();
    BigInteger tempB = newBigInteger();
    add(tempA, A, A);
    add(tempA, tempA, A);
    add(tempB, B, B);
    subtract(res, tempA, tempB);
    printBigInteger(stdout, res);
    multiply(res, A, B);
    printBigInteger(stdout, res);
    multiply(res, A, A);
    printBigInteger(stdout, res);
    multiply(res, B, B);
    printBigInteger(stdout, res);
    multiply(tempA, A, A);
    multiply(tempA, tempA, tempA);
    for (int i = 0; i < 8; i++)
    {
        add(tempA, tempA, A);
    }
    multiply(tempB, B, B);
    for (int i = 0; i < 3; i++)
    {
        multiply(tempB, tempB, B);
    }
    add(res, tempA, tempB);
    printBigInteger(stdout, res);
}