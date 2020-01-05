// Rukmini Bose
// rubose
// PA3

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "BigInteger.h"


int main(int argc, char* argv[]){
    BigInteger A = stringToBigInteger("-4108554545449");
    BigInteger B = stringToBigInteger("4395892495945023959459569");
    BigInteger C = stringToBigInteger("0");
    BigInteger D = stringToBigInteger("653656563");
    BigInteger E = stringToBigInteger("-345853");

    BigInteger F = newBigInteger(); 
    BigInteger G = newBigInteger(); 
    BigInteger H = newBigInteger(); 
    BigInteger I = newBigInteger(); 
    BigInteger J = newBigInteger(); 
    BigInteger K = newBigInteger(); 


    add(F,A,B);
    add(G,A,C);
    subtract(H,E,C);
    subtract(I,B,D);
    multiply(J,C,E);
    multiply(K,A,E);

    BigInteger L = newBigInteger();
    negate(E);
    subtract(L,E,A);


    BigInteger M = NULL;
    M = copy(B);


    printBigInteger(stdout,F);
    printBigInteger(stdout,G);
    printBigInteger(stdout,H);
    printBigInteger(stdout,I);
    printBigInteger(stdout,J);
    printBigInteger(stdout,K);
    printBigInteger(stdout,L);
    printBigInteger(stdout,M);

    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&E);
    freeBigInteger(&F);
    freeBigInteger(&G);
    freeBigInteger(&H);
    freeBigInteger(&I);
    freeBigInteger(&J);
    freeBigInteger(&K);
    freeBigInteger(&L);
    freeBigInteger(&M);

}

