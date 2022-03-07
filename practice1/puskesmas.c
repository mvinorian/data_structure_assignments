#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct patient_t {
    char name[10];
    int disease;
} Patient;

/* Struktur Node */

typedef struct pqueueNode_t {
    Patient data;
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
void pqueue_push(PriorityQueue *pqueue, char* name, int value);
void pqueue_pop(PriorityQueue *pqueue);
Patient  pqueue_top(PriorityQueue *pqueue);

/* Function definition below */

void pqueue_init(PriorityQueue *pqueue)
{
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, char* name, int value)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
        (PQueueNode*) malloc (sizeof(PQueueNode));
    pqueue->_size++;
    strcpy(newNode->data.name, name);
    newNode->data.disease = value;
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }

    if (value < pqueue->_top->data.disease ||
       (value == pqueue->_top->data.disease &&
        strcmp(name, pqueue->_top->data.name) < 0)) {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else {
        while ( temp->next != NULL && 
                temp->next->data.disease < value)
            temp = temp->next;
        while ( temp->next != NULL &&
                temp->next->data.disease == value &&
                strcmp(temp->next->data.name, name) < 0)
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

Patient pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->data;
    Patient ret;
    strcpy(ret.name, "");
    ret.disease = 10;
    return ret;
}

/* Struktur Node */

typedef struct queueNode_t {
    Patient data;
    struct queueNode_t *next;
} QueueNode;

/* Struktur ADT Queue */

typedef struct queue_t {
    QueueNode   *_front, 
                *_rear;
    unsigned _size;
} Queue;

/* Function prototype */

void queue_init(Queue *queue);
bool queue_isEmpty(Queue *queue);
void queue_push(Queue *queue, char* name, int value);
void queue_pop(Queue *queue);
Patient queue_front(Queue *queue);
int  queue_size(Queue *queue);

/* Function definition below */

void queue_init(Queue *queue)
{
    queue->_size = 0;
    queue->_front = NULL;
    queue->_rear = NULL;
}

bool queue_isEmpty(Queue *queue) {
    return (queue->_front == NULL && queue->_rear == NULL);
}

void queue_push(Queue *queue, char* name, int value)
{
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode) {
        queue->_size++;
        strcpy(newNode->data.name, name);
        newNode->data.disease = value;
        newNode->next = NULL;
        
        if (queue_isEmpty(queue))                 
            queue->_front = queue->_rear = newNode;
        else {
            queue->_rear->next = newNode;
            queue->_rear = newNode;
        }
    }
}

void queue_pop(Queue *queue)
{
    if (!queue_isEmpty(queue)) {
        QueueNode *temp = queue->_front;
        queue->_front = queue->_front->next;
        free(temp);
        
        if (queue->_front == NULL)
            queue->_rear = NULL;
        queue->_size--;
    }
}

Patient queue_front(Queue *queue)
{
    if (!queue_isEmpty(queue)) {
        return (queue->_front->data);
    }
    Patient ret;
    strcpy(ret.name, "");
    ret.disease = 10;
    return ret;
}

int queue_size(Queue *queue) {
    return queue->_size;
}

int main(){
    PriorityQueue pq;
    pqueue_init(&pq);
    Queue s;
    queue_init(&s);

    int n, q, d[4] = {0, 0, 0, 0};
    char name[10], disease[25];
    
    scanf("%d", &n);
    while (scanf(" %d", &q) != EOF) {
        int dr = 0;
        if (q == 1) {
            scanf("%s %s", name, disease);
            if (strcmp(disease, "pusingkebanyakantugas") == 0) {
                dr = 0;
                d[dr]++;
            }
            else if (strcmp(disease, "diare") == 0) {
                dr = 1;
                d[dr]++;
            }
            else if (strcmp(disease, "maag") == 0) {
                dr = 2;
                d[dr]++;
            }
            else if (strcmp(disease, "flu") == 0) {
                dr = 3;
                d[dr]++;
            }

            printf("Pasien atas nama %s terdaftar ke database.\n", name);
            if (n > 0) {
                queue_push(&s, name, dr);
                printf("Pasien atas nama %s langsung masuk.\n", name);
                n--;
            }
            else {
                pqueue_push(&pq, name, dr);
                printf("Pasien atas nama %s mengantri.\n", name);
            }
        }
        if (q == 2) {
            n++;
            Patient t = queue_front(&s);
            queue_pop(&s);
            printf("Pasien atas nama %s sudah selesai konsultasi mengenai ", t.name);
            switch (t.disease) {
                case 0:
                    printf("pusingkebanyakantugas.\n");
                    break;
                case 1:
                    printf("diare.\n");
                    break;
                case 2:
                    printf("maag.\n");
                    break;
                case 3:
                    printf("flu.\n");
                    break;
            }
            if (n > 0 && !pqueue_isEmpty(&pq)) {
                printf("Pasien atas nama %s masuk dari antrian.\n", pqueue_top(&pq).name);
                queue_push(&s, pqueue_top(&pq).name, pqueue_top(&pq).disease);
                pqueue_pop(&pq);
                n--;
            }
        }
    }

    printf("Data pasien hari ini:\n");
    if (d[1] > 0) printf("diare: %d.\n", d[1]);
    if (d[3] > 0) printf("flu: %d.\n", d[3]);
    if (d[2] > 0) printf("maag: %d.\n", d[2]);
    if (d[0] > 0) printf("pusingkebanyakantugas: %d.\n", d[0]);

    return 0;
}