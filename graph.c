#include "graph.h"

void create_graph(graph *g)
{
    char input[INPUT_SIZE];
    fgets(input, sizeof(input), stdin);

    size_t vsz = 0;
    size_t esz = 0;
    state_e state = ENTER;
    int i;
    for(i = 0; input[i] != '#'; ++i)
    {
        switch(state)
	{
	case ENTER:
	    if(input[i] == '(')
	    {
		state = VERTEX;
		++vsz;
	    }	    
	    break;
	case LEAVE:
	    if(input[i+1] == '(')
		state = ENTER;
	    break;
	case BLANK:
	    if(input[i+1] != ' ')
		state = EDGE;
	    break;
	case VERTEX:
	{
	    char vertex[NAME_SIZE] = {0};
	    int j = 0;
	    while(input[i] != ' ')
	    {
		vertex[j] = input[i];
		++i;
		++j;
	    }
	    vertex[i] = '\0';
	    --i;
	    add_vertex(g, vertex);
	    state = BLANK;
	    break;
	}
	case EDGE:
	{
	    ++esz;
	    char edge[NAME_SIZE] = {0};
	    int j = 0;
	    while(input[i] != ' ' && input[i] != ')')
	    {
		edge[j] = input[i];
		++i;
		++j;
	    }
	    edge[i] = '\0';
	    if(input[i] == ' ')
		state = BLANK;
	    else if(input[i] == ')')
		state = LEAVE;
	    --i;

//	    vertex *tvx = g->vtable;
//	    int k;
//	    for(k = 1; k < vsz; tvx = tvx->next);
	    add_edge(g->vcurrent, edge);
	    break;
	}
	case END:
	    goto end;
	    break;
	default:
	    goto end;
	    break;
	}
    }
    g->v_size = vsz;
    g->e_size = esz;
end:
    ;
}
graph  *buy_graph()
{
    graph *g = (graph*)malloc(sizeof(graph));
    g->vtable = NULL;
    g->vcurrent = NULL;
    g->v_size = 0;
    g->e_size = 0;

    return g;
}
edge *buy_edge()
{
    edge *e = (edge*)malloc(sizeof(edge));
    e->next = NULL;
    return e;
}
vertex *buy_vertex()
{
    vertex *v = (vertex*)malloc(sizeof(vertex));
    v->next = NULL;
    v->edge = NULL;
    v->current = NULL;
    v->color = WHITE;
    v->distance = 0;
    v->s_time = 0;
    v->l_time = 0;

    return v;
}
edge *add_edge(vertex *v, char *name)
{
    edge *e = buy_edge();
    strcpy(e->name, name);
    
    if(v->edge == NULL)
    {
	v->edge = e;
	v->current = e;
    }
    else
    {
	v->current->next = e;
	v->current = e;
    }
    return e;
}
vertex *add_vertex(graph *g, char *name)
{
    vertex *v = buy_vertex();
    strcpy(v->name, name);

    if(g->vcurrent == NULL)
    {
	g->vtable = v;
	g->vcurrent = v;
    }
    else
    {
	g->vcurrent->next = v;
	g->vcurrent = v;
    }
    return v;
}
void print_vertex(vertex *v)
{
    printf("%s \n", v->name);
}
void print_edge(edge *e)
{
    printf("%s \n", e->name);
}

void BFS(graph *g, vertex *v)
{
    queue *q = buy_queue();
    print_vertex(v);
    enqueue_alledges(q, v);
    
    while(queue_empty(q) == 0)
    {
	edge *tmp = dequeue(q);
	vertex *found = lookup_vertex(g, tmp);
	if(tmp == NULL)
	    print_edge(tmp);
	else
	    BFS(g, found);
    }
    
}
void DFS(graph *g)
{
    
}

void shortest_path(graph *g);
void topo_sort(graph *g);

queue *buy_queue()
{
    queue *q = (queue*)malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;

    return q;    
}
queue_node *buy_queue_node()
{
    queue_node *qn = (queue_node*)malloc(sizeof(queue_node));
    qn->next = NULL;
    qn->e = NULL;
    return qn;
}
void enqueue(queue *q, edge *e)
{
    if(q == NULL)
	return;

    queue_node *qn = buy_queue_node();
    qn->e = e;
    if(q->head == NULL)
    {
	q->head = qn;
	q->tail = qn;
    }
    else
    {
	q->tail->next = qn;
	q->tail = qn;
    }
    q->size++;
}
edge *dequeue(queue *q)
{
    queue_node *t = q->head;
    if(q->head == q->tail)
    {
	q->head = q->tail = NULL;
    }
    else
	q->head = q->head->next;
    q->size--;
    
    return t->e;
}
vertex *lookup_vertex(graph *g, edge *e)
{
    vertex *table = g->vtable;

    while(table != NULL && (strcmp(table->name, e->name) != 0))
    {
	table = table->next;
    }
    
    if(table == NULL)
    {
	table = add_vertex(g, e->name);
    }
    
    return table;
}
void enqueue_alledges(queue *q, vertex *v)
{
    edge *e = v->edge;
    while(e != NULL)
    {
	enqueue(q, e);
	e = e->next;
    }
}
int queue_empty(queue *q)
{
    if(q->head == NULL)
	return 1;
    else
	return 0;
}

int main(int argc, char *argv[])
{
    graph *g = buy_graph();
    create_graph(g);
    BFS(g, g->vtable);
    return 0;
}
