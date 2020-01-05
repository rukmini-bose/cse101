// Rukmini Bose
// rubose
// PA3

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "BigInteger.h"

#define POWER 9
#define BASE 1000000000

size_t
     strlen(const char *s);

// Exported type -------------------------------------------------------------
// BigInteger reference type
typedef struct BigIntegerObj {
    int sign;
    List nnl;  
} BigIntegerObj;


// Constructors-Destructors ---------------------------------------------------


// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
    BigInteger bi;
    bi = malloc(sizeof(BigIntegerObj));
    bi -> sign = 0;
    bi-> nnl = newList(); 
    return bi;
}


// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
    if(pN != NULL && *pN != NULL){
        BigInteger A = *pN; 
        freeList(&A->nnl);
        free(*pN);
        *pN = NULL;
    }
}


// Access functions -----------------------------------------------------------


// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N){
    if(N == NULL){
        fprintf(stderr, "ERROR: cannot call sign() on NULL BigInteger");
        exit(EXIT_FAILURE); 
    } 
    return N->sign;
}
// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
    if (A == B){
     return 0;
    }
    if(sign(A) < sign(B)){
        return -1;
    } else if(sign(A) > sign(B)){
        return 1;
    } else{

        if(length(A->nnl) < length(B->nnl)){
            if(sign(A) == -1){
                return 1;
            } else{
                return -1;
            }
        } else if(length(A->nnl) > length(B->nnl)){
            if(sign(A) == -1){
                return -1;
            } else{
                return 1; 
            }
        } else {

            moveFront(A->nnl);
            moveFront(B->nnl);
            while(index(A->nnl) != -1 && index(B->nnl) != -1){
                long i = get(A->nnl);
                long j = get(B->nnl);
                if(i < j){
                    if(sign(A) == -1){
                        return 1;
                    } else{
                        return -1;
                    }
                } else if(j < i){
                    if(sign(A) == -1){
                        return -1;
                    } else{
                        return 1;
                    }
                } else{
                    moveNext(A->nnl);
                    moveNext(B->nnl);
                }

            } 
            return 0;
        }
    }
}


// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
    if(compare(A,B) == 0){
        return 1;
    } else{
        return 0;
    }
}

// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
    if(N == NULL){
        fprintf(stderr, "ERROR: cannot call makeZero() on NULL BigInteger");
        exit(EXIT_FAILURE);
    } else{
        clear(N->nnl);
        N->sign = 0;

    }
}


// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){
    if(N == NULL || N->nnl == NULL){
        fprintf(stderr, "ERROR: cannot call negate()on NULL BigInteger");
        exit(EXIT_FAILURE);
    } else{ 
        N->sign = N->sign * -1;

    }
}

// BigInteger Arithmetic operations -----------------------------------------------


// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.


BigInteger stringToBigInteger(char* s){
    if(s == NULL){
        fprintf(stderr,"ERROR: cannot call stringToBigInteger() on an empty or NULL string array");
        exit(EXIT_FAILURE);
    } else{
        int len = strlen(s);
        int start = 0;
        BigInteger finalBig = newBigInteger();
        if(s[0] == '-'){
            finalBig->sign = -1;
            start = 1;
        } else {
            if(s[0] == '+') {
                start = 1;
            }
            finalBig->sign = 1;
        }
        moveBack(finalBig->nnl);
        long cur;
        char digits[POWER + 1];
        digits[POWER] = '\0';
        int i;

        for(i = len-1; i >= start; i -= POWER) {
            int j = (i - POWER + 1);
            if (j < start) {
                break;
            }
            for (int a = j; a <= i; a++) {
                digits[a - j] = s[a];
            }
            sscanf(digits, "%ld", &cur);
            prepend(finalBig->nnl, cur);

        }
        if (i >= start) {
            for (int a = start; a <= i; a++) {
                digits[a - start] = s[a];
            }
            digits[i - start + 1] = '\0';
            sscanf(digits, "%ld", &cur);
            prepend(finalBig->nnl, cur);
        }
        while (length(finalBig->nnl) > 0 && front(finalBig->nnl) == 0) {
            deleteFront(finalBig->nnl);
        }
        if (length(finalBig->nnl) == 0) {
            finalBig->sign = 0;
        }
        return finalBig;
    }
}

void normalizeSP(List C){
    moveBack(C);
    int count = 0;
    long remainder = 0;
    while(index(C) != -1){
        long number = get(C) + count;
        count = number / BASE ; 
        remainder = number % BASE;
        set(C, remainder);
        movePrev(C);
    }
    if(count != 0){
        prepend(C,count);
    }
}

List sumHelper(List A, List B) {
    moveBack(A);
    moveBack(B);

    long i; 
    long j; 
    long k;
    long copy;

    List C = newList();

    while(index(A) != -1 && index(B) != -1){
        i = get(A);
        j = get(B);
        k = i + j;
        
        prepend(C, k);

        movePrev(A); 
        movePrev(B);
    }  

    while(index(A) != -1){
        copy = get(A);
        prepend(C, copy);
        movePrev(A);
    }
    
    while(index(B) != -1){
        copy = get(B);
        prepend(C, copy);
        movePrev(B);
    }

    normalizeSP(C);
    return C;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
    if(N == NULL){
        fprintf(stderr, "ERROR: cannot call copy() on a NULL BigInteger");
        exit(EXIT_FAILURE);
    }
    BigInteger copied = newBigInteger();
    moveFront(N->nnl);
    while(index(N->nnl) != -1){
        append(copied->nnl, get(N->nnl));
        moveNext(N->nnl);
    }
    copied->sign = N->sign;
    return copied;
}

void normalizeD(List C){
    moveBack(C);
    int carry = 0; 
    long number;
    while(index(C) != -1){
        number = get(C) - carry;
        if(number < 0){
            number = BASE + number;
            carry = 1;
        } else{
            carry = 0;
        }
        set(C, number);
        movePrev(C);
    }

    while(length(C) != 0 && front(C) ==0){
        deleteFront(C);
    }
}


List diffHelper(List A, List B){
    List C = newList();
    moveBack(A);
    moveBack(B);

    while(index(B) != -1){
        
        long i = get(A);
        long j = get(B);
        long k = i-j;

        prepend(C, k);
        movePrev(A);
        movePrev(B);

    }

    long copy;
    while(index(A) != -1){
        copy = get(A);
        prepend(C, copy);
        movePrev(A);
    }
    normalizeD(C);
    return C;
}

List productHelper(List A, List B){
    List C = newList();
    List cumSum = newList();
    moveBack(B);
    moveBack(A);

    while(index(B) != -1){

        moveBack(A);
        while(index(A) != -1){
            long i = get(A); 
            long j = get(B);
            long k = i*j;

          

            prepend(C, k);
            movePrev(A);
        }       
        normalizeSP(C);



        for(int i =0; i < (length(B) - (index(B) + 1)) ; i++){
            append(C, 0);
        }
        
        List oldCumSum = cumSum;
        cumSum = sumHelper(cumSum, C);

        normalizeSP(cumSum);

        movePrev(B);
        freeList(&oldCumSum);
        clear(C);
    } 
    freeList(&C);
    return cumSum;
}
// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "ERROR: cannot call sum() on NULL BigInteger()");
        exit(EXIT_FAILURE);
    } 
    if(A->sign == 0){
        return copy(B);
    } 
    if(B->sign == 0){
        return copy(A);
    } 

    if(A->sign == B->sign){
        BigInteger C = malloc(sizeof(BigIntegerObj));
        C->nnl = sumHelper(A->nnl,B->nnl);
        C->sign = A->sign;
        return C;
    }

    if(A->sign == -1){
        BigInteger C = NULL;
        negate(A);
        int comparison = compare(A,B);
        if(comparison == -1){
            C = malloc(sizeof(BigIntegerObj));
           

            C->nnl = diffHelper(B->nnl,A->nnl);
            C->sign = 1;
            negate(A);
            return C;
        } else if (comparison == 0) {
            negate(A);
            return newBigInteger();
        } else{
            C = malloc(sizeof(BigIntegerObj));
            C->nnl = diffHelper(A->nnl, B->nnl);
            C->sign = -1;
            negate(A);
            return C;
        }
        
    } else { // A->sign == 1 
        BigInteger C = NULL;
        negate(B);
        int comparison = compare(A,B);
        if(comparison == -1){
            C = malloc(sizeof(BigIntegerObj));
            C->nnl = diffHelper(B->nnl,A->nnl);
            C->sign = -1;
            negate(B);
            return C;
        } else if(comparison == 0){
            negate(B);
            return newBigInteger();
        } else {
            C = malloc(sizeof(BigIntegerObj));
            C->nnl = diffHelper(A->nnl,B->nnl);
            C->sign = 1;
            negate(B);
            return C;
        }

    }
}


// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "ERROR: cannot call add() on NULL BigInteger(s)");
        exit(EXIT_FAILURE);
    } else{ 
        BigInteger res = sum(A,B);
        S->sign = res->sign;
        freeList(&(S->nnl));
        S->nnl = res->nnl;
        free(res);
    }
}



// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "ERROR: cannot call diff() NULL BigInteger(s)");
        exit(EXIT_FAILURE);
    }
    int comparison = compare(A, B);
    if(comparison == 0){
        return newBigInteger();
    } 
    
    if(B->sign == 0){
        return copy(A);
    }
    
    BigInteger C = NULL;
    //printf("Comparing A and B: %d\n",compare(A,B));
    if(A->sign == 0){
        C = copy(B);
        negate(C);
        return C;
    }
    if(A->sign == 1 && B->sign == -1){
        C = malloc(sizeof(BigIntegerObj));
        C->nnl = sumHelper(A->nnl, B->nnl);
        C->sign = 1;
        return C;
    } else if(A->sign == -1 && B->sign == 1){
        C = malloc(sizeof(BigIntegerObj));
        C->nnl = sumHelper(A->nnl, B->nnl);
        C->sign = -1; 
        return C; 
    } else if(A->sign == 1 && B->sign == 1){
        if(comparison == -1){
             C = malloc(sizeof(BigIntegerObj));
             C->nnl = diffHelper(B->nnl, A->nnl);
             C->sign = -1;
            return C;
        } else{ 
             C = malloc(sizeof(BigIntegerObj));
             C->nnl = diffHelper(A->nnl, B->nnl);
             C->sign = 1;
             return C;
        }
    } else{
        if(comparison == 1){
             C = malloc(sizeof(BigIntegerObj));
             C->nnl = diffHelper(B->nnl, A->nnl);
             C->sign = 1;
             return C;
        } else{
             C = malloc(sizeof(BigIntegerObj));
             C->nnl = diffHelper(A->nnl, B->nnl);
             C->sign = -1; 
             return C; 
        }
    }
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "ERROR: cannot call subtract() on NULL BigInteger(s)");
        exit(EXIT_FAILURE);
    } else{  
        BigInteger res = diff(A,B);
        D->sign = res->sign;
        freeList(&(D->nnl));
        D->nnl = res->nnl;
        free(res);
    } 

}
// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "ERROR: cannot call multiply() on NULL BigInteger(s)");
        exit(EXIT_FAILURE);
    } else{ 
        BigInteger res = prod(A,B);
        P->sign = res->sign;
        freeList(&(P->nnl));
        P->nnl = res->nnl;
        free(res);
    }
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "ERROR: cannot call prod() NULL BigInteger(s)");
        exit(EXIT_FAILURE);
    }
    if(A->sign== 0 || B->sign == 0){
        return newBigInteger();
    }  

    int aEqualsB = 0;
    if(A==B){
        B = copy(A);
        aEqualsB = 1; 
    }
    BigInteger C = NULL;
    if(A->sign == B->sign){
        C = malloc(sizeof(BigIntegerObj));
        if(A->sign == 1){
            if(length(A->nnl) < length(B->nnl)){
                C->nnl = productHelper(B->nnl, A->nnl);

            } else{
                C->nnl = productHelper(A->nnl, B->nnl);
                
            }
        } else{
            if(length(A->nnl) > length(B->nnl)){
                C->nnl = productHelper(A->nnl, B->nnl);

            } else{
                C->nnl = productHelper(B->nnl, A->nnl);
            }
        }
    C->sign = 1;
    } else{ // signs different
        C = malloc(sizeof(BigIntegerObj));
        if(A->sign == 1){
            if(length(A->nnl) < length(B->nnl)){
               C->nnl = productHelper(B->nnl,A->nnl);
            } else{
                C->nnl = productHelper(A->nnl,B->nnl);
            }
        } else{
            if(length(A->nnl) < length(B->nnl)){
                C->nnl = productHelper(B->nnl,A->nnl);
            } else{
                C->nnl = productHelper(A->nnl, B->nnl);
            }
        }
        C->sign = -1;
    }
    if(aEqualsB == 1){
        freeBigInteger(&B);
    }
    return C;
}
    

// Other operations -----------------------------------------------------------


int get_int_len (long value){
    int l = 1;
    while(value>9){ 
        l++; 
        value/=10; 
    }
  return l;
}
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
    
    if(N->sign == -1){
        fprintf(out, "-");
    } else if (N->sign == 0) {
        fprintf(out, "0\n");
        return;
    }
    moveFront(N->nnl);
    if(index(N->nnl) != -1) {
        fprintf(out,"%ld", get(N->nnl));
        moveNext(N->nnl);        
    }
    while(index(N->nnl) != -1){
        for(int i = 0; i < POWER - get_int_len(get(N->nnl)) ; i++){
            fprintf(out,"0");
        }
        fprintf(out,"%ld", get(N->nnl));
        moveNext(N->nnl);
    }
    fprintf(out,"\n");
}
