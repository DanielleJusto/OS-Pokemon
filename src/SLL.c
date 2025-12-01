#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next; // pointer to next
};

struct SLL{
    struct Node *head;
};

// struct HashTable{
// }; 

int 
test(){
    struct Node node1;
    struct Node node2;

    node1.data = 1;
    node2.data = 2;

    struct Node *temp;
    temp = &node2;

    node1->next = temp;

    printf("%d\n", node1.next->data);

    return 0;
}