#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct cow_t {
    int id, age, mass;
} Cow;

/* Struktur Node */

typedef struct pqueueNode_t {
    Cow data;
    struct pqueueNode_t *next;
} PQueueNode;

/* Struktur ADT PriorityQueue menggunakan Linked List */

// Prioritas default: nilai minimum
typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;

/* Function prototype */

void pqueue_init(PriorityQueue *pqueue);
bool pqueue_isEmpty(PriorityQueue *pqueue);
void pqueue_push(PriorityQueue *pqueue, int id, int age, int mass);
void pqueue_pop(PriorityQueue *pqueue);
int  pqueue_top(PriorityQueue *pqueue);

/* Function definition below */

void pqueue_init(PriorityQueue *pqueue)
{
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, int id, int age, int mass)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
        (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->data.id = id;
    newNode->data.age = age;
    newNode->data.mass = mass;
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }

    if (age > pqueue->_top->data.age ||
       (age == pqueue->_top->data.age &&
        mass > pqueue->_top->data.mass)) {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else {
        while ( temp->next != NULL &&
                temp->next->data.age > age)
            temp = temp->next;
        while ( temp->next != NULL &&
                temp->next->data.age == age &&
                temp->next->data.mass > mass)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void pqueue_pop(PriorityQueue *pqueue)
{
    if (!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
}

int pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->data.id;
    else return 0;
}

int main(){
    PriorityQueue pq;
    pqueue_init(&pq);

    int n, id, a, m, x;
    char s[10];
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        if (strcmp(s, "DAFTAR") == 0) {
            scanf("%d %d %d", &id, &a, &m);
            pqueue_push(&pq, id, a, m);
        }
        else if (strcmp(s, "BELI") == 0) {
            scanf("%d", &x);
            while (!pqueue_isEmpty(&pq) && x--) {
                pqueue_pop(&pq);
            }
        }
    }

    while (!pqueue_isEmpty(&pq)) {
        printf("%d ", pqueue_top(&pq));
        pqueue_pop(&pq);
    }
    
    return 0;
}