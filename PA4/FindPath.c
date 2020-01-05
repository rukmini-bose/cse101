// Rukmini Bose 
// rubose 
// PA4

//-----------------------------------------------------------------------------
//  FindPath.c 
//  A test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

#define MAX_LENGTH 20000

int main(int argc, char** argv) {

  // Sanity check
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
  Graph graph = newGraph(n);
  // At this point, we have an empty graph of size `n`, with `n` being the first line in the input file `in`

  int left = -1;
  int right = -1;
  for (fscanf(in, "%d %d\n", &left, &right); left != 0; fscanf(in, "%d %d\n", &left, &right)) {
    // Each iteration of this loop populates the variables `left` and `right` with the corresponding
    // entries in the file, until it hits that first 0 0 line.
    
    // TODO: add an EDGE in `graph` from `left` to `right`. This should be a single line of code
    addEdge(graph, left, right);
  }
  printGraph(out, graph);
  fprintf(out, "\n");
  // At this point, `graph` should be fully populated

  List list = newList();
  for (fscanf(in, "%d %d\n", &left, &right); left != 0; fscanf(in, "%d %d\n", &left, &right)) {
    // This loop corresponds to the logic after the first 0 0. `left` and `right` are still
    // updated in the loop as before.

    // TODO: perform a BFS from `left`, and print the distance to `right` as instructed.
    // This will definitely be more than one line of code.
    BFS(graph, left);
    getPath(list, graph, right);
    if(getDist(graph, right) != INF){
        fprintf(out, "The distance from %d to %d is %d\n", left, right, length(list) -1);
        fprintf(out, "A shortest %d-%d path is: ", left, right);
        printList(out, list);
        fprintf(out, "\n");
    } else{
        fprintf(out, "The distance from %d to %d is infinity\n", left, right);
        fprintf(out, "No %d-%d path exists\n", left, right);
        fprintf(out, "\n");
    }
    clear(list);
  }
freeList(&list);
freeGraph(&graph);
fclose(out);
fclose(in);
}