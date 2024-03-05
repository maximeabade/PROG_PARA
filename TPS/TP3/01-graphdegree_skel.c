#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// structure of an undirected graph 
struct edge	 
{ 
   // vertices 
   int vertex1;
   int vertex2;	
}; 

struct graph
{
   int n_vertex;
   int n_edges;
   struct edge *list_of_edges;
};

struct graph *readgraph(char *filename){
   FILE *fd;
   struct edge *list_of_edges;
   struct graph *G;
   int vertex1, vertex2;
   int i, no_of_edges, no_of_vertices;

   printf("Reading file %s\n", filename);
   fd = fopen(filename, "r");
   if (fd == NULL) {
      perror("Error opening the file.\n");
      exit(-1);
   }

   fscanf(fd, "%d", &no_of_vertices);
   fscanf(fd, "%d", &no_of_edges);
   printf("Number of vertices = %d\n", no_of_vertices);
   printf("Number of edges = %d\n", no_of_edges);
   list_of_edges = (struct edge *)malloc(no_of_edges * sizeof(struct edge));
   for (i = 0; i < no_of_edges; i++) {
      fscanf(fd, "%d %d", &vertex1, &vertex2);
      list_of_edges[i].vertex1 = vertex1;
      list_of_edges[i].vertex2 = vertex2;
   }
   fclose(fd);
   G = (struct graph *)malloc(sizeof(struct graph));
   G->n_vertex = no_of_vertices;
   G->n_edges = no_of_edges;
   G->list_of_edges = list_of_edges;
   return G;
}

int main(int argc, char **argv)
{
   int i;
   int *degree;
   double start_time, run_time;
   struct graph *G;

   if (argc != 2) {
      printf("Please enter filename containing the graph structure.\n");
      exit(0);
   }

   G = readgraph(argv[1]);

   degree = (int *)malloc(G->n_vertex * sizeof(int));
   for (i = 0; i < G->n_vertex; i++) {
      degree[i] = 0;
   }

   #pragma omp parallel for
   for (i = 0; i < G->n_edges; i++) {
      #pragma omp atomic
      degree[G->list_of_edges[i].vertex1]++;
      #pragma omp atomic
      degree[G->list_of_edges[i].vertex2]++;
   }

   for (i = 0; i < G->n_vertex; i++) {
      printf("Vertex %d has degree %d\n", i, degree[i]);
   }

   free(degree);
   free(G->list_of_edges);
   free(G);
   return 0;
}
