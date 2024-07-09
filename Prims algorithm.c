#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_VERTICES 1000  // Maximum number of vertices
#define INFINITY INT_MAX   // Infinity represented as maximum integer value

// Typedefs for clarity
typedef struct Edge {
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
    bool known[MAX_VERTICES];   // Whether the vertex is included in MST
    int dist[MAX_VERTICES];     // Minimum weight edge connecting to MST
    int parent[MAX_VERTICES];   // Parent node in MST
} Table;

// Function prototypes
void initGraph(Graph* graph, int numVertices);
void addEdge(Graph* graph, int src, int dest, int weight);
void initTable(Table* table, int numVertices);
int minDistance(Table* table, int numVertices);
void primMST(Graph* graph, Table* table, int source);
void printMST(Table* table, int numVertices, int source);
// Driver function
int main() {
    Graph graph;
    Table table;
    int numVertices, numEdges, source;

    printf("Enter number of vertices and edges: ");
    scanf("%d", &numVertices);
    scanf("%d", &numEdges);

    initGraph(&graph, numVertices);

    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < numEdges; ++i) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(&graph, src, dest, weight);
    }

    printf("Enter the source vertex: ");
    scanf("%d", &source);

    primMST(&graph, &table, source);
    printMST(&table, numVertices, source);

    // Free allocated memory for the graph
    freeGraph(&graph, numVertices);

    return 0;
}

// Function to initialize a graph with 'numVertices' vertices
void initGraph(Graph* graph, int numVertices) {
    graph->numVertices = numVertices;
    for (int i = 0; i < numVertices; ++i) {
        graph->vertices[i] = (Vertex*)malloc(sizeof(Vertex));
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

    // Since the graph is undirected, add the edge back from dest to src
    newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = src;
    newEdge->weight = weight;
    newEdge->next = graph->vertices[dest]->head;  // Insert at the beginning of adjacency list
    graph->vertices[dest]->head = newEdge;
}

// Function to initialize the result table for Prim's algorithm
void initTable(Table* table, int numVertices) {
    for (int i = 0; i < numVertices; ++i) {
        table->known[i] = false;
        table->dist[i] = INFINITY;
        table->parent[i] = -1;  // No parent initially
    }
}

// Function to find the vertex with the minimum distance that is not yet included in MST
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

// Function to run Prim's algorithm
void primMST(Graph* graph, Table* table, int source) {
    initTable(table, graph->numVertices);
    table->dist[source] = 0;  // Start from the source vertex

    for (int count = 0; count < graph->numVertices - 1; ++count) {
        int u = minDistance(table, graph->numVertices);
        table->known[u] = true;

        // Update distances of adjacent vertices not yet included in MST
        Edge* edge = graph->vertices[u]->head;
        while (edge != NULL) {
            int v = edge->dest;
            int weight = edge->weight;
            if (!table->known[v] && weight < table->dist[v]) {
                table->parent[v] = u;
                table->dist[v] = weight;
            }
            edge = edge->next;
        }
    }
}

// Function to print the Minimum Spanning Tree (MST)
void printMST(Table* table, int numVertices, int source) {
    printf("Edges in the Minimum Spanning Tree (MST):\n");
    for (int i = 0; i < numVertices; ++i) {
        if (i != source) {
            printf("(%d - %d) Weight: %d\n", table->parent[i], i, table->dist[i]);
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
