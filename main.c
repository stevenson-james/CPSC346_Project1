#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
};

//add to end of linked list
void pushToEnd(struct node** head, int value) {
    if (*head == NULL){
        *head = (struct node*) malloc(sizeof(struct node));
        (*head)->next = NULL;
        (*head)->data = value;
    }
    else {
        struct node* newnode = (struct node*) malloc(sizeof(struct node));
        newnode->next = NULL;
        newnode->data = value;
        struct node* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newnode;
    }
}

struct node* merge(struct node* head1, struct node* head2){
    struct node* newHead = NULL;
    while(!(head1 == NULL && head2 == NULL))
    {
        if(head2 == NULL) {
            pushToEnd(&newHead, head1->data);
            head1 = head1->next;
        }
        else if (head1 == NULL) {
            pushToEnd(&newHead, head2->data);
            head2 = head2->next;
        }
        else if (head1->data >= head2->data){
            pushToEnd(&newHead, head2->data);
            head2 = head2->next;
        }
        else {
            pushToEnd(&newHead, head1->data);
            head1 = head1->next;
        }

    }
    return newHead;
}

int getSize(struct node* head){
    int size = 0;
    while (head!=NULL) {
        head = head->next;
        size++;
    }
    return size;
}
void split (struct node* head, struct node** secondHalf, int mid){
    for (int i = 1; i < mid; i++) {
        head = head->next;
    }
    *secondHalf = head->next;
    head->next = NULL;
}

struct node* mergeSort(struct node* head, int size)
{
    struct node* firstHalf = head;
    struct node* secondHalf = NULL;
    int mid = size / 2;

    if (size == 0 || size == 1) {
        return head;
    }

    split(head, &secondHalf, mid);

    firstHalf = mergeSort(firstHalf, getSize(firstHalf));
    secondHalf = mergeSort(secondHalf, getSize(secondHalf));

    return merge(firstHalf, secondHalf);
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
    struct node* mergeList = NULL;
    pushToEnd(&list1, 10);
    pushToEnd(&list1, 9);
    pushToEnd(&list2, 11);
    pushToEnd(&list2, 8);
    pushToEnd(&list2, 7);
    mergeList = merge(list1, list2);
    printList(mergeList);
    mergeList = mergeSort(mergeList, getSize(mergeList));
    printList(mergeList);
    return 0;
}
