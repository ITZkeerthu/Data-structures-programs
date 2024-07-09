#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure to represent a node in adjacency list
struct node {
    int data;
    struct node* next;
};

// **typedef for Node structure**
typedef struct node Node;

void addEdge(Node* adjList[], int u, int v);
void bfs(Node* adjList[], int vertices,int startNode, int visited[]);

int main()
{
    // Number of vertices in the graph
    printf("Enter number of vertices");
    int v;
    scanf("%d",&v);
    int a,b;

    // Adjacency list representation of the graph
    Node* adjList[v];
    for (int i = 0; i < v; ++i)
    {
        adjList[i] = NULL;
        scanf("%d%d",&a,&b);
        addEdge(adjList,a,b);
    }

    // Mark all the vertices as not visited
    int visited[v];
    for (int i = 0; i < v; ++i)
        visited[i] = 0;

    // Perform BFS traversal starting from vertex 0
    printf(
        "Breadth First Traversal starting from vertex 0: ");
    bfs(adjList, v, 0, visited);

    return 0;
}


// Function to create a new node
Node* createNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge to the graph
void addEdge(Node* adjList[], int u, int v)
{
    Node* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

// Function to perform Breadth First Search on a graph
// represented using adjacency list
void bfs(Node* adjList[], int vertices,
         int startNode, int visited[])
{
    // Create a queue for BFS
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    // Mark the current node as visited and enqueue it
    visited[startNode] = 1;
    queue[rear++] = startNode;

    // Iterate over the queue
    while (front != rear) {
        // Dequeue a vertex from queue and print it
        int currentNode = queue[front++];
        printf("%d ", currentNode);

        // Get all adjacent vertices of the dequeued vertex
        // currentNode If an adjacent has not been visited,
        // then mark it visited and enqueue it
        Node* temp = adjList[currentNode];
        while (temp != NULL) {
            int neighbor = temp->data;
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                queue[rear++] = neighbor;
            }
            temp = temp->next;
        }
    }
}
