#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
    Stack s1, s2, s3;
    stack_init(&s1);
    stack_init(&s2);
    stack_init(&s3);

    char s[10];
    int n, x, c = 1;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s %d", s, &x);
        if (strcmp(s, "CETAK") == 0) {
            for (int j = 0; j < x; j++) {
                stack_push(&s1, c++);
            }
        }
        else if (strcmp(s, "TTD") == 0) {
            for (int j = 0; j < x; j++) {
                stack_push(&s2, stack_top(&s1));
                stack_pop(&s1);
            }
        }
        else if (strcmp(s, "SAMPUL") == 0) {
            for (int j = 0; j < x; j++) {
                stack_push(&s3, stack_top(&s2));
                stack_pop(&s2);
            }
        }
    }

    Stack t;
    stack_init(&t);

    printf("tumpukan 1: ");
    while (!stack_isEmpty(&s1)) {
        stack_push(&t, stack_top(&s1));
        stack_pop(&s1);
    }
    while (!stack_isEmpty(&t)) {
        printf("%d ", stack_top(&t));
        stack_pop(&t);
    }
    printf("\n");

    printf("tumpukan 2: ");
    while (!stack_isEmpty(&s2)) {
        stack_push(&t, stack_top(&s2));
        stack_pop(&s2);
    }
    while (!stack_isEmpty(&t)) {
        printf("%d ", stack_top(&t));
        stack_pop(&t);
    }
    printf("\n");

    printf("tumpukan 3: ");
    while (!stack_isEmpty(&s3)) {
        stack_push(&t, stack_top(&s3));
        stack_pop(&s3);
    }
    while (!stack_isEmpty(&t)) {
        printf("%d ", stack_top(&t));
        stack_pop(&t);
    }
    printf("\n");

    return 0;
}