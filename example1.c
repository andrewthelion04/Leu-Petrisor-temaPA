#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node* next;
} NODE;

typedef struct Graph
{
    int numVertices;
    int* visited;
    NODE** head;
} GPH;

typedef struct Stack
{
    int position;
    int stackCapacity;
    int* stackArray;
} STK;

NODE* createNode(int data)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addEdge(GPH* graph, int src, int dest)
{
    NODE* newNode = createNode(dest);
    newNode->next = graph->head[src];
    graph->head[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->head[dest];
    graph->head[dest] = newNode;
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

GPH* createGraph(int numVertices)
{
    GPH* graph = (GPH*)malloc(sizeof(GPH));
    graph->numVertices = numVertices;
    graph->head = (NODE**)malloc(numVertices * sizeof(NODE*));
    graph->visited = (int*)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++)
    {
        graph->head[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}


STK* createStack(int stackCapacity)
{
    STK* stack = (STK*)malloc(sizeof(STK));
    stack->stackArray = (int*)malloc(stackCapacity * sizeof(int));
    stack->position = -1;
    stack->stackCapacity = stackCapacity;
    return stack;
}

void push(int data, STK* s)
{
    if (s->position < s->stackCapacity - 1)
    {
        s->position++;
        s->stackArray[s->position] = data;
    }
}

void DFS(GPH* graph, STK* stack, int v_nr)
{
    if (graph->visited[v_nr] == 1)
    {
        return;
    }

    graph->visited[v_nr] = 1;
    push(v_nr, stack);

    NODE* adj_list = graph->head[v_nr];
    NODE* aux = adj_list;

    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (graph->visited[con_ver] == 0)
        {
            DFS(graph, stack, con_ver);
        }
        aux = aux->next;
    }
}

void wipe(GPH* graph, int numVertices)
{
    for (int i = 0; i < numVertices; i++) {
        graph->visited[i] = 0;
    }
}

void dfsUtil(GPH* graph, int numVertices, STK* stack, int src, int dest)
{
    wipe(graph, numVertices);
    DFS(graph, stack, src);

    int found = 0;
    for (int i = 0; i <= stack->position; i++)
    {
        if (stack->stackArray[i] == dest)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("Am gasit cale intre nodurile %d si %d.\n", src, dest);
    } else
    {
        printf("N-am gasit cale intre nodurile %d si %d.\n", src, dest);
    }
}

int main()
{
    int numVertices;
    int numEdges;
    int src;
    int dest;

    printf("Cate noduri are graful?\n");
    scanf("%d", &numVertices);

    printf("Cate muchii are graful?\n");
    scanf("%d", &numEdges);

    GPH* graph = createGraph(numVertices);
    STK* stack = createStack(2 * numVertices);


    insertEdges(numVertices, numEdges, graph);

    printf("Introdu sursa:\n");
    scanf("%d", &src);
    printf("Introdu destinatia:\n");
    scanf("%d", &dest);

    dfsUtil(graph, numVertices, stack, src, dest);


    return 0;
}
