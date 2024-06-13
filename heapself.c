// sumedh ganpatye
// crated date 27/02/2024 17:43
// completed 28/02/2024 01:43 4 hours
// last modified fine details
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HEAPSIZE 10000
#define N 3
char heap[HEAPSIZE];

typedef struct heap_metadata
{
    int size;
    _Bool allocated;
    char name[N];
    struct heap_metadata *next;
} Metadata; // size = 16 (4+1+3+8)

void Initialise(Metadata *heap_ptr)
{
    printf("Size of Metadata : %d\n", sizeof(Metadata));
    heap_ptr->size = (HEAPSIZE - sizeof(Metadata));
    heap_ptr->allocated = 0;
    strcpy(heap_ptr->name, "XX");
    printf("Starting Index %d: \n", 0);
    printf("Ending Index %d: \n", sizeof(heap) - 1);
    printf("Heap Initialised\n");
    heap_ptr->next = NULL;
}

void Display()
{
    Metadata *temp = (void *)heap;
    int idx = sizeof(Metadata);
    printf("\nDisplaying all heap\n");
    printf("Name \t\t\t");
    printf("Size \t\t\t");
    printf("Status \n");
    while (temp != NULL)
    {
        printf("%s\t\t\t", temp->name);
        printf("%d\t\t\t", temp->size);
        if (temp->allocated == 1)
            printf("Allocated from %d to %d", idx, idx + temp->size - 1);
        else
            printf("Free ");

        printf("\n");
        idx += temp->size + sizeof(Metadata);
        temp = temp->next;
    }
    printf("\n");
}

void Allocate(int size_req, char n[N])
{
    Metadata *head = (void *)heap;
    Metadata *tail = (void *)heap;
    int index = sizeof(Metadata);

    while ((head != NULL) && ((head->allocated == 1) || (head->size < size_req)))
    {
        tail = head;
        head = head->next;
        index += tail->size + sizeof(Metadata);
    }
    if ((head->next == NULL) && (head->size < size_req))
    {
        printf("No free space left to allocate %d bytes of memory \n", size_req);
    }
    else
    {
        if (head->size == size_req + sizeof(Metadata))
        {
            head->size = size_req + sizeof(Metadata);
            head->allocated = 1;
            strcpy(head->name, n);
            printf("%d bytes Memory is allocated from Index %d to %d \n", size_req, index, index + size_req - 1);
        }
        else
        {
            Metadata *new_block = (void *)((void *)head + sizeof(Metadata) + size_req);
            new_block->size = head->size - size_req - sizeof(Metadata);
            new_block->allocated = 0;
            strcpy(new_block->name, "XX");
            new_block->next = head->next;

            head->next = new_block;
            head->allocated = 1;
            head->size = size_req;
            strcpy(head->name, n);
            printf("%d bytes memory is allocated from Index %d to %d\n", size_req, index, index + size_req - 1);
        }
    }
}

void Merge()
{
    Metadata *ptr = (void *)heap;
    _Bool ismergered = 0;
    while (ptr != NULL && ptr->next != NULL)
    {
        if (ptr->allocated == 0 && ptr->next->allocated == 0)
        {
            ptr->size += ptr->next->size + sizeof(Metadata);
            ptr->next = ptr->next->next;
            strcpy(ptr->name, "XX");
            ismergered = 1;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    if (ismergered)
        printf("Mergerd successfully...\n");
    else
        printf("No need for merging...\n");
}

void Free(char n[N])
{
    Metadata *mptr = (void *)heap;
    int idx = sizeof(Metadata);
    while (mptr != NULL && mptr->next != NULL && strcmp(mptr->name, n) != 0)
    {
        idx += sizeof(Metadata) + mptr->size;
        mptr = mptr->next;
    }

    if (mptr == NULL)
        printf("No such data found\n");
    else
    {
        mptr->allocated = 0;
        printf("%s freed at index %d\n", mptr->name, idx);
        strcpy(mptr->name, "XX");
        Merge();
    }
}
int main()
{
    // printf("Size of metadata :%d",sizeof(Metadata));
    Metadata *heap_ptr = (void *)heap;
    Initialise(heap_ptr);
    Display();

    // Allocate(100, "aa");
    // Allocate(200, "ab");
    // Allocate(300, "bb");
    // Allocate(400, "bc");
    // Display();

    Free("bb");
    Display();
    Free("ab");
    Display();
    Free("bc");
    Display();
    Free("aa");
    Display();

    int size, t = 1, option;
    char name_of_data[N];
    while (t != 0)
    {
        printf("\n1. Allocate memory\n");
        printf("2. Free\n");
        printf("3. Display Heap\n");
        printf("0.Exit\n");
        printf("Enter the number of operation you want to perform :");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("Enter number of bytes you want to enter :");
            scanf("%d", &size);
            printf("Enter name for this data in 2 letters :");
            scanf("%s", name_of_data);
            Allocate(size, name_of_data);
            break;
        case 2:
            printf("Enter name of data you want to delete :");
            scanf("%s", name_of_data);
            Free(name_of_data);
            break;
        case 3:
            Display();
            break;
        case 0:
            printf("Ending the programm...\n");
            t = 0;
            break;
        default:
            printf("Invalid input\n");
            break;
        }
    }

    return 0;
}
