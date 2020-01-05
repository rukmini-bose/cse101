// Rukmini Bose 
// rubose
// PA5

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

#define UNDEF -2
#define INF -1
#define NIL 0
#define WHITE 1 
#define GRAY 2 
#define BLACK 3

typedef struct GraphObj{
    int order; // number of vertices 
    int size; // number of edges 
    int source; 

    List* neighbor; 
    int* color; 
    int* parent; 
    int* distance; 
    int* discover; 
    int* finish; 
} GraphObj; 

/* Constructors-Destructors */
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->neighbor = malloc(sizeof(List) * (n+1));
    G->color = malloc(sizeof(int) * (n+1));
    G->parent = malloc(sizeof(int) * (n+1));
    G->distance = malloc(sizeof(int) * (n+1));
    G->discover = malloc(sizeof(int) * (n+1));
    G->finish = malloc(sizeof(int) * (n+1));

    for(int i = 1; i < n+1 ; i++){
        G->neighbor[i] = newList(); 
        G->color[i] = WHITE; 
        G->parent[i] = NIL; 
        G->distance[i] = INF; 
        G->discover[i] = UNDEF; 
        G->finish[i] = UNDEF; 
    }

    G->size = 0; 
    G->source = NIL; 
    G->order = n;

    return G; 
}
void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        Graph G = *pG; 
        for(int i = 1; i < (G->order)+1; i++){
            freeList(&(G->neighbor[i]));
        }
        free(G->neighbor);
        free(G->color);
        free(G->distance);
        free(G->parent);
        free(G->discover);
        free(G->finish);
        free(*pG);
        *pG = NULL;
    }
}
/* Access functions */
int getOrder(Graph G){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call getOrder() on a NULL Graph\n");
        exit(EXIT_FAILURE);
    } 
    return G->order;
}
int getSize(Graph G){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call getSize() on a NULL Graph\n");
        exit(EXIT_FAILURE);
    } 
    return G->size;
}
int getParent(Graph G, int u) /* Pre: 1<=u<=n=getOrder(G) */ {
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call getParent() on a NULL graph\n");
        exit(EXIT_FAILURE);
    } 
    if(!(1 <= u && u <= getOrder(G))){
        fprintf(stderr, "ERROR: cannot call getParent() because out of bounds\n");
        exit(EXIT_FAILURE);
    } 
    return G->parent[u];
}
int getDiscover(Graph G, int u) /* Pre: 1<=u<=n=getOrder(G) */{
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call getDiscover() on a NULL graph\n");
        exit(EXIT_FAILURE);
    } 
    if(!(1 <= u && u <= getOrder(G))){
        fprintf(stderr, "ERROR: cannot call getDiscover() because out of bounds\n");
        exit(EXIT_FAILURE);
    } 
    return G->discover[u];
}
int getFinish(Graph G, int u) /* Pre: 1<=u<=n=getOrder(G) */{
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call getFinish() on a NULL graph\n");
        exit(EXIT_FAILURE);
    } 
    if(!(1 <= u && u <= getOrder(G))){
        fprintf(stderr, "ERROR: cannot call getFinish() because out of bounds\n");
        exit(EXIT_FAILURE);
    } 
    return G->finish[u];
}
/* Manipulation procedures */
void sortHelper(List L, int v){
    if(L == NULL){
        fprintf(stderr, "ERROR: cannot call sortHelper() on NULL list\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) == 0){
        append(L, v);
        return; 
    }
    moveFront(L);
    while(index(L) != -1){
        if(v < get(L)){
            insertBefore(L,v);
            return;
        }
        moveNext(L); 
    }

    if(index(L) == -1){
        append(L,v);
    }
}
void addArc(Graph G, int u, int v) /* Pre: 1<=u<=n, 1<=v<=n */ {
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call addArc() on an empty graph\n");
        exit(EXIT_FAILURE);
    } 
    if(!(1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G))){
        fprintf(stderr, "ERROR: cannot call getArc() because out of bounds\n");
        exit(EXIT_FAILURE);
    }
    sortHelper(G->neighbor[u], v);
    G->size++;
}
void addEdge(Graph G, int u, int v) /* Pre: 1<=u<=n, 1<=v<=n */ {
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call addEdge() on a NULLgraph\n");
        exit(EXIT_FAILURE);
    } 
    if(!(1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G))){
        fprintf(stderr, "ERROR: cannot call addEdge() because out of bounds\n");
        exit(EXIT_FAILURE);
    }
    sortHelper(G->neighbor[u], v);
    sortHelper(G->neighbor[v], u);
    G->size++; 
}

void Visit(Graph G, List S, int v, int p, int* time){
    if(G == NULL){
        fprintf(stderr,"ERROR: cannot call Visit() on a NULL Graph\n");
        exit(EXIT_FAILURE);
    } 
    if(S == NULL){
        fprintf(stderr, "ERROR: cannot call Visit() on a NULL List\n");
        exit(EXIT_FAILURE);
    } 

     if(G->color[v] != WHITE){
        return;
    }
    (*time)++;
    G->discover[v] = *time; 
    G->color[v] = GRAY;

    G->parent[v] = p;
   
    moveFront(G->neighbor[v]);
    while(index(G->neighbor[v]) != -1){
        Visit(G, S, get(G->neighbor[v]), v, time);
        moveNext(G->neighbor[v]);
    }
    G->color[v] = BLACK;
    (*time)++; 
    G->finish[v] = *time; 
    prepend(S,v);
}
void DFS(Graph G, List S) /* Pre: length(S)==getOrder(G) */ {
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call DFS() on a NULL Graph\n");
        exit(EXIT_FAILURE);
    }
    if(length(S) != getOrder(G)){
        fprintf(stderr, "ERROR: cannot call DFS on graph of insufficient length\n");
        exit(EXIT_FAILURE);
    } 
    if(S == NULL){ 
        fprintf(stderr, "ERROR: cannot call DFS() on NULL List\n");  
        exit(EXIT_FAILURE);  
    }


    for(int i = 1; i < getOrder(G) + 1; i++){
        G->color[i] = WHITE; 
        G->parent[i] = NIL; 
        G->discover[i] = UNDEF; 
        G->finish[i] = UNDEF; 
    }
    moveFront(S);

    moveFront(S);
    int time = 0;
    while(index(S) != -1){
        int v = get(S);
        int p = NIL;
        Visit(G, S, v, p, &time);
        moveNext(S);
    }

    for(int i = 0; i < G->order; i++){
        deleteBack(S);
    }
}

/* Other Functions */
Graph transpose(Graph G){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call transpose() on an empty graph\n");
        exit(EXIT_FAILURE);
    } 
    Graph T = newGraph(getOrder(G));
    for(int i = 1; i < getOrder(G) + 1; i++){
        moveFront(G->neighbor[i]);
        List temp = G->neighbor[i];
        while(index(temp) != -1){
            int x = get(temp);
            addArc(T, x, i);
            moveNext(G->neighbor[i]);
        }
    }
    return T; 

}
Graph copyGraph(Graph G){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call copyGraph() on a NULL graph\n");
        exit(EXIT_FAILURE);
    }
    Graph copy = newGraph(getOrder(G));
    for(int i = 1; i < getOrder(G) + 1; i++){
        moveFront(G->neighbor[i]);

        while(index(G->neighbor[i]) != -1){
            addArc(copy, i, get(G->neighbor[i]));
            moveNext(G->neighbor[i]);
        }
    }
    return copy; 
}
void printGraph(FILE* out , Graph G){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot print a NULL graph\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1 ; i < getOrder(G)+1 ; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->neighbor[i]);
    }
}






