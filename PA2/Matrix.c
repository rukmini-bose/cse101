// Rukmini Bose 
// rubose 
// PA2

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

typedef struct EntryObj{ 
    int column; 
    double data; 
} EntryObj; 

typedef EntryObj* Entry;

typedef struct MatrixObj{ 
    int size; 
    int nonZeroEntries;
    List* rows; 
} MatrixObj;

// --- CONSTRUCTOR / DESTRUCTOR ---
Entry newEntry(int column, double data){
    Entry E;
    E = malloc(sizeof(EntryObj));
    E-> column = column; 
    E-> data = data; 
    return E;
}

void freeListHelper(List list) {
    moveFront(list);
    while (index(list) != -1) {
        Entry e = get(list);
        free(e);
        moveNext(list);
    }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(MatrixObj));
    M-> size = n; 
    M-> nonZeroEntries = 0;
    M->rows = malloc(sizeof(List) * n);
    for(int i = 0; i < n; i++){
        M->rows[i]= newList();
    }
    return M; 
}
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    if(pM != NULL && *pM != NULL){
        Matrix M = *pM;
        for(int i = 0; i < size(M); i++){
            freeListHelper(M->rows[i]);
            freeList(&(M->rows[i]));
        } 
        free(M->rows);
        free(*pM);
        *pM = NULL;
    }
}
// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
    if(M == NULL){
        fprintf(stderr, "ERROR: cannot call size() on NULL matrix");
        exit(EXIT_FAILURE);
    }
    return (M->size); 
}


// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
    if(M == NULL){
        fprintf(stderr, "ERROR: cannot call NNZ() on NULL matrix");
        exit(EXIT_FAILURE);
    }
    return M->nonZeroEntries;
}


// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    if(A == NULL || B == NULL){
        fprintf(stderr, "ERROR: cannot call NNZ() on NULL matrix");
        exit(EXIT_FAILURE);
    } else if(size(A) != size(B)){
        return 0;
    } else if(A->nonZeroEntries != B->nonZeroEntries){
        return 0;
    } else{
        for(int i = 0; i < size(A); i++){
            if (length(A->rows[i]) != length(B->rows[i])) {
                return 0;
            }
            moveFront(A->rows[i]);
            moveFront(B->rows[i]);
            while(index(A->rows[i]) != -1 || index(B->rows[i]) != -1){
                Entry entryA = get(A->rows[i]);
                Entry entryB = get(B->rows[i]);
                if((entryA->column != entryB->column) || (entryA->data != entryB->data)) {
                    return 0;
                } else{
                    moveNext(A->rows[i]);
                    moveNext(B->rows[i]);
                }
            }
        }
        return 1;
    }
}

// Manipulation procedures


// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M){
    if(M == NULL){
        fprintf(stderr, "ERROR: cannot call makeZero() on NULL matrix");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < size(M); i++){
        freeListHelper(M->rows[i]);
        freeList(&(M->rows[i]));
        M->rows[i] = newList();
    }
    M -> nonZeroEntries = 0; 
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if(M == NULL){
        fprintf(stderr, "ERROR: cannot call NNZ() on NULL matrix");
        exit(EXIT_FAILURE);
    } else if(i < 1 || i > size(M) || j < 1 || j > size(M)){
        fprintf(stderr, "ERROR: cannot call changeEntry() on invalid row or column");
        exit(EXIT_FAILURE);
    }

    List row = M-> rows[i-1];
    moveFront(row);
    while (index(row) != -1) {
        Entry E = get(row);
        if(j < E->column){
            if(x != 0){
                insertBefore(row, newEntry(j,x));
                M-> nonZeroEntries++;
            }
            return;
        } else if(j == E->column){
            if(x == 0){
                free(E);
                delete(row);
                M->nonZeroEntries--;
            } else{
                E->data = x;
            }
            return;
        }
        moveNext(row);
    }
    if (x != 0) {
        append(row,newEntry(j,x));
        M-> nonZeroEntries++;        
    }
}


// Matrix Arithmetic operations

List copyList(List A) {
    List copied = newList();
    moveFront(A); 
    while(index(A) != -1){
        Entry E = get(A);
        append(copied,newEntry(E->column, E->data));
        moveNext(A);
    }
    return copied;
}

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    if(A == NULL){
        fprintf(stderr, "ERROR: cannot call copy() on NULL matrix");
        exit(EXIT_FAILURE);
    } 
    Matrix copyMatrix = newMatrix(size(A));
    for(int i = 0; i < size(A) ; i++) {
        freeList(&(copyMatrix->rows[i]));
        copyMatrix-> rows[i] = copyList(A->rows[i]);
    }
    copyMatrix->nonZeroEntries = A->nonZeroEntries;
    return copyMatrix;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    if(A == NULL){
        fprintf(stderr, "ERROR: cannot call transpose()) on NULL matrix");
        exit(EXIT_FAILURE);
    }
    Matrix M = newMatrix(size(A));
    for(int i = 0; i < size(M); i++){
        moveFront(A->rows[i]);
        while(index(A->rows[i]) != -1){
            Entry E = get(A->rows[i]);
            Entry newE = newEntry(i+1,E->data);
            append(M->rows[E->column-1], newE);
            moveNext(A->rows[i]);
        }

    }
    M->nonZeroEntries = A->nonZeroEntries;
    return M; 
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    if(A == NULL){
        fprintf(stderr, "ERROR: cannot call scalarMult() on NULL matrix");
        exit(EXIT_FAILURE);
    }
    Matrix multMatrix = newMatrix(size(A));
    if(x != 0){
        for(int i = 0; i < size(A) ; i++){
            List aList = A->rows[i];
            List multList = newList();
            moveFront(aList);
            while(index(aList) != -1){
                Entry E = get(aList);
                Entry multE = newEntry(E->column, x * E->data);
                append(multList, multE);
                moveNext(aList);
                multMatrix->nonZeroEntries++;
            }
            free(multMatrix->rows[i]);
            multMatrix->rows[i] = multList;
        }
    }
    return multMatrix;
}

List sumHelper(List A, List B){
    List result = newList();
    moveFront(A);
    moveFront(B);

    while(index(A) != -1 && index(B) != -1){
        Entry entryA = get(A);
        Entry entryB = get(B);
        if(entryA->column < entryB->column){
            append(result, newEntry(entryA->column, entryA->data));
            moveNext(A);
        } else if(entryB->column < entryA->column){
            append(result, newEntry(entryB->column, entryB->data));
            moveNext(B);
        } else{
            double sum = entryA->data + entryB->data;
            if(sum != 0){
                append(result, newEntry(entryA->column, sum));
            }
            moveNext(A);
            moveNext(B);
        }
    }
    while(index(A) != -1){
        Entry entryA = get(A);
        append(result, newEntry(entryA->column, entryA->data));
        moveNext(A);
    }
    while(index(B) != -1){
        Entry entryB = get(B);
        append(result, newEntry(entryB->column, entryB->data));
        moveNext(B);
    }
    return result;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "ERROR: cannot call sum() on NULL matrix");
        exit(EXIT_FAILURE);
    } else if(size(A) != size(B)){
        fprintf(stderr, "ERROR: cannot call sum() on matricies of different sizes");
        exit(EXIT_FAILURE);
    } else{ 
        Matrix finalMatrix = newMatrix(size(A));
        for(int i = 0; i < size(A); i++){
            List rowA = A->rows[i];
            List rowB;
            freeList(&(finalMatrix->rows[i]));
            if (A == B) {
                rowB = copyList(B->rows[i]);
                finalMatrix->rows[i] = sumHelper(rowA, rowB);
                finalMatrix->nonZeroEntries += length(finalMatrix->rows[i]);
                freeListHelper(rowB);
                freeList(&rowB);
            } else {
                rowB = B->rows[i];
                finalMatrix->rows[i] = sumHelper(rowA, rowB);
                finalMatrix->nonZeroEntries += length(finalMatrix->rows[i]);                
            }
        }
        return finalMatrix;
    }
}

List diffHelper(List A, List B){
    List result = newList();
    moveFront(A);
    moveFront(B);

    while(index(A) != -1 && index(B) != -1){
        Entry entryA = get(A);
        Entry entryB = get(B);
        if(entryA->column < entryB->column){
            append(result, newEntry(entryA->column, entryA->data));
            moveNext(A);
        } else if(entryB->column < entryA->column){
            append(result, newEntry(entryB->column, -(entryB->data)));
            moveNext(B);
        } else{
            double diff = entryA->data - entryB->data;
            if(diff != 0){
                append(result, newEntry(entryA->column, diff));
            }
            moveNext(A);
            moveNext(B);
        }
    }
    while(index(A) != -1){
        Entry entryA = get(A);
        append(result, newEntry(entryA->column, entryA->data));
        moveNext(A);
    }
    while(index(B) != -1){
        Entry entryB = get(B);
        append(result, newEntry(entryB->column, -(entryB->data)));
        moveNext(B);
    }
    return result;
}
    
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "ERROR: cannot call diff() on NULL matrix");
        exit(EXIT_FAILURE);
    } else if(size(A) != size(B)){
        fprintf(stderr, "ERROR: cannot call sum() on matricies of different sizes");
        exit(EXIT_FAILURE);
    } else{ 
        Matrix finalMatrix = newMatrix(size(A));
        for(int i = 0; i < size(A); i++){
            List rowA = A->rows[i];
            List rowB;
            freeList(&(finalMatrix->rows[i]));
            if (A == B) {
                rowB = copyList(B->rows[i]);
                finalMatrix->rows[i] = diffHelper(rowA, rowB);
                finalMatrix->nonZeroEntries += length(finalMatrix->rows[i]);
                freeListHelper(rowB);
                freeList(&rowB);
            } else {
                rowB = B->rows[i];
                finalMatrix->rows[i] = diffHelper(rowA, rowB);
                finalMatrix->nonZeroEntries += length(finalMatrix->rows[i]);                
            }
        }
        return finalMatrix;
    }
}

double vectorDot(List A, List B){
    double result = 0;
    moveFront(A);
    moveFront(B);
    while(index(A) != -1 && index(B) != -1){
        Entry entryA = get(A);
        Entry entryB = get(B);
        if(entryA->column < entryB->column){
            moveNext(A);
        } else if(entryA->column > entryB->column){
            moveNext(B);
        } else{
            result += (entryA->data * entryB->data);
            moveNext(A);
            moveNext(B);
        }
    }
    return result;
}
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "ERROR: cannot call product() on NULL matrix");
        exit(EXIT_FAILURE);
    } else if(size(A) != size(B)){
        fprintf(stderr, "ERROR: cannot call product() on 2 matricies of different sizes");
        exit(EXIT_FAILURE);
    }
    Matrix finalMatrix = newMatrix(size(A));
    Matrix T = transpose(B);
    for(int i = 0; i < size(A) ; i++){
        for(int j = 0; j < size(A) ; j++){
            double vd = vectorDot(A->rows[i], T->rows[j]);
            if (vd != 0) {
                append(finalMatrix ->rows[i], newEntry( j+1 , vd));
                finalMatrix->nonZeroEntries++;
            }
            
        }
    }
    freeMatrix(&T);
    return finalMatrix;
}
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    for(int i = 0; i < size(M) ; i++) {
        List rowM = M->rows[i];
        if (length(rowM) != 0) {
            fprintf(out,"%d: ", i+1);
            moveFront(rowM);
            while(index(rowM) != -1){
                Entry entryM = get(rowM);            
                fprintf(out, "(%d, %.1f) ", entryM->column, entryM->data);
                moveNext(rowM);
            }
            fprintf(out, "\n");
        }
    }
}
