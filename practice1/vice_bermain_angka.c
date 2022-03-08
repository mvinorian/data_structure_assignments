#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct snode_t {
    int data;
    struct snode_t *next;
} SListNode;

typedef struct slist_t {
    unsigned _size;
    SListNode *_head;
} SinglyList;

void slist_init(SinglyList *list) 
{
    list->_head = NULL;
    list->_size = 0;
}

bool slist_isEmpty(SinglyList *list) {
    return (list->_head == NULL);
}

void slist_pushBack(SinglyList *list, int value)
{
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        newNode->data = value;
        newNode->next = NULL;
        
        if (slist_isEmpty(list)) 
            list->_head = newNode;
        else {
            SListNode *temp = list->_head;
            while (temp->next != NULL) 
                temp = temp->next;
            temp->next = newNode;
        }
    }
}

int main(){
    SinglyList list;
    slist_init(&list);

    int b, x, n;
    scanf("%d", &b);
    for (int i = 0; i < b; i++) {
        scanf("%d", &x);
        slist_pushBack(&list, x);
    }
    scanf("%d", &n);
    
    int c = 0;
    SListNode *temp = list._head;
    while (temp->next != NULL) {
        if (temp->data % n == 0) {
            x = temp->data + ++c;
            if (temp->next != NULL && x == temp->next->data){
                printf("VICE!!!\n");
                return 0;
            }

            SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
            newNode->data = x;
            newNode->next = temp->next;
            temp->next = newNode;
        }
        temp = temp->next;
    }

    if (c == 0) {
        printf("VICE!!!\n");
        return 0;
    }

    if (c > n) {
        printf("#NICEVICE\n");
        SListNode *temp = list._head->next;
        while (temp->next != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
    }
    else {
        printf(":(\n");
        SListNode *temp = list._head;
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
    }
    printf("\n");

    return 0;
}