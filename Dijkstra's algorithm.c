#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>  // for malloc

#define MAX_VERTICES 1000  // Maximum number of vertices
#define INFINITY INT_MAX   // Infinity represented as maximum integer value

// Typedefs for clarity
typedef struct Edge 
{
    int dest;
    int weight;
    struct Edge* next;
} Edge;

typedef struct Vertex 
{
    Edge* head;  // Head of the adjacency list
} Vertex;

typedef struct Graph 
{
    int numVertices;
    Vertex* vertices[MAX_VERTICES];
} Graph;

typedef struct Table 
{
    bool known[MAX_VERTICES];   // Whether the shortest path is known
    int dist[MAX_VERTICES];     // Shortest distance from the source
    int path[MAX_VERTICES];     // Previous vertex in the shortest path
} Table

// Function prototypes
void initGraph(Graph* graph, int numVertices);
void addEdge(Graph* graph, int src, int dest, int weight);
void initTable(Table* table, int numVertices, int source);
int minDistance(Table* table, int numVertices);
void dijkstra(Graph* graph, Table* table, int source);
void printShortestPaths(Table* table, int numVertices, int source);
void freeGraph(Graph* graph, int numVertices);

int main() 
{
    Graph graph;
    int numVertices, numEdges;
    
    printf("Enter number of vertices and edges: ");
    scanf("%d", &numVertices);
    scanf("%d", &numEdges);
    
    initGraph(&graph, numVertices);
    
    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < numEdges; ++i) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(&graph, src, dest, weight);
        addEdge(&graph, dest, src, weight);  // Assuming undirected graph
    }
    
    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);
    
    Table table;
    dijkstra(&graph, &table, source);
    printShortestPaths(&table, numVertices, source);
    
    // Free allocated memory for the graph
    freeGraph(&graph, numVertices);
    
    return 0;
}

// Function to initialize a graph with 'numVertices' vertices
void initGraph(Graph* graph, int numVertices) {
    graph->numVertices = numVertices;
    for (int i = 0; i < numVertices; ++i) {
        graph->vertices[i] = (Vertex*)malloc(sizeof(Vertex));  // Allocate memory for each vertex
        graph->vertices[i]->head = NULL;  // Initialize each vertex's adjacency list as NULL
    }
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    // Create a new edge
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = graph->vertices[src]->head;  // Insert at the beginning of adjacency list
    graph->vertices[src]->head = newEdge;
}

// Function to initialize the result table for Dijkstra's algorithm
void initTable(Table* table, int numVertices, int source) {
    for (int i = 0; i < numVertices; ++i) {
        table->known[i] = false;
        table->dist[i] = INFINITY;
        table->path[i] = -1;  // No path initially
    }
    table->dist[source] = 0;  // Distance from source to itself is zero
}

// Function to find the vertex with the minimum distance that is not yet known
int minDistance(Table* table, int numVertices) {
    int minDist = INFINITY;
    int minIndex = -1;
    for (int v = 0; v < numVertices; ++v) {
        if (!table->known[v] && table->dist[v] < minDist) {
            minDist = table->dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to run Dijkstra's algorithm
void dijkstra(Graph* graph, Table* table, int source) {
    initTable(table, graph->numVertices, source);
    
    for (int count = 0; count < graph->numVertices - 1; ++count) {
        int u = minDistance(table, graph->numVertices);
        table->known[u] = true;
        
        // Update distances of adjacent vertices
        Edge* edge = graph->vertices[u]->head;
        while (edge != NULL) {
            int v = edge->dest;
            if (!table->known[v] && table->dist[u] != INFINITY &&
                table->dist[u] + edge->weight < table->dist[v]) {
                table->dist[v] = table->dist[u] + edge->weight;
                table->path[v] = u;
            }
            edge = edge->next;
        }
    }
}

// Function to print the shortest paths from the source vertex
void printShortestPaths(Table* table, int numVertices, int source) {
    printf("Shortest paths from vertex %d:\n", source);
    for (int i = 0; i < numVertices; ++i) {
        if (i != source) {
            printf("Vertex %d: Distance = %d, Path = ", i, table->dist[i]);
            
            // Print the path from source to i
            int prev = table->path[i];
            printf("%d", i);
            while (prev != -1) {
                printf(" <- %d", prev);
                prev = table->path[prev];
            }
            printf("\n");
        }
    }
}

// Function to free allocated memory for the graph
void freeGraph(Graph* graph, int numVertices) {
    for (int i = 0; i < numVertices; ++i) {
        Edge* edge = graph->vertices[i]->head;
        while (edge != NULL) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
        free(graph->vertices[i]);
    }
}
