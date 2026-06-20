#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define REQUEST_MESSAGE_MAX_LENGTH 10

typedef enum RequestPriority {
    RP_LOW, RP_MEDIUM, RP_HIGH
} RequestPriority;

typedef struct Request {
    RequestPriority priority;
    char message[REQUEST_MESSAGE_MAX_LENGTH];
} Request;

Request *request_alloc(RequestPriority priority, char *message)
{
    Request *r = (Request *)malloc(sizeof(Request));
    r->priority = priority;
    strncpy(r->message, message, REQUEST_MESSAGE_MAX_LENGTH - 1);
    r->message[REQUEST_MESSAGE_MAX_LENGTH - 1] = '\0';
    return r;
}

void request_free(Request *r)
{
    free(r);
}

typedef struct Node {
    Request      *request;
    struct Node  *left;
    struct Node  *right;
} Node;

Node *node_alloc()
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->request = NULL;
    n->left    = NULL;
    n->right   = NULL;
    return n;
}

void node_free(Node *n)
{
    free(n);
}

typedef struct Queue {
    Node *front;
    Node *rear;
    int   size;
} Queue;

Queue *queue_alloc()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size  = 0;
    return q;
}

bool queue_isempty(Queue *pq)
{
    return pq->front == NULL;
}

Request *queue_remove(Queue *pq);

void queue_free(Queue *pq)
{
    while (!queue_isempty(pq)) {
        Request *r = queue_remove(pq);
        request_free(r);
    }
    free(pq);
}

void queue_insert(Queue *q, Request *r)
{
    Node *n = node_alloc();
    n->request = r;

    if (q->rear == NULL) {
        q->front = q->rear = n;
    } else {
        n->left        = q->rear;
        q->rear->right = n;
        q->rear        = n;
    }
    q->size++;
}

Request *queue_remove(Queue *pq)
{
    if (queue_isempty(pq)) return NULL;

    Node *best = pq->front;
    for (Node *cur = pq->front->right; cur != NULL; cur = cur->right) {
        if (cur->request->priority > best->request->priority) {
            best = cur;
        }
    }

    if (best->left != NULL) {
        best->left->right = best->right;
	} else {
        pq->front = best->right;
	}
    if (best->right != NULL){
        best->right->left = best->left;
    } else {
        pq->rear = best->left;
	}
    Request *r = best->request;
    node_free(best);
    pq->size--;
    return r;
}

void queue_print(Queue *pq)
{
    printf("Queue: X <-> ");
    for (Node *n = pq->front; n; n = n->right) {
        Request *r = n->request;
        printf("[%6s, %10s] <-> ",
               (r->priority == RP_HIGH)   ? "HIGH"   :
               (r->priority == RP_MEDIUM) ? "MEDIUM" : "LOW",
               r->message);
    }
    printf("X\n");
}

int main(int argc, char *argv[])
{
    Queue *pq = queue_alloc();

    queue_insert(pq, request_alloc(RP_MEDIUM, "msg1"));
    queue_insert(pq, request_alloc(RP_MEDIUM, "msg2"));
    queue_insert(pq, request_alloc(RP_LOW,    "msg3"));
    queue_insert(pq, request_alloc(RP_LOW,    "msg4"));
    queue_insert(pq, request_alloc(RP_HIGH,   "msg5"));
    queue_insert(pq, request_alloc(RP_LOW,    "msg6"));
    queue_insert(pq, request_alloc(RP_MEDIUM, "msg7"));
    queue_insert(pq, request_alloc(RP_HIGH,   "msg8"));
    queue_print(pq);

    while (!queue_isempty(pq)) {
        Request *r = queue_remove(pq);
        printf("REQUEST: [%6s, %10s]\n",
               (r->priority == RP_HIGH)   ? "HIGH"   :
               (r->priority == RP_MEDIUM) ? "MEDIUM" : "LOW",
               r->message);
        request_free(r);
    }

    queue_insert(pq, request_alloc(RP_MEDIUM, "msg1"));
    queue_insert(pq, request_alloc(RP_MEDIUM, "msg2"));
    queue_insert(pq, request_alloc(RP_LOW,    "msg3"));
    queue_insert(pq, request_alloc(RP_LOW,    "msg4"));
    queue_insert(pq, request_alloc(RP_HIGH,   "msg5"));
    queue_insert(pq, request_alloc(RP_LOW,    "msg6"));
    queue_insert(pq, request_alloc(RP_MEDIUM, "msg7"));
    queue_insert(pq, request_alloc(RP_HIGH,   "msg8"));
    queue_print(pq);

    while (!queue_isempty(pq)) {
        Request *r = queue_remove(pq);
        printf("REQUEST: [%6s, %10s]\n",
               (r->priority == RP_HIGH)   ? "HIGH"   :
               (r->priority == RP_MEDIUM) ? "MEDIUM" : "LOW",
               r->message);
        request_free(r);
    }

    queue_free(pq);

    return EXIT_SUCCESS;
}