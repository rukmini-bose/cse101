// Rukmini Bose 
// rubose 
// PA2

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main(int argc, char** argv) {
    if (argc != 3) {
      fprintf(stderr, "Usage: Sparse <input file> <output file>\n");
      exit(1);
   }

   FILE* in, *out;


   // Open input and output files
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if (in == NULL) {
      fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if (out == NULL) {
      fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   int n, a, b;
   fscanf(in, "%d %d %d\n", &n, &a, &b);

   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);

   for (int i = 0; i < a; i++) {
      int r, c;
      double v;
      fscanf(in, "%d %d %lf\n", &r, &c, &v);
      changeEntry(A, r, c, v);
   }
   fprintf(out, "A has %d non-zero entries:\n", a);
   printMatrix(out, A);
   fprintf(out, "\n");

   for (int i = 0; i < b; i++) {
      int r, c;
      double v;
      fscanf(in, "%d %d %lf\n", &r, &c, &v);
      changeEntry(B, r, c, v);
   }
   fprintf(out, "B has %d non-zero entries:\n", b);
   printMatrix(out, B);
   fprintf(out, "\n");

    
    Matrix scalarResult = scalarMult(1.5, A);
    fprintf(out, "(1.5) * A =\n");
    printMatrix(out, scalarResult);
    fprintf(out,"\n");

    Matrix sumResult = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, sumResult);
    fprintf(out,"\n");

    Matrix sumResult2 = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, sumResult2);
    fprintf(out,"\n");

    Matrix diffResult = diff(B,A);
    fprintf(out, "B-A =\n");
    printMatrix(out, diffResult);
    fprintf(out,"\n");

    Matrix diffResult2 = diff(A,A);
    fprintf(out, "A-A =\n");
    printMatrix(out, diffResult2);
    fprintf(out,"\n");

    Matrix TResult = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, TResult);
    fprintf(out,"\n");

    Matrix prodResult = product(A,B);
    fprintf(out, "A*B =\n");
    printMatrix(out, prodResult);
    fprintf(out,"\n");

    Matrix prodResult2 = product(B,B);
    fprintf(out, "B*B =\n");
    printMatrix(out, prodResult2);

    freeMatrix(&scalarResult);
    freeMatrix(&sumResult);
    freeMatrix(&sumResult2);
    freeMatrix(&diffResult);
    freeMatrix(&diffResult2);
    freeMatrix(&TResult);
    freeMatrix(&prodResult);
    freeMatrix(&prodResult2);
    freeMatrix(&A);
    freeMatrix(&B);

    fclose(in);
    fclose(out);
}
