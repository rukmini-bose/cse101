// Rukmini Bose 
// rubose 
// PA2

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"
     
int main(){
 int n=10000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H;

   changeEntry(A, 1, 1, 1.1);
   changeEntry(A, 1, 2, 2.2);
   changeEntry(A, 1, 3, 3.3);
   changeEntry(A, 2, 1, 4.4);
   changeEntry(A, 2, 2, 5.5);
   changeEntry(A, 2, 3, 6.6);
   changeEntry(A, 7, 1, 7.7);
   changeEntry(A, 7, 2, 8.8);
   changeEntry(A, 7, 3, 9.9);
   changeEntry(A, 14, 2, 10);
   changeEntry(A, 14, 3, 11);
   changeEntry(A, 14, 5, 12);
   changeEntry(A, 14, 8, 13);

   printf("%d\n", NNZ(A)); // 13
   printMatrix(stdout, A); // 3/3/3/4
   printf("\n");

   changeEntry(A, 2, 2, 0);
   changeEntry(A, 7, 1, 0);
   changeEntry(A, 3, 2, 0); // no-op
   changeEntry(A, 7, 2, 0);
   changeEntry(A, 7, 3, 0);

   printf("%d\n", NNZ(A)); // 9
   printMatrix(stdout, A); // 3/2/4
   printf("\n");

   changeEntry(B, 1, 1, 1.1); // row 1 same as A
   changeEntry(B, 1, 2, 2.2);
   changeEntry(B, 1, 3, 3.3);
   changeEntry(B, 1, 4, 0); // no-op
   changeEntry(B, 2, 2, 4.4); // row 2 no overlap w/ A
   changeEntry(B, 2, 3, 5.5);
   changeEntry(B, 2, 4, 5.5);
   changeEntry(B, 2, 5, 6.6);
   changeEntry(B, 2, 6, 7.7);
   changeEntry(B, 2, 4, 0);
   changeEntry(B, 3, 50, 8.8);
   changeEntry(B, 3, 100, 9.9);

   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");
   
   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   return EXIT_SUCCESS;

}