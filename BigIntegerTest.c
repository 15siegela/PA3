#include "BigInteger.h"

int main()
{
    char* string = "15000000000";
    char* string2 = "10000";
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
    printf("+\n");
    printBigInteger(stdout, a);
    printf("=\n"); 
    add(suma, a, a);
    printBigInteger(stdout, suma);
    printf("\n______________________\n");
    printBigInteger(stdout, a);
    printf("+\n");
    printBigInteger(stdout, a);
    printf("=\n"); 
    add(a, a, a);
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
    
    
    
    //Src1 = src2 sub
    printBigInteger(stdout, a);
    printf("-\n");
    printBigInteger(stdout, a);
    printf("=\n"); 
    subtract(suma, a, a);
    printBigInteger(stdout, suma);
    printf("\n______________________\n");
    
    freeBigInteger(&a);
    freeBigInteger(&a2);
    freeBigInteger(&suma);
    return 0;
}