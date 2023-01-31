#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int X;
    int T;
    struct node *next;
}Node;

typedef Node *Ptr_Node;

void allocation(Ptr_Node* ,char *);
void enqueue(Ptr_Node *, Ptr_Node *, Ptr_Node *);
void dequeue(Ptr_Node *, Ptr_Node *, Ptr_Node *);
void circular_enqueue(Ptr_Node *, Ptr_Node *, Ptr_Node *);
void circular_dequeue(Ptr_Node *, Ptr_Node *, Ptr_Node *);
void processor(Ptr_Node *, int);
void rotation_circular_queue(Ptr_Node *, Ptr_Node *);
void push(Ptr_Node *, Ptr_Node *);
void pop(Ptr_Node *);

int main(void)
{
    Ptr_Node head_queue = NULL, tail_queue = NULL, temp_node_queue = NULL;
    Ptr_Node head_circular_queue = NULL, tail_circular_queue = NULL, temp_node_circular_queue = NULL;
    Ptr_Node stack = NULL;
    char loader[15];
    int K;

    scanf("%d", &K);

    while(strspn(loader, "END") != 3) {
        scanf(" %14[^\n]", loader);

        if(strspn(loader, "LOAD") == 4) {
            allocation(&temp_node_queue, loader);
            enqueue(&head_queue, &tail_queue, &temp_node_queue);
        }
        else if(strspn(loader, "PROC") == 4) {
            if(head_circular_queue != NULL && head_circular_queue -> T == 0) {
                circular_dequeue(&head_circular_queue, &tail_circular_queue, &temp_node_circular_queue);
                push(&stack, &temp_node_circular_queue);
                temp_node_circular_queue = NULL;
            }

            if(head_queue != NULL) { 
                dequeue(&head_queue, &tail_queue, &temp_node_queue);
                circular_enqueue(&head_circular_queue, &tail_circular_queue, &temp_node_queue);
                temp_node_queue =  NULL;
            }
    
            if(head_circular_queue != NULL) {
                processor(&head_circular_queue, K);

                if(head_circular_queue -> T != 0) {   
                    rotation_circular_queue(&head_circular_queue, &tail_circular_queue);
                }
            } 
            else {
                printf("PROC -1 -1\n");
            }
        }
        else if(strspn(loader, "UNLD") == 4) {
            pop(&stack);
        }
    }

    return 0;
}

void allocation(Ptr_Node *temp_node_external, char *loader)
{
    Ptr_Node temp_node = (Ptr_Node) malloc(sizeof(Ptr_Node));

    if(temp_node != NULL) {
        temp_node -> X = strtol(strchr(loader, ' '), NULL, 10);
        temp_node -> T = strtol(strrchr(loader, ' '), NULL, 10);
        temp_node -> next = NULL;
        *temp_node_external = temp_node;
    }
    else {
        exit(1);
    }
}

void enqueue(Ptr_Node *head, Ptr_Node *tail, Ptr_Node *temp_node)
{
    if(*head == NULL) {
        *head = *temp_node;
    }
    else {
        (*tail) -> next = *temp_node;
    }

    *tail = *temp_node;
}

void dequeue(Ptr_Node *head, Ptr_Node *tail, Ptr_Node *temp_node)
{
    *temp_node = *head;
    *head = (*head) -> next;

    if(*head == NULL) {
        *tail = NULL;
    }
}

void circular_enqueue(Ptr_Node *head, Ptr_Node *tail, Ptr_Node *temp_node)
{
    if(*head == NULL) {
        *head = *temp_node;
    }
    else {
        (*tail) -> next = *temp_node;
    }

    *tail = *temp_node;
    (*tail) -> next = *head;
}

void circular_dequeue(Ptr_Node *head, Ptr_Node *tail, Ptr_Node *temp_node)
{
    *temp_node = *head;
    *head = (*head) -> next;
    (*tail) -> next = *head;

    if(*head == NULL) {
        *tail = NULL;
    }
    else if((*head) -> X == (*tail) -> X) {
        (*tail) -> next = NULL;
    }
}

void processor(Ptr_Node *head, int K)
{
    (*head) -> T -= K;
   
    if((*head) -> T < 0) {
        (*head) -> T = 0;
    }

    printf("PROC %d %d\n", (*head) -> X, (*head) -> T);
}

void rotation_circular_queue(Ptr_Node *head, Ptr_Node *tail)
{
    *tail = *head;
    *head = (*head) -> next;
}

void push(Ptr_Node *top, Ptr_Node *temp_node)
{
    (*temp_node) -> next = *top;
    *top = *temp_node; 

}

void pop(Ptr_Node *top)
{
    Ptr_Node temp_node;

    temp_node = *top;
    *top = (*top) -> next;

    printf("UNLD %d\n", temp_node -> X);

    free(temp_node);
}
