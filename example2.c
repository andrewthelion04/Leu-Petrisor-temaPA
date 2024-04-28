#include<stdlib.h>
#include<stdio.h>
typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adjacencyLists;
} GPH;

NODE *createNode(int v)
{
    NODE *newNode = malloc(sizeof(NODE));
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}
GPH *createGraph(int vertices)
{
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacencyLists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * vertices);

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacencyLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(GPH *graph, int src, int dest)
{
    NODE *newNode = createNode(dest);

    newNode->next = graph->adjacencyLists[src];
    graph->adjacencyLists[src] = newNode;

    newNode = createNode(src);

    newNode->next = graph->adjacencyLists[dest];
    graph->adjacencyLists[dest] = newNode;
}

void insertEdges(int numVertices, int numEdges, GPH *graph)
{
    int src, dest;

    printf("Adauga %d muchii (de la 0 la %d)\n", numEdges, numVertices - 1);

    for (int i = 0; i < numEdges; i++)
    {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

int isEmpty(NODE *queue)
{
    return queue == NULL;
}

void enqueue(NODE **queue, int data)
{
    NODE *newNode = createNode(data);

    if (isEmpty(*queue))
    {
        *queue = newNode;
    }
    else
    {
        NODE *temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}


int dequeue(NODE **queue)
{
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;

    return data;
}

void printGraph(GPH *graph)
{
    int i;
    for (i = 0; i < graph->vertices; i++)
    {
        NODE *temp = graph->adjacencyLists[i];

        while (temp)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }

        printf("\n");
    }
}

void printQueue(NODE *queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}

void wipeVisitedList(GPH *graph, int nr_of_vertices)
{
    for (int i = 0; i < nr_of_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void dfs(GPH *graph, int vertex_nr)
{
    NODE *adj_list = graph->adjacencyLists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d ", vertex_nr);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            dfs(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void bfs(GPH *graph, int start)
{
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!isEmpty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacencyLists[current];

        while (temp)
        {
            int adjVertex = temp->data;

            if (graph->visited[adjVertex] == 0)
            {
                graph->visited[adjVertex] = 1;
                enqueue(&queue, adjVertex);
            }
            temp = temp->next;
        }
    }
}


int main()
{
    int numVertices;
    int numEdges;
    int src, dest;
    int startingVertex;
    int *adjMatrix;

    printf("cate noduri are graful?\n");
    scanf("%d", &numVertices);

    printf("cate muchii are graful?\n");
    scanf("%d", &numEdges);


    GPH *graph = createGraph(numVertices);
    insertEdges(numVertices, numEdges, graph);

    printf("de unde plecam in DFS?\n");
    scanf("%d", &startingVertex);

    printf("parcurgere cu DFS:");
    dfs(graph, startingVertex);

    wipeVisitedList(graph, numVertices);
    printf("\n");

    printf("\nde unde plecam in BFS?\n");
    scanf("%d", &startingVertex);

    printf("parcurgere cu BFS:");
    bfs(graph, startingVertex);

    return 0;
}
