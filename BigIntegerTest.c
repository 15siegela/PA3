#include "BigInteger.h"

int main()
{
    char* string = "-9400";
    char* string2 = "-4000";
    BigInteger a = stringToBigInteger(string);
    BigInteger a2 = stringToBigInteger(string2);

    BigInteger suma = newBigInteger();
   
    //Simple add
    printBigInteger(stdout, a);
    printf("+\n");
    printBigInteger(stdout, a2);
    printf("= "); 
    add(suma, a, a2);
    printBigInteger(stdout, suma);
    printf("\n______________________\n");
    //Src1 = src2 add
    printBigInteger(stdout, a);
    printf("+\n");
    printBigInteger(stdout, a);
    printf("= "); 
    add(suma, a, a);
    printBigInteger(stdout, suma);
    printf("\n______________________\n");
    //dest = src1 add
    printBigInteger(stdout, a);
    printf("+\n");
    printBigInteger(stdout, a2);
    printf("= "); 
    add(a, a, a2);
    printBigInteger(stdout, a);
    printf("\n______________________\n");

    a = stringToBigInteger(string);
    a2 = stringToBigInteger(string2);

    //simple subtract
    subtract(suma, a, a2);
    printBigInteger(stdout, a);
    printf("-\n");
    printBigInteger(stdout, a2);
    printf("= ");
    printBigInteger(stdout, suma);
    printf("\n______________________\n");
    //Src1 = src2 sub
    printBigInteger(stdout, a);
    printf("-\n");
    printBigInteger(stdout, a);
    printf("= "); 
    subtract(suma, a, a);
    printBigInteger(stdout, suma);
    printf("\n______________________\n");
    
    freeBigInteger(&a);
    freeBigInteger(&a2);
    freeBigInteger(&suma);
    return 0;
}