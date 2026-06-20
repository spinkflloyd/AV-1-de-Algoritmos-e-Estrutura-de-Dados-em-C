#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 10

typedef struct Stack {
 int data[MAX_STACK_SIZE];
} Stack;
Stack * stack_alloc()
{
 Stack *s = (Stack *)malloc(sizeof(Stack));
	s->data[0] = 0;
	return s;
}
void stack_free(Stack *s)
{
 free (s);
}
bool stack_isempty(Stack *s)
{
 return s->data[0] == 0;
}
bool stack_isfull(Stack *s)
{
 return s->data[0] == MAX_STACK_SIZE - 1;
}
void stack_push(Stack *s, int datum)
{
 if(stack_isfull(s)) return;
 s->data[0]++;
 s->data[s->data[0]] = datum;
}
int stack_pop(Stack *s)
{
 if(stack_isempty(s)) return -1;
 int val = s->data[s->data[0]];
 s->data[0]--;
 return val;
}

typedef struct Node {
 int datum;
 struct Node *next;
} Node;
Node * node_alloc()
{
 Node *n = (Node *)malloc(sizeof(Node));
	n->datum = 0;
	n->next = NULL;
	return n;
}
void node_free(Node *n)
{
 free(n);
}
typedef struct Queue {
 Node *front;
 Node *rear; 
} Queue;
Queue * queue_alloc()
{
 Queue *q = (Queue *)malloc(sizeof(Queue));
	q->front = q->rear = NULL;
	return q;
}
void queue_free(Queue *q)
{
 free (q);
}
bool queue_isempty(Queue *q)
{
 return q->front == NULL;
}
Node * queue_insert(Queue *q, int
datum)
{
 Node *n = node_alloc();
	n->datum = datum;
	if(q->rear == NULL){
		q->front = q->rear = n;
	} else {
		q->rear->next = n;
		q->rear = n;
	}
	return n;
}

int queue_remove(Queue *q)
{
 if(queue_isempty(q)) return -1;
	Node *temp = q->front;
	int val = temp->datum;
	q->front = q->front->next;
	if(q->front == NULL) q->rear = NULL;
	node_free(temp);
	return val;
}
void queue_print(Queue *q)
{
 printf("Queue: ");
 for (Node *n = q->front; n; n =
n->next) {
 printf("%02d -> ", n->datum);
 }
 printf("X\n");
}
Queue * queue_invert(Queue *q)
{
 Stack *s = stack_alloc();	
	
 for (Node *n = q->front; n != NULL; n = n->next){
	if(stack_isfull(s)) break;
		stack_push(s, n->datum);
 }
 
 Queue *inv = queue_alloc();
	while(!stack_isempty(s)){
		queue_insert(inv, stack_pop(s));
}
	stack_free(s);
	return inv;
}

int main(int argc, char *argv[])
{
 Queue *q, *qinv;

 q = queue_alloc();
 for (int i = 0; i < 8; i++) {
 queue_insert(q, i);
 }
 printf("Fila Original:\n");
queue_print(q);
 qinv = queue_invert(q);
 printf("Fila Invertida:\n");
queue_print(qinv);
 queue_free(qinv);
 while (!queue_isempty(q)) {
 queue_remove(q);
 }
 queue_free(q);

 q = queue_alloc();
 for (int i = 0; i < 15; i++) {
 queue_insert(q, i);
 }
 printf("Fila Original:\n");
queue_print(q);
 qinv = queue_invert(q);
 printf("Fila Invertida:\n");
queue_print(qinv);
 queue_free(qinv);
 queue_free(q);

return EXIT_SUCCESS;

}