#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct node {
    int data;
    struct node* next;
};
typedef struct node Node;

void addEdge(Node* adjList[], int u, int v);
void bfs(Node* adjList[], int vertices, int startNode, int visited[]);
void dfs(Node* adjList[], int visited[], int startNode);
Node* createNode(int data);

int main() {
    int v;
    printf("Enter number of vertices: ");
    scanf("%d", &v);

    Node* adjList[v];
    for (int i = 0; i < v; ++i) {
        adjList[i] = NULL;
    }

    int numEdges;
    printf("Enter number of edges: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; ++i) {
        int a, b;
        printf("Enter edge (u v): ");
        scanf("%d %d", &a, &b);

        // Adjust for 0-based indexing
        a -= 1;
        b -= 1;

        if (a < v && b < v) {
            addEdge(adjList, a, b);
            addEdge(adjList, b, a); // Assuming the graph is undirected
        } else {
            printf("Invalid edge (%d, %d)\n", a, b);
        }
    }

    int visited[v];
    for (int i = 0; i < v; ++i)
        visited[i] = 0;

    printf("Breadth First Traversal starting from vertex 0: ");
    bfs(adjList, v, 0, visited);

    for (int i = 0; i < v; ++i)
        visited[i] = 0;

    printf("\nDepth First Traversal starting from vertex 0: ");
    dfs(adjList, visited, 0);

    return 0;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Node* adjList[], int u, int v) {
    Node* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

void dfs(Node* adjList[], int visited[], int startNode) {
    visited[startNode] = 1;
    printf("%d ", startNode + 1);  // Adjusting for 1-based output
    Node* temp = adjList[startNode];
    while (temp != NULL) {
        int neighbor = temp->data;
        if (!visited[neighbor]) {
            dfs(adjList, visited, neighbor);
        }
        temp = temp->next;
    }
}

void bfs(Node* adjList[], int vertices, int startNode, int visited[]) {
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    visited[startNode] = 1;
    queue[rear++] = startNode;

    while (front != rear) {
        int currentNode = queue[front++];
        printf("%d ", currentNode + 1);  // Adjusting for 1-based output
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
