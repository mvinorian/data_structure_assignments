#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct queueNode_t {
    char name[5];
    int rank;
    struct queueNode_t *next, *prev;
} QueueNode;

typedef struct queue_t {
    QueueNode *_front, *_rear;
    unsigned _size;
} Queue;

void queue_init(Queue *queue)
{
    queue->_size = 0;
    queue->_front = NULL;
    queue->_rear = NULL;
}

bool queue_isEmpty(Queue *queue) {
    return (queue->_front == NULL && queue->_rear == NULL);
}

void queue_push(Queue *queue, char* name, int rank)
{
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode) {
        queue->_size++;
        strcpy(newNode->name, name);
        newNode->rank = rank;
        newNode->next = NULL;
        newNode->prev = NULL;
        
        if (queue_isEmpty(queue))                 
            queue->_front = queue->_rear = newNode;
        else {
            queue->_rear->next = newNode;
            newNode->prev = queue->_rear;
            queue->_rear = newNode;
        }
    }
}

void queue_rank(Queue *queue, char* name, int rank)
{
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode) {
        queue->_size++;
        strcpy(newNode->name, name);
        newNode->rank = rank;
        newNode->next = NULL;
        newNode->prev = NULL;
        
        if (queue_isEmpty(queue))                 
            queue->_front = queue->_rear = newNode;
        else {
            QueueNode *temp = queue->_rear;
            while (temp != NULL && temp->rank > newNode->rank) {
                temp = temp->prev;
            }
            while (temp != NULL && temp->rank == newNode->rank && strcmp(temp->name, newNode->name) > 0) {
                temp = temp->prev;
            }
            if (temp == NULL) {
                newNode->next = queue->_front;
                queue->_front->prev = newNode;
                queue->_front = newNode;
            }
            else if (temp == queue->_rear) {
                newNode->prev = queue->_rear;
                queue->_rear->next = newNode;
                queue->_rear = newNode;
            }
            else {
                newNode->next = temp->next;
                temp->next = newNode;
                newNode->prev = temp;
            }
        }
    }
}

void queue_pop(Queue *queue)
{
    if (!queue_isEmpty(queue)) {
        QueueNode *temp = queue->_front;
        queue->_front = queue->_front->next;
        free(temp);
        
        if (queue->_front == NULL) queue->_rear = NULL;
        else queue->_front->prev = NULL;
        queue->_size--;
    }
}

int queue_size(Queue *queue) {
    return queue->_size;
}

int main(){
    Queue q, r;
    int n, c, d[4];

    queue_init(&q);
    queue_init(&r);

    scanf("%d", &n);
    while (scanf("%d", &c) != EOF) {
        printf("%d %d %d\n", n, r._size, q._size);
        if (c == 2) {
            printf("Pasien atas nama %s sudah selesai konsultasi mengenai ", r._front->name);
            switch (r._front->rank) {
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
            queue_pop(&r);
            if (!queue_isEmpty(&q)) {
                queue_push(&r, q._front->name, q._front->rank);
                printf("Pasien atas nama %s masuk dari antrian.\n", q._front->name);
                queue_pop(&q);
            }
            else n++;
            continue;
        }

        int rank;
        char name[10], disease[30];
        scanf(" %s %s", name, disease);
        if (strcmp(disease, "pusingkebanyakantugas") == 0) {
            rank = 0;
            d[rank]++;
        }
        else if (strcmp(disease, "diare") == 0) {
            rank = 1;
            d[rank]++;
        }
        else if (strcmp(disease, "maag") == 0) {
            rank = 2;
            d[rank]++;
        }
        else if (strcmp(disease, "flu") == 0) {
            rank = 3;
            d[rank]++;
        }
        
        // queue_rank(&q, name, rank);
        printf("Pasien atas nama %s terdaftar ke database.\n", name);
        if (n > 0) {
            queue_push(&r, name, rank);
            // queue_pop(&q);
            n--;
            printf("Pasien atas nama %s langsung masuk.\n", name);
        }
        else {
            queue_rank(&q, name, rank);
            printf("Pasien atas nama %s mengantri.\n", name);
        }
    }

    printf("Data pasien hari ini:\n");
    if (d[3] > 0) printf("flu: %d.\n", d[3]);
    if (d[2] > 0) printf("maag: %d.\n", d[2]);
    if (d[1] > 0) printf("diare: %d.\n", d[1]);
    if (d[0] > 0) printf("pusingkebanyakantugas: %d.\n", d[0]);

    return 0;
}