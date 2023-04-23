#include <stdlib.h>
#include <stdio.h>

struct node {
    int vertice;
    struct node* next;
};

struct node* createNode(int v);

struct Graph {
    int numVertices;
    int* visited;
    struct node** adLists;
};

void DFS(struct Graph* graph, int vertice) {
    struct node* adList = graph->adLists[vertice];
    struct node* temp = adList;

    graph->visited[vertice] = 1;
    printf("Visited %d \n", vertice);

    while (temp != NULL) {
        int connectedVertice = temp->vertice;

        if (graph->visited[connectedVertice] == 0) {
            DFS(graph, connectedVertice);
        }
        temp = temp->next;
    }
}

struct node* createNode(int v) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertice = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    
    graph->numVertices = vertices;
    graph->adLists = malloc(vertices * sizeof(struct node*)); // Array of arrays
    graph->visited = malloc(vertices * sizeof(int));

    int i;

    for (i = 0; i < vertices; i++) {
        graph->adLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct node* newNode = createNode(dest);
    newNode->next = graph->adLists[src];
    graph->adLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adLists[dest];
    graph->adLists[dest] = newNode;
}

void printGraph(struct Graph* graph) {
  int v;
  for (v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adLists[v];
    printf("\n Adjacency list of vertex %d\n ", v);
    while (temp) {
      printf("%d -> ", temp->vertice);
      temp = temp->next;
    }
    printf("\n");
  }
}

int main() {
    struct Graph* graph = createGraph(9);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 0, 6);
    addEdge(graph, 6, 7);
    addEdge(graph, 7, 8);

    printGraph(graph);

    DFS(graph, 0);

    return 0;
}