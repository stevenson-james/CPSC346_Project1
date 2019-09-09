#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
};

/*
 * adds node to end of linked list with data = value
 * pre: head is a reference to a node pointer and value is an int
 * post: new node is added to end of linked list with
 *       ->next = NULL and ->data = value
 */
void pushToEnd(struct node** head, int value) {
    if (*head == NULL){
        *head = (struct node*) malloc(sizeof(struct node));
        (*head)->next = NULL;
        (*head)->data = value;
    }
    else {
        struct node* newNode = (struct node*) malloc(sizeof(struct node));
        newNode->next = NULL;
        newNode->data = value;
        struct node* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

/*
 * returns a new linked list with sorted lists list1 and list2 merged
 * pre: head1 and head2 are pointers to sorted linked lists
 * post: newHead is returned, pointing to the sorted combination of list1 and list2
 */
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

/*
 * returns the number of nodes in a linked list
 * pre: head points to a linked list
 * post: the size of the linked list is returned
 */
int getSize(struct node* head){
    int size = 0;
    while (head!=NULL) {
        head = head->next;
        size++;
    }
    return size;
}

/*
 * splits a linked list into a first and second half
 * pre: head points to the node to be split, secondHalf is a reference to
 *      the node pointer of the second half, and mid is half the size of
 *      head linked list
 * post: secondHalf points to the pointer of the second half of the list
 */
void split (struct node* head, struct node** secondHalf, int mid){
    for (int i = 1; i < mid; i++) {
        head = head->next;
    }
    *secondHalf = head->next;
    head->next = NULL;
}

/*
 * sorts a linked list using the mergeSort algorithm
 * pre: head is a linked list
 * post: sorted linked list of head is returned
 */
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

/*
 * prints out the values of a linked list
 * pre: head is a pointer to a linked list
 * post: data in linked list is printed to the screen
 */
void printList(struct node* head)
{
    while (head!=NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

/*
 * runs a test of merge and mergeSort functions
 * pre: N/A
 * post: mergeList = the sorted linked list of list1 and list2
 *       and is printed to the screen before and after sorting
 */
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
    printf("Original list: \n");
    printList(mergeList);

    mergeList = mergeSort(mergeList, getSize(mergeList));
    printf("Sorted list (using merge sort): \n");
    printList(mergeList);
    return 0;
}
