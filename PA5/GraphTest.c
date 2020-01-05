// Rukmini Bose 
// rubose 
// PA5

#include<stdlib.h>
#include<stdio.h>
#include"Graph.h"
#include "List.h"

int main(int argc, char* argv[]){
    int m = 10;
    Graph G = newGraph(m);
    List S = newList();

    for(int i = 1; i <= m; i++){
        append(S, i);
    }
    addArc(G, 2, 4);
    addArc(G, 4, 5);
 
    printf("G graph: ");
    printGraph(stdout, G);
    
    printf("Order: %d\n", getOrder(G));

    printf("Size of graph: %d", getSize(G));
    printf("\n");
    for(int i = 1; i < m; i++){
        DFS(G, S); 
        for(int j = 1; j < m; j++){
            printf("Parent of %d: %d\n", j, getParent(G, j));
            
        }
    }

   DFS(G, S);
   printf("DFS: \n");
   printf("x: d f p\n");
   for(int i = 1; i <= 10 ; i++){
        printf("%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i),
               getParent(G, i));

    }

    Graph trans = transpose(G);
    printf("Transpose graph: \n");
    printGraph(stdout, trans);
    printf("\n");
    Graph copy= copyGraph(trans);
    printf("Copy of Transpose Graph: \n");
    printGraph(stdout, copy);

    freeGraph(&G);
    freeGraph(&trans);
    freeGraph(&copy);
    freeList(&S);
}
