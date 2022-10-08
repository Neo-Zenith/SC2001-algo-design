#include <stdio.h>
#include <stdlib.h>
#include "structures.h"         // refer to this file for the data structures used

/*  ==== Data Structures used:
    Graph 
    {
        int V;                  # of vertices
        int E;                  # of edges
        int **adjMatrx;         # graph representation in matrix
        int **adjList           # graph representation in linked list
    }

    QueueNode
    {
        int vertex;             vertex value 
        int dist;               vertex current min distance from start
    }

    int start is the starting vertex
    int *visited is an auxillary array that keeps track of the visited nodes
    int *parent is an auxillary array that keep tracks of the parent nodes
    int *dist is an auxillary array that keep tracks of the min distance from start to current node
*/


// dijkstra's shortest path search algorithm implemented using min heap priority queue
void MinHeapPathSearch(Graph *g, int start, int *visited, int *parent, int *dist)
{
    QueueNode pQueue[MAX];              // priority queue
    int tail = -1;                      // initialize end of queue to be -1 (queue is empty)

    // default value initialization
    for (int i = 1; i <= g->V; i ++)
    {
        visited[i] = 0;
        dist[i] = MAX_DIST;
        parent[i] = -1;
    }

    GraphNode *ptr = g->adjList[start];     // begin at vertex start
    
    // put all adjacent vertex to start to priority queue
    while (ptr != NULL)
    {
        if (ptr->weight != -1) 
        {
            insert(pQueue, &tail, ptr->vertex, ptr->weight);        // insert will build minheap everytime
            dist[ptr->vertex] = ptr->weight;
            parent[ptr->vertex] = start;
        }
        ptr = ptr->next;
    }

    // we have visited start
    visited[start] = 1;
    dist[start] = 0;

    while (! isEmptyQueue(pQueue, &tail))
    {
        int target = getFront(pQueue);      // expand the vertex with smallest dist
        visited[target] = 1;
        delete(pQueue, &tail);              // remove from queue

        GraphNode *ptr = g->adjList[target];
        while (ptr != NULL)
        {   
            /* only expand if:
                1. not yet visited
                2. weight(target, i) + dist[target] is smaller than dist[i]
            */
            if (visited[ptr->vertex] != 1 && ptr->weight != -1 && ptr->weight + dist[target] < dist[ptr->vertex]) 
            {
                dist[ptr->vertex] = ptr->weight + dist[target];
                insert(pQueue, &tail, ptr->vertex, dist[ptr->vertex]);      // put into queue
                parent[ptr->vertex] = target;
            }
            ptr = ptr->next;
        }
    }

    /*  DEBUG
        printf("\n");
        for (int i = 1; i <= g->V; i ++)
        {
            printf("%d ", dist[i]);
        }
    */
    free(ptr);          // remember to free any unusued dynamically allocated variables!!
}


// dijkstra's shortest path search algorithm implemented using array-based priority queue
void ArrayPathSearch(Graph *g, int start, int *visited, int *dist, int *parent)
{
    QueueNode pQueue[MAX];
    int tail = -1;

    for (int i = 1; i <= g->V; i ++)
    {
        visited[i] = 0;
        dist[i] = MAX_DIST;
        parent[i] = -1;
    
        if (g->adjMatrix[start][i] != -1) 
        {
            // enqueue incurs O(1) since it just appends to end of queue
            enqueue(pQueue, &tail, i, g->adjMatrix[start][i]);      
            dist[i] = g->adjMatrix[start][i];
            parent[i] = start;
        }
    }

    visited[start] = 1;
    dist[start] = 0;

    while (! isEmptyQueue(pQueue, &tail))
    {
        // here dequeue incurs at worst-case O(vertex) complexity 
        /*
            How worst-case occurs?
                When queue is almost full
            
            Regardless dequeue will incur O(n) complexity where n = size of queue
            if n == vertex, then O(vertex)
        */
        int target = dequeue(pQueue, &tail);
        visited[target] = 1;
        
        for (int i = 1; i <= g->V; i ++)
        {
            if (visited[i] != 1 && g->adjMatrix[target][i] != -1 && g->adjMatrix[target][i] + dist[target] < dist[i]) 
            {
                dist[i] = g->adjMatrix[target][i] + dist[target];
                enqueue(pQueue, &tail, i, dist[i]);
                parent[i] = target;
            }
        }
    }

    /*  DEBUG
        printf("\n");
        for (int i = 1; i <= g->V; i ++)
        {
            printf("%d ", dist[i]);
        }
    */
}

// helper function to print the adjacency matrix
void printAdjMatrix(Graph *g)
{
    printf("\n===== Printing Adjacency Matrix =====\n");
    for (int i = 1; i <= g->V; i ++)
    {
        for (int j = 1; j <= g->V; j ++)
        {
            (g->adjMatrix[i][j] != -1) ? printf("%d ", g->adjMatrix[i][j]): printf("# ");
        }
        printf("\n");
    }
    printf("\nDone!\n");
}

// helper function to print the adjacency list
void printAdjList(Graph *g)
{
    printf("\n===== Printing Adjacency List =====\n");
    for (int i = 1; i <= g->V; i ++)
    {
        GraphNode *ptr = g->adjList[i];
        printf("%d", i);
        while (ptr != NULL)
        {
            printf(" [--(%d)-->%d]", ptr->weight, ptr->vertex);
            ptr = ptr->next;
        }
        printf("\n");
    }
    printf("\nDone!\n");
}
