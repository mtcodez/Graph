#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include <stddef.h>
#include <malloc.h>
#include <string.h>
#define NAME_SIZE 5
#define INPUT_SIZE 100

typedef enum
{
    BEGIN = 0,
    ENTER,
    LEAVE,
    BLANK,
    VERTEX,
    EDGE,
    END
}state_e;

typedef enum
{
    WHITE = 0,
    GRAY,
    BLACK
}color_e;

typedef struct edge edge;
struct edge
{
    char name[NAME_SIZE];
    edge *next;
};

typedef struct vertex vertex;
struct vertex
{
    char name[NAME_SIZE];
    vertex *next;
    edge *edge;
    edge *current;
    color_e color;
    int distance;
    int s_time; /* start time */
    int l_time; /* leave time */
};

typedef struct graph graph;
struct graph
{
    vertex *vtable;
    vertex *vcurrent;
    size_t v_size; /* size of vertices */
    size_t e_size; /* size of edges */
};
///////
typedef struct queue_node queue_node;
struct queue_node
{
    edge *e;
    queue_node *next;
};

typedef struct queue
{
    queue_node *head;
    queue_node *tail;
    size_t size;
}queue;

void   create_graph(graph *g);
graph  *buy_graph();
edge   *buy_edge();
vertex *buy_vertex();
edge   *add_edge(vertex *v, char *name);
vertex *add_vertex(graph *g, char *name);
vertex *lookup_vertex(graph *g, edge *e);
void print_vertex(vertex *v);
void print_edge(edge *e);
void BFS(graph *g, vertex *v);
void DFS(graph *g);

void shortest_path(graph *g);
void topo_sort(graph *g);
/* queue */
queue      *buy_queue();
queue_node *buy_queue_node();
void        enqueue(queue *q, edge *e);
edge       *dequeue(queue *q);
int         queue_empty(queue *q);
void enqueue_alledges(queue *q, vertex *v);


#endif /* _GRAPH_H_ */
