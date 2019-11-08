#include "BigInteger.h"

int main()
{
    char* string = "+355100";
    char* string2 = "900";
    BigInteger a = stringToBigInteger(string);
    BigInteger a2 = stringToBigInteger(string2);

    BigInteger suma = newBigInteger();
    add(suma, a, a2);
    printBigInteger(stdout, suma);
    subtract(suma, a, a2);
    printBigInteger(stdout, a);
    printf("-\n");
    printBigInteger(stdout, a2);
    printBigInteger(stdout, suma);
    freeBigInteger(&a);
    freeBigInteger(&suma);
    return 0;
}