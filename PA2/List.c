// Rukmini Bose 
// rubose 
// PA2

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj{ 
    void* data; 
    struct NodeObj* previous;
    struct NodeObj* next;
} NodeObj;

typedef NodeObj* Node; 

typedef struct ListObj{
    Node front;  
    Node back;
    Node cursor;  
    int length;
    int index; 

} ListObj; 

// Constructors-Destructors ---------------------------------------------------
List newList(void){
    List L; 
    L = malloc(sizeof(ListObj));
    L->front = NULL;
    L-> back = NULL;
    L-> cursor = NULL; 
    L-> length = 0; 
    L -> index = -1;
    return L;  

} // Creates and returns a new empty List.

Node newNode(void* data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data; 
    N->next = NULL;
    N->previous = NULL;
    return(N);
}
void freeList(List* pL){
    clear(*pL);
    if(pL != NULL && *pL != NULL){
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
       
}// Frees all heap memory associated with *pL, and sets
 // *pL to NULL.

void freeNode(Node* pN){
    if(pN!= NULL && *pN != NULL){
        free(*pN);
        *pN = NULL; 
    }
}
// Access functions -----------------------------------------------------------
int length(List L){
    if(L== NULL){
        fprintf(stderr, "ERROR: cannot call length() on a NULL list\n");
        exit(EXIT_FAILURE);
    } else if(L-> front == NULL){
        return 0;
    } else{ 
        return L->length; 
    }
} // Returns the number of elements in L.
int index(List L){
    if(L== NULL){
        fprintf(stderr, "ERROR: cannot call index() on a NULL list\n");
        exit(EXIT_FAILURE);
    } else if(L -> cursor != NULL){ 
        return L-> index; 
    } else
        return -1; 
    
} // Returns index of cursor element if defined, -1 otherwise.
void* front(List L){
    if(L== NULL){
        fprintf(stderr, "ERROR: cannot call front() on a NULL list\n");
        exit(EXIT_FAILURE);
    } else if(L->length <= 0){
        fprintf(stderr, "ERROR: cannot call front() on an empty list\n");
        exit(EXIT_FAILURE);
    } else{
        return L-> front -> data;
    } 
}// Returns front element of L. Pre: length()>0
void* back(List L){
    if(L == NULL){
        fprintf(stderr, "ERROR: cannot call back() on a NULL list\n");
            exit(EXIT_FAILURE);
    } else if(L->length <= 0){
        fprintf(stderr, "ERROR: cannot call back(List L) on an empty list\n");
        exit(EXIT_FAILURE); 
    }else{
        return L-> back -> data;  
    }
} // Returns back element of L. Pre: length()>0
void* get(List L){
    if(L == NULL){
        fprintf(stderr, "ERROR: cannot call get() on a NULL list\n");
        exit(EXIT_FAILURE);
    } else if(length(L)>0 && index(L) >=0){
        return L -> cursor -> data; 
    } else if(length(L) <= 0){
        fprintf(stderr, "ERROR: cannot call get() on an empty or negative list length\n");
        exit(EXIT_FAILURE);
    } else if(index(L) < 0){
        fprintf(stderr, "ERROR: cannot call get() on a negative index\n");
        exit(EXIT_FAILURE);
    } else{
        exit(EXIT_FAILURE);
    }
} // Returns cursor element of L. Pre: length()>0, index()>=0
// Manipulation procedures ----------------------------------------------------
void clear(List L){
    if(L == NULL){
        fprintf(stderr, "ERROR: calling clear() on NULL list\n");
        exit(EXIT_FAILURE);
    } else{ 
        while(L->front != NULL){
            deleteFront(L);
        }
        L -> front = L-> back = L-> cursor = NULL; 
        L -> length = 0;
    } 
} // Resets L to its original empty state.
void moveFront(List L){
    if(L == NULL){
        fprintf(stderr, "ERROR: calling moveFront() on NULL list\n");
        exit(EXIT_FAILURE);
    }else if(L->length > 0) {
        L->cursor = L->front;
        L-> index = 0; 
    }
} // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveBack(List L){
    if(L == NULL){
        fprintf(stderr, "ERROR: calling moveBack() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    else if (L->length >0){
        L->cursor = L->back;
        L-> index = L->length - 1; 
    }
} // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void movePrev(List L){
    if(L == NULL){
        fprintf(stderr, "ERROR: movePrev() called on NULL list\n");
        exit(EXIT_FAILURE);
    } else if(L->cursor != NULL && L->cursor != L->front){
        L->cursor = L->cursor -> previous; 
        L -> index --; 
    } else if(L->cursor != NULL && L->cursor == L->front){
        L->cursor = NULL;
        L->index = -1;  
    }
} // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L){
    if(L == NULL){
        fprintf(stderr, "ERROR: moveNext() called on NULL list\n");
        exit(EXIT_FAILURE);
    } else if(L->cursor != NULL && L->cursor != L->back){
        L->cursor = L->cursor -> next; 
        L -> index ++; 
    } else if(L->cursor != NULL && L->cursor == L->back){
        L->cursor = NULL; 
        L->index = -1;
    }
} // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void prepend(List L, void* data){
    if(L == NULL){
        fprintf(stderr,"ERROR: calling prepend() on NULL list\n");
        exit(EXIT_FAILURE);
    } 
    Node N = newNode(data);
    if(length(L) == 0){
        L->front = N;
        L->back = N;
    } else{
        L->front->previous = N; 
        N->next = L-> front;
        L->front = N; 

        if(L->index!= -1){
            L->index++;
        }
    } 
    L->length ++; 

} // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void append(List L, void* data){
    if(L == NULL){
        fprintf(stderr, "ERROR: calling append() on NULL list\n");
        exit(EXIT_FAILURE);
    } 
    Node N = newNode(data);
    if(length(L) == 0){
        L->front = N;
        L->back = N;
    } else{
        L->back-> next  = N; 
        N->previous = L-> back;
        L->back= N; 
    } 
    L->length ++; 
} // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.

void insertBefore(List L, void* data){
    if(L==NULL){
        fprintf(stderr, "ERROR: calling insertBefore() on NULL list\n");
        exit(EXIT_FAILURE);
    } 
    if(L->length <=0 ){
        fprintf(stderr, "ERROR: calling insertBefore() on an empty list\n");
        exit(EXIT_FAILURE);
    } 
    if(L->index < 0 ){
        fprintf(stderr, "ERROR: calling insertBefore() on list with undefined cursor\n");
        exit(EXIT_FAILURE);
    } else{ 
        Node N = newNode(data);
        if(L->cursor == L->front){
            L->cursor->previous = N;
            N->next = L->cursor; 
            L->front = N; 
        } else{
            Node temp = L-> cursor-> previous;
            L->cursor->previous = N; 
            N->next = L->cursor; 
            N->previous = temp;
            temp->next = N; 
        }
    }
    L-> index ++; 
    L-> length ++; 
} // Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, void* data){
    if(L==NULL){
        fprintf(stderr, "ERROR: calling insertAfter() on NULL list\n");
        exit(EXIT_FAILURE);
    } if(L->length <=0 ){
        fprintf(stderr, "ERROR: calling insertAfter() on an empty or undefined list length\n");
        exit(EXIT_FAILURE);
    } if(L->index < 0 ){
        fprintf(stderr, "ERROR: calling insertAfter() on list with undefined cursor\n");
        exit(EXIT_FAILURE);
    } else{
        Node N = newNode(data);
        if(L->cursor == L->back){
            L->cursor->next = N; 
            N->previous = L->cursor; 
            L->back = N; 
        } else{
            Node temp = L->cursor->next;
            L->cursor -> next = N; 
            N-> previous = L->cursor; 
            N->next = temp;
            temp->previous = N;
        }
    }
    L->length ++; 
} // Insert new element after cursor.
 // Pre: length()>0, index()>=0
void deleteFront(List L){
    if(L == NULL){
        fprintf(stderr,"ERROR: calling deleteFront() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    else if(length(L) <= 0){
        fprintf(stderr,"ERROR: calling deleteFront() on empty list\n");
        exit(EXIT_FAILURE);
    } else{
        Node temp = L->front;
        if(L->length == 1){
            L->front = L->back = NULL;
            L->cursor = NULL;
            L->index = -1;
        } else{
            L->front = L->front->next;
            L->front->previous = NULL;
            if(L -> index == 0){
                L -> cursor = NULL;
            }
            L->index--; 
        }
        freeNode(&temp);
        L->length --;    
    } 
} // Delete the front element. Pre: length()>0
void deleteBack(List L){
    if(L == NULL){
        fprintf(stderr,"ERROR: calling deleteBack() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    else if(length(L) <= 0){
        fprintf(stderr,"ERROR: calling deleteBack() on empty list\n");
        exit(EXIT_FAILURE);
    }
    else{
        Node temp = L->back;
        if(L-> length == 1){
            L->front = L->back = NULL;
            L->cursor = NULL;
            L->index = -1;
        } else{
            L->back = L->back->previous;
            L->back->next = NULL;
            if(L -> cursor == temp){
                L->cursor = NULL; 
                L->index = -1;
            }
        }      
        freeNode(&temp);
        L->length--;
    }
    
} // Delete the back element. Pre: length()>0
void delete(List L) {
    
    if (L == NULL) {
        fprintf(stderr, "ERROR: calling delete() on NULL List reference\n");
        exit(1);
    }
    if (L->length == 0) {
        fprintf(stderr, "ERROR: calling delete() on empty List\n");
        exit(1);
    }
    if (L->index < 0) {
        fprintf(stderr, "ERROR: calling delete() against undefined cursor\n");
        exit(1);
    }
    if (L->index == 0) {
        deleteFront(L);
    } else if (L->index == L->length - 1) {
        deleteBack(L);
    } else {
        Node oldPrev = L->cursor->previous;
        Node oldNext = L->cursor->next;
        oldPrev->next = oldNext;
        oldNext->previous = oldPrev;        
        freeNode(&(L->cursor));
        L->index = -1;
        L->cursor = NULL;
        L->length -= 1;
    }
} // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
// Other operations -----------------------------------------------------------
/* void printList(FILE* out, List L){
    Node N = NULL;
    if(L==NULL){
        fprintf(stderr, "ERROR: calling printList() on NULL list\n");
        exit(EXIT_FAILURE);
    } else{ 
        for(N = L->front; N != NULL; N = N->next){
            fprintf(out, "%d ", N->data);
        }
        fprintf(out,"\n");
    }
} // Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.
*/

