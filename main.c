#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    struct node *next;
    int hash;
    int id;
    char name[20];
    char buffer[100];
    unsigned int timestamp;
    char acl;
    short flow;
    char *parent;
    void *fifo;
};

struct node *pair_filter(struct node *head) {
    if ( head == NULL ) return NULL;
    typedef struct node node_t;
    node_t * newhead = NULL;
    int index = 0;
    node_t * prevnode = NULL;
    for (node_t * current = head; current != NULL; current = current->next) {
        if ( index%2 == 0)
        {
            node_t * newnode = (node_t *)malloc(sizeof(node_t));
            //printf("Size of struct: %d\n", (int)sizeof(node_t));
            if ( newnode == NULL) return NULL;
            memcpy(newnode, current, sizeof(node_t));
            newnode->next = NULL;
            if ( newhead == NULL ) newhead = newnode;
            if ( prevnode != NULL) {
              prevnode->next = newnode;
            }
            prevnode = newnode;
        }
        index++;
    }
    return newhead;
}

int main()
{
    typedef struct node node_t;
    char * names[] = {"elem0", "elem1","elem2","elem3","elem4","elem5","elem6","elem7", "elem8","elem9"};
    node_t * head = NULL;
    for (int i=9; i >=0; i--) {
        node_t * newnode = (node_t *)malloc(sizeof(node_t));
        newnode->next = head;
        head = newnode;
        strcpy(newnode->name, names[i]);
    }
    printf("Elements in initial list\n");
    printf("************************\n");
    for (node_t * current = head; current != NULL; current = current->next) {
        printf("Element: %s\n", current->name);
    }
    node_t * head_pairlist = pair_filter(head);
    printf("Remaining elements in pair list\n");
    printf("*******************************\n");
    for (node_t * current = head_pairlist; current != NULL; current = current->next) {
        printf("Element: %s\n", current->name);
    }
    node_t * current = head;
    while ( current != NULL )
    {
        node_t * prev = current;
        current = current->next;
        free(prev);
    }
    current = head_pairlist;
    while ( current != NULL )
    {
        node_t * prev = current;
        current = current->next;
        free(prev);
    }
    return 0;
}
