#include <stdlib.h>
#include <stdio.h>

#define SIZE 40

struct queue {
    int items[SIZE];
    int front;
    int back;
};

struct queue* createQueue();
void enqueue(struct queue* q, int i);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);

struct node {
    int vertice;
    struct node* next;
};

struct node* createNode(int v);

struct Graph {
    int numVertices;
    int* visited; 
    struct node** adjList;
};

void BFS(struct Graph* graph, int startVertice) {
    struct queue* q = createQueue();

    graph->visited[startVertice] = 1;
    enqueue(q, startVertice);

    while (!isEmpty(q)) {
        printQueue(q);
        int currentVertice = dequeue(q);
        printf("\nVisited %d\n", currentVertice);

        struct node* temp = graph->adjList[currentVertice];

        while (temp) {
            int adjVertice = temp->vertice;

            if (graph->visited[adjVertice] == 0) {
                graph->visited[adjVertice] = 1;
                enqueue(q, adjVertice);
            }
            temp = temp->next;
        }
    }
}

struct node* createNode(int v) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertice = v;
    newNode->next = NULL;
    return newNode;
};

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    
    graph->numVertices = vertices;
    graph->adjList = malloc(vertices * sizeof(struct node*)); // Array of arrays 
    graph->visited = malloc(vertices * sizeof(int));

    int i;

    for (i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void printGraph(struct Graph* graph) {
  int v;
  for (v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adjList[v];
    printf("\n Adjacency list of vertex %d\n ", v);
    while (temp) {
      printf("%d -> ", temp->vertice);
      temp = temp->next;
    }
    printf("\n");
  }
}

struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->back = -1;
    return q;
}

int isEmpty(struct queue* q) {
    if (q->back == -1) {
        return 1;
    } else {
        return 0;
    }
}

void enqueue(struct queue* q, int value) {
    if (q->back == SIZE - 1) {
        printf("\nQueue is full!\n"); // Should make this error handling better
    } else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->back++;
        q->items[q->back] = value;
    }
}

int dequeue(struct queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("\nQueue is empty!\n"); // Should make this error handling better
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->back) {
            printf("\nResetting queue!");
            q->front = q->back = -1;
        }
    }
    return item;
}

void printQueue(struct queue* q) {
  int i = q->front;

  if (isEmpty(q)) {
    printf("Queue is empty");
  } else {
    printf("\nQueue contains \n");
    for (i = q->front; i < q->back + 1; i++) {
      printf("%d ", q->items[i]);
    }
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


    BFS(graph, 0);

    return 0;
}