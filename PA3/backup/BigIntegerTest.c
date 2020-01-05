// Rukmini Bose
// rubose
// PA3

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "BigInteger.h"


int main(int argc, char* argv[]){

    //BigInteger A = stringToBigInteger("-41085449");
    BigInteger A = stringToBigInteger("-41085449");
    BigInteger B = stringToBigInteger("-41085449");
    BigInteger C = newBigInteger();

    printBigInteger(stdout, A);
    printBigInteger(stdout, B);

    //add(C,A,B);
    //C = sum(A,B);

   C = prod(A,A);

    printBigInteger(stdout,C);
}

