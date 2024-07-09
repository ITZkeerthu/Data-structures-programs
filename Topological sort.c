#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Function to find the indegree of each vertex
void findIndegree(int adj[MAX][MAX], int n, int indegree[]) 
{
    for (int i = 0; i < n; i++) 
    {
        indegree[i] = 0;
    }
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if (adj[i][j] == 1) 
            {
                indegree[j]++;
            }
        }
    }
}

// Function to perform topological sort using Kahn's Algorithm
void topologicalSort(int adj[MAX][MAX], int n) 
{
    int indegree[MAX], queue[MAX], front = 0, rear = 0, count = 0;
    int topOrder[MAX]; 
  // Store the topological order

    findIndegree(adj, n, indegree);

    // Enqueue all vertices with indegree 0
    for (int i = 0; i < n; i++) 
    {
        if (indegree[i] == 0) 
        {
            queue[rear++] = i;
        }
    }

    // Process vertices in the queue
    while (front < rear) 
    {
        int v = queue[front++];
        topOrder[count++] = v;

        // Reduce the indegree of adjacent vertices
        for (int i = 0; i < n; i++) 
        {
            if (adj[v][i] == 1) 
            {
                if (--indegree[i] == 0) 
                {
                    queue[rear++] = i;
                }
            }
        }
    }

    // Check if there was a cycle
    if (count != n) 
    {
        printf("The graph has a cycle!\n");
        return;
    }

    // Print the topological order
    printf("Topological Order: ");
    for (int i = 0; i < count; i++) 
    {
        printf("v%d ", topOrder[i] + 1);
    }
    printf("\n");
}

int main() 
{
    int n;
    int adj[MAX][MAX];

    // Take the number of vertices as input
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    // Take the adjacency matrix as input
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            scanf("%d", &adj[i][j]);
        }
    }

    topologicalSort(adj, n);

    return 0;
}
//____________________________________________________________________________________

/*int main() {
    int n = 7;
    int adj[MAX][MAX] = {
        {0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0}
    };

    topologicalSort(adj, n);

    return 0;
}
*/
//____________________________________________________________________________________
/* Output

Enter the number of vertices: 7
Enter the adjacency matrix:
0 1 1 1 0 0 0
0 0 0 1 1 0 0
0 0 0 1 0 0 0
0 1 0 0 1 0 0
0 0 0 0 0 0 1
0 0 0 0 0 0 1
0 0 0 0 0 0 0
  */
