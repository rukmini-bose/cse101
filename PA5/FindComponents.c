// Rukmini Bose 
// rubose 
// PA5

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

#define MAX_LENGTH 20000

int main(int argc, char** argv) {
    if (argc != 3) {
    fprintf(stderr, "Usage: FindPath <input file> <output file>\n");
    exit(1);
  }

  // Open input and output files
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

  int n;
  fscanf(in, "%d\n", &n);
  Graph G = newGraph(n);
  // At this point, we have an empty graph of size `n`, with `n` being the first line in the input file `in`

  int left = -1;
  int right = -1;

    for (fscanf(in, "%d %d\n", &left, &right); left != 0; fscanf(in, "%d %d\n", &left, &right)) {
    // Each iteration of this loop populates the variables `left` and `right` with the corresponding
    // entries in the file, until it hits that first 0 0 line.
    
    // TODO: add an EDGE in `graph` from `left` to `right`. This should be a single line of code
        addArc(G, left, right);
  }


  List stack = newList();


  for(int i = 1; i <= n; i++){
    append(stack, i);
  }

  DFS(G, stack);
  
  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);

  Graph T = transpose(G);


  DFS(T, stack);

  int SCCcount = 0;
  for(int i = 1; i < getOrder(T) + 1; i++){
    if(getParent(T, i) == NIL){
        SCCcount++;
    }
  }

  fprintf(out, "\n");
  fprintf(out, "G contains %d strongly connected components:\n", SCCcount);
  
  List *scc = malloc(sizeof(List) * (SCCcount+1));

  
 
  for(int i = 1; i < SCCcount+1; i++){
    scc[i] = newList();
  }

  for(int i = 1; i < SCCcount+1;){
    int front = back(stack);
    deleteBack(stack);
    prepend(scc[i], front);
    if(getParent(T, front) == NIL){
        i++;
    }

  }
for(int i = 1; i < SCCcount +1; i++){
    fprintf(out, "Component %d: ", i);
    printList(out, scc[i]);
    fprintf(out, "\n");
}

freeGraph(&G);
freeGraph(&T);

for(int i = 1; i < SCCcount + 1; i++){
    freeList(&scc[i]);
}

free(scc);
freeList(&stack);
fclose(out);
fclose(in);


}