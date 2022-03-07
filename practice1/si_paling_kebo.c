#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct pair_t {
    int id, time;
} Pair;

/* Struktur Node */

typedef struct pqueueNode_t {
    Pair data;
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
void pqueue_push(PriorityQueue *pqueue, int id, int value);
void pqueue_pop(PriorityQueue *pqueue);
Pair pqueue_top(PriorityQueue *pqueue);

/* Function definition below */

void pqueue_init(PriorityQueue *pqueue)
{
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, int id, int value)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
        (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->data.time = value;
    newNode->data.id = id;
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }

    if (value < pqueue->_top->data.time) {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else {
        while ( temp->next != NULL && 
                temp->next->data.time < value)
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

Pair pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->data;
    Pair ret;
    ret.id = -1;
    ret.time = 10000;
    return ret;
}

/* Struktur Node */

typedef struct stackNode_t {
    int data;
    struct stackNode_t *next;
} StackNode;

/* Struktur ADT Stack */

typedef struct stack_t {
    StackNode *_top;
    unsigned _size;
} Stack;

/* Function prototype */

void stack_init(Stack *stack);
bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, int value);
void stack_pop(Stack *stack);
int stack_top(Stack *stack);
unsigned stack_size(Stack *stack);

/* Function definition below */

void stack_init(Stack *stack) 
{
    stack->_size = 0;
    stack->_top = NULL;
}

bool stack_isEmpty(Stack *stack) {
    return (stack->_top == NULL);
}

void stack_push(Stack *stack, int value) 
{
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        newNode->data = value;
        
        if (stack_isEmpty(stack)) newNode->next = NULL;
        else newNode->next = stack->_top;

        stack->_top = newNode;
    }
}

void stack_pop(Stack *stack) 
{
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        free(temp);
        stack->_size--;
    }
}

int stack_top(Stack *stack) 
{
    if (!stack_isEmpty(stack)) 
        return stack->_top->data;
    return 0;
}

unsigned stack_size(Stack *stack) {
    return stack->_size;
}

int main(){
    int n, p, q;
    unsigned k;
    while (1) {
        PriorityQueue in, out;
        pqueue_init(&in);
        pqueue_init(&out);

        Stack s;
        stack_init(&s);

        scanf("%d %d", &n, &k);
        if (n == 0 && k == 0) break;
        
        bool r = false;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &p, &q);
            if (q < p) r = true;
            pqueue_push(&in, i, p);
            pqueue_push(&out, i, q);
        }

        while (!pqueue_isEmpty(&in) || !pqueue_isEmpty(&out)) {
            Pair tp = pqueue_top(&in), tq = pqueue_top(&out);
            if (tp.time < tq.time) {
                stack_push(&s, tp.id);
                pqueue_pop(&in);
                if (pqueue_top(&in).time == tp.time) r = true;
            }
            else if (tq.time < tp.time && stack_top(&s) == tq.id) {
                stack_pop(&s);
                pqueue_pop(&out);
                if (pqueue_top(&out).time == tq.time) r = true;
            }
            else if (tp.time == tq.time && tp.id != tq.id && stack_top(&s) == tq.id) {
                stack_pop(&s);
                pqueue_pop(&out);
                stack_push(&s, tp.id);
                pqueue_pop(&in);
                if (pqueue_top(&in).time == tp.time || pqueue_top(&out).time == tq.time) r = true;
            }
            else r = true;

            if (stack_size(&s) > k) r = true;
            if (r) break;
        }
        printf(r ? "Dah lah\n" : "Bagusla\n");
    }

    return 0;
}
