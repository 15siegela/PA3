#include "BigInteger.h"

int main()
{
    char * string = "+12345";
    stringToBigInteger(string);
    char * nstring = "-12345";
    stringToBigInteger(nstring);
     char * wstring = "12345";
    stringToBigInteger(wstring);
}