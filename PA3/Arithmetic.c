// Rukmini Bose
// rubose
// PA3

#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"

#define MAX_LENGTH 20000

int main(int argc, char** argv) {
if (argc != 3) {
fprintf(stderr, "Usage: Arithmetic <input file> <output file>\n");
exit(1);
}

FILE *in = fopen(argv[1], "r"),
  *out = fopen(argv[2], "w");
if (in == NULL) {
fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
exit(1);
}
if (out == NULL) {
fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
exit(1);
}

char line[MAX_LENGTH];

fgets(line, MAX_LENGTH, in); // aLen, bytes
int aLen;
sscanf(line, "%d\n", &aLen); // aLen
char* aDat = calloc(aLen + 3, sizeof(char)); // sign, newline, null
fgets(aDat, MAX_LENGTH, in); // aDat
if (aDat[0] == '+' || aDat[0] == '-') {
aDat[aLen + 1] = '\0';
} else {
aDat[aLen] = '\0';
}
BigInteger A = stringToBigInteger(aDat);
free(aDat);

fgets(line, MAX_LENGTH, in); // bLen, bytes
int bLen;
sscanf(line, "%d\n", &bLen); // bLen
char* bDat = calloc(bLen + 3, sizeof(char)); // sign, newline, null
fgets(bDat, MAX_LENGTH, in); // bDat
if (bDat[0] == '+' || bDat[0] == '-') {
bDat[bLen + 1] = '\0';
} else {
bDat[bLen] = '\0';
}
BigInteger B = stringToBigInteger(bDat);
free(bDat);

// A, B
printBigInteger(out, A);
fprintf(out, "\n");
printBigInteger(out, B);
fprintf(out, "\n");

// A+B
BigInteger summation = sum(A, B);
printBigInteger(out, summation);
fprintf(out, "\n");

// A-B 
BigInteger difference1 = diff(A,B);
printBigInteger(out, difference1);
fprintf(out, "\n");

// A-A = 0 
BigInteger difference2 = diff(A,A);
printBigInteger(out, difference2);
fprintf(out, "\n");

//3A-2B = -14928815061

BigInteger three = stringToBigInteger("3");
BigInteger two = stringToBigInteger("2");

BigInteger combo1 = prod(three, A);
BigInteger combo2 = prod(two,B);
BigInteger answer1 = diff(combo1, combo2);
printBigInteger(out, answer1);
fprintf(out, "\n");

// AB = -304146513730276293
BigInteger multiplication1 = prod(A,B);
printBigInteger(out, multiplication1);
fprintf(out, "\n");

// A*A 
BigInteger multiplication2 = prod(A,A);
printBigInteger(out, multiplication2);
fprintf(out, "\n");

// B*B 
BigInteger multiplication3 = prod(B,B);
printBigInteger(out, multiplication3);
fprintf(out, "\n");

// 9(A^4) + 16(B^5)
BigInteger nine = stringToBigInteger("9");
BigInteger sixteen = stringToBigInteger("16");
BigInteger A2 = prod(A,A);
BigInteger A4 = prod(A2, A2);

/* fprintf(out,"A4 product: ");
printBigInteger(out, A4);
fprintf(out, "\n"); */


BigInteger B2 = prod(B,B);
BigInteger B4 = prod(B2,B2);
BigInteger B5 = prod(B,B4);

/* fprintf(out,"B5 product: ");
printBigInteger(out, B5);
fprintf(out, "\n"); */

BigInteger combo3 = prod(nine,A4);
BigInteger combo4 = prod(sixteen,B5);
BigInteger sum1 = sum(combo3, combo4);
printBigInteger(out, sum1);
fprintf(out, "\n");

freeBigInteger(&A);
freeBigInteger(&B);
freeBigInteger(&summation);
freeBigInteger(&difference1);
freeBigInteger(&difference2);
freeBigInteger(&combo1);
freeBigInteger(&combo2); 
freeBigInteger(&answer1);
freeBigInteger(&multiplication1);
freeBigInteger(&multiplication2);
freeBigInteger(&multiplication3);
freeBigInteger(&combo3);
freeBigInteger(&combo4);
freeBigInteger(&sum1);
freeBigInteger(&three);
freeBigInteger(&two);
freeBigInteger(&nine);
freeBigInteger(&sixteen);
freeBigInteger(&A4);
freeBigInteger(&B5);
freeBigInteger(&A2);
freeBigInteger(&B2);
freeBigInteger(&B4);

fclose(out);
fclose(in);
}
