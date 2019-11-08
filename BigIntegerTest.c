#include "BigInteger.h"

int main()
{
    char * string = "+1234567899876543211234567891";
    BigInteger a = stringToBigInteger(string);
    BigInteger b = stringToBigInteger(string);

    BigInteger C = sum(a,b);
    printBigInteger(stdout, C);
    
}