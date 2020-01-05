// Rukmini Bose 
// rubose 
// PA4

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

#define INF -1
#define NIL 0
#define WHITE 1 
#define GRAY 2 
#define BLACK 3

typedef struct GraphObj{
    int order; // number vertices 
    int size; // number edges
    int source; 
    
    List* neighbor; // list of neighboring vertices 
    int* color; 
    int* parent; 
    int* distance;
} GraphObj; 

Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->neighbor = malloc(sizeof(List) *(n+1)); 
    G->color = malloc(sizeof(int) * (n+1));
    G->parent = malloc(sizeof(int) * (n+1));
    G->distance = malloc(sizeof(int) * (n+1));

    for(int i = 1; i < n+1 ; i++){
        G->neighbor[i] = newList();
        G->color[i] = WHITE; 
        G->parent[i] = NIL; 
        G->distance[i] = INF; 
    }
    
    G->size = 0;
    G->source = NIL; 
    G->order = n;

    return G;
}

void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        Graph G = *pG; 
        for (int i = 1; i < (G->order)+1; i++) {
            freeList(&(G->neighbor[i]));
        }
        free(G->neighbor);
        free(G->color);
        free(G->distance);
        free(G->parent);
        free(*pG);
        *pG = NULL;
    }
}
/*** Access functions ***/
int getOrder(Graph G){
    if(G == NULL){
        fprintf(stderr,"ERROR: cannot call getOrder() on a NULL graph\n");
        exit(EXIT_FAILURE);
    } 
    return (G->order);
}
    
int getSize(Graph G){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call getSize() on a NULL graph\n");
        exit(EXIT_FAILURE);
    }
    return (G->size);
}
int getSource(Graph G){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call getSource() on a NULL graph\n");
        exit(EXIT_FAILURE);
    } 
    return (G->source);
}
int getParent(Graph G, int u){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call getParent() on a NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr,"ERROR: cannot call getParent() on out of bounds graph\n");
        exit(EXIT_FAILURE);
    }
    return (G->parent[u]);
}
int getDist(Graph G, int u){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call getDist() on a NULL graph\n");
        exit(EXIT_FAILURE);
    } 
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr,"ERROR: cannot call getDist() on out of bounds graph\n");
        exit(EXIT_FAILURE);
    } 
    if(getSource(G) == NIL){
        return INF; 
    }

    return G->distance[u];
}
void getPath(List L, Graph G, int u){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call getDist() on a NULL graph\n");
        exit(EXIT_FAILURE);
    } 
    if(getSource(G) == NIL){
        fprintf(stderr, "ERROR: cannot call getPath() on NULL source\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr,"ERROR: cannot call getDistance() on out of bounds graph\n");
        exit(EXIT_FAILURE);
    } 
    if(u == getSource(G)){
        append(L, getSource(G));
    } else if(G->parent[u] == NIL){
        append(L, NIL);
    } else{
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call makeNull() on a NULL graph\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i < getOrder(G)+1; i++){
        clear(G->neighbor[i]);
    }
    G->size = 0;

}

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
void addEdge(Graph G, int u, int v){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot addEdge() on NULL graph\n");
        exit(EXIT_FAILURE);
    }

    sortHelper(G->neighbor[u], v);
    sortHelper(G->neighbor[v], u);
    G->size++; 
}
void addArc(Graph G, int u, int v){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call addArc() on an empty graph\n");
        exit(EXIT_FAILURE);
    } 
    sortHelper(G->neighbor[u], v);
    G->size++;

}
void BFS(Graph G, int s){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot call BFS() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if(s < 1 || s > getOrder(G)){
        fprintf(stderr, "ERROR: cannot call BFS() on out of bounds graph\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i < getOrder(G)+1; i++){
        G->color[i] = WHITE; 
        G->parent[i] = NIL; 
        G->distance[i] = INF; 
    }

    G->source = s; 
    G->color[s] = GRAY; 
    G->parent[s] = NIL; 
    G->distance[s] = 0; 

    List L = newList(); 
    prepend(L, s); 

    while(length(L) > 0){
        int i = back(L); 
        deleteBack(L);

        moveFront(G->neighbor[i]);
        

        while(index(G->neighbor[i]) != -1){
            
            int j = get(G->neighbor[i]);

            
            if(G->color[j] == WHITE){
                G->color[j] = GRAY; 
                G->parent[j] = i; 
                G->distance[j] = G->distance[i]+1; 

                prepend(L, j);
            }
            moveNext(G->neighbor[i]); 
        }
    }

    freeList(&L);
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    if(G == NULL){
        fprintf(stderr, "ERROR: cannot print a NULL graph\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1 ; i < getOrder(G)+1 ; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->neighbor[i]);
    }
}