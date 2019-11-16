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
        exit(EXIT_FAILURE);
    }
    return 0;
}
//create a new bigInt from buf
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
        exit(EXIT_FAILURE);
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

    //start program
    BigInteger res = newBigInteger(); //stores result
    int digitsA = getCount(buf, in); //get count of first line
    char aBuf[digitsA+1]; //create properly sized buf
    BigInteger A = createBigInt(aBuf, in); //create bigint A
    printBigInteger(out, A); //print A
    
    int digitsB = getCount(buf, in);//get count of second line
    char bBuf[digitsB+1];//create properly sized buf
    BigInteger B = createBigInt(bBuf, in);//create bigint B
    printBigInteger(out, B);//Print B
    
    //A+B
    add(res, A, B);
    printBigInteger(out, res); //Print A+B
    //A-B
    subtract(res, A, B);
    printBigInteger(out, res);
    //A-A
    subtract(res, A, A);
    printBigInteger(out, res);

    //create copies
    BigInteger tempA = copy(A);
    BigInteger tempB = copy(B);
    
    //3*a -2*B 
    scalar(tempA, 3);
    scalar(tempB, 2);
    subtract(res, tempA, tempB);
    printBigInteger(out, res);
    
    //A*B
    multiply(res, A, B);
    printBigInteger(out, res);
    
    //A*A
    multiply(tempA, A, A);
    printBigInteger(out, tempA);
    //B*B
    multiply(tempB, B, B);
    printBigInteger(out, tempB);
    
    //9*A^4 + 16B^5
    multiply(tempA, tempA, tempA);
    scalar(tempA, 9);
    multiply(tempB, tempB, tempB);
    multiply(tempB, tempB, B);
    scalar(tempB, 16);
    add(res, tempA, tempB);
    printBigInteger(out, res);

    //free memory
    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&tempA);
    freeBigInteger(&tempB);
    freeBigInteger(&res);
    fclose(in);
    fclose(out);
}