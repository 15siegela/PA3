#include "BigInteger.h"

int main()
{
    char * string = "+123456789123456789";
    BigInteger a = stringToBigInteger(string);
    BigInteger suma = newBigInteger();
    add(suma, a, a);
    printBigInteger(stdout, suma);
    subtract(suma, a, a);
    printBigInteger(stdout, suma);
    return 0;
}