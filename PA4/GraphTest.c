// Rukmini Bose 
// rubose 
// PA4

#include<stdlib.h>
#include<stdio.h>
#include"Graph.h"
#include "List.h"

int main(int argc, char* argv[]){
    Graph undirected = NULL; 
    int n = 5;
    undirected = newGraph(n); 
    addEdge(undirected, 1, 3);
    addEdge(undirected, 3, 4);
    addEdge(undirected, 4, 2);
     
    printf("undirected graph: ");
    printGraph(stdout, undirected);
    
    printf("size of undirected graph: %d", getSize(undirected));
    printf("\n"); 

    for(int i = 1; i < n; i++){
        BFS(undirected, i); 
        for(int j = 1; j < n; j++){
            int dist = getDist(undirected, j);
            printf("Distance of undirected: %d-%d: %d\n", i, j, dist);
            printf("Parent of %d: %d\n", j, getParent(undirected, j));
        }       
    }


     

// -----------------------
    int m = 6;
    Graph directed = newGraph(m);
    
    
    addEdge(directed, 2, 4);
    addEdge(directed, 4, 5);
 
    printf("directed graph: ");
    printGraph(stdout, directed);
    
    printf("Order: %d\n", getOrder(directed));

    for(int i = 1; i < m; i++){
        BFS(directed, i); 
        printf("Source: %d\n", getSource(directed));
        for(int j = 1; j < m; j++){
            int dist = getDist(directed, j);
            printf("Distance of directed: %d-%d: %d\n", i, j, dist);
            
        }
    }

   BFS(directed, 2);
    List path2 = newList();
    getPath(path2,directed, 5);

    printf("getPath(): ");
    printf("Path from 2 to 5: ");
    printList(stdout,path2);
    printf("\n");   

    freeGraph(&undirected);
    freeGraph(&directed);
    freeList(&path1);
    freeList(&path2);
}