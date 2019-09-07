#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
};

void printList(struct node* head);

//add to end of linked list
void push(struct node** start, int value) {
    if (*start == NULL){
        *start = (struct node*) malloc(sizeof(struct node));
        (*start)->next = NULL;
        (*start)->data = value;
    }
    else {
        struct node* newnode = (struct node*) malloc(sizeof(struct node));
        newnode->next = NULL;
        newnode->data = value;
        struct node* temp = *start;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newnode;
    }
}

struct node* merge(struct node* head1, struct node* head2){
    struct node* newhead = NULL;
    struct node* temp1 = head1;
    struct node* temp2 = head2;
    while(!(temp1 == NULL && temp2 == NULL))
    {
        if(temp1 == NULL) {
            push(&newhead, temp2->data);
            temp2 = temp2->next;
        }
        else if (temp2 == NULL) {
            push(&newhead, temp1->data);
            temp1 = temp1->next;
        }
        else if (temp1->data >= temp2->data){
            push(&newhead, temp2->data);
            temp2 = temp2->next;
        }
        else {
            push(&newhead, temp1->data);
            temp1 = temp1->next;
        }

    }
    return newhead;
}

int getSize(struct node* head){
    int size = 0;
    while (head!=NULL)
    {
        head = head->next;
        size++;
    }
    return size;
}
void split (struct node* head, struct node** first, struct node** second, int mid){
    for (int i = 1; i < mid; i++) {
        head = head->next;
    }
    *second = head->next;
    head->next = NULL;
}

struct node* mergeSort(struct node* head, int size)
{
    struct node* first = head;
    struct node* second = NULL;
    int mid = size / 2;

    if (size == 0 || size == 1) {
        return head;
    }
    split(head, &first, &second, mid);

    first = mergeSort(first, getSize(first));
    second = mergeSort(second, getSize(second));

    return merge(first, second);
}
void printList(struct node* head)
{
    while (head!=NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}


int main()
{
    struct node* list1 = NULL;
    struct node* list2 = NULL;
    struct node* mainlist = NULL;
    push(&list1, 10);
    push(&list1, 9);
    push(&list2, 11);
    push(&list2, 8);
    push(&list2, 7);
    mainlist = merge(list1, list2);
    printList(mainlist);
    mainlist = mergeSort(mainlist, getSize(mainlist));
    printList(mainlist);
    return 0;
}
