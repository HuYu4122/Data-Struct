#include <stddef.h>
#include <stdio.h>

#define AIV_LIST(x) &(x.list_item)

typedef struct aiv_list_item list_item;
typedef struct aiv_int_item int_item;

struct aiv_list_item
{
    struct aiv_list_item *next;
    unsigned int count;
};

struct aiv_int_item
{
    struct aiv_list_item list_item;
    int value;
};

struct aiv_list_item *aiv_list_get_tail(struct aiv_list_item *head)
{
    if(!head)
    {
        return NULL;
    }

    struct aiv_list_item *current_item = head;
    struct aiv_list_item *last_item = head;
    while(current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }

    return last_item;
};

struct aiv_list_item *aiv_list_append(struct aiv_list_item **head, struct aiv_list_item *item)
{
    struct aiv_list_item *tail = aiv_list_get_tail(*head);
    if(!tail)
    {
        *head = item;
        (*head)->count = 1;
    }
    else
    {
        tail->next = item;
        (*head)->count++;
    }
    item->next = NULL;
    return item;
};

struct aiv_list_item *aiv_list_pop(struct  aiv_list_item **head)
{
    if(!(*head))
    {
        return NULL;
    }

    struct aiv_list_item *current_head = *head;
    const unsigned int current_count = current_head->count;
    *head = (*head)->next;
    if(*head)
    {
        (*head)->count = current_count - 1;
    }

    current_head->next = NULL;
    return current_head;
};

struct aiv_list_item *aiv_list_remove(struct aiv_list_item **head, struct aiv_list_item *item)
{
    if(!(*head))
    {
        return NULL;
    }
    
    struct aiv_list_item *current_item = *head;
    if(current_item == item)
    {
        printf("\n\nItem Removed : %d\n", ((int_item*)current_item)->value);
        aiv_list_pop(head);
        return current_item;
    }
    else
    {
        for(;current_item != NULL; current_item = current_item->next)
        {
            if(current_item->next == item)
            {
                printf("\n\nItem Removed : %d\n", ((int_item*)current_item->next)->value);
                current_item->next = current_item->next->next;
                (*head)->count--;
            }
        }
    }
    return item;
};

struct aiv_list_item *reverse_list(struct aiv_list_item **head)
{
    if(!(*head))
    {
        return NULL;
    }
    
    struct aiv_list_item *current_head = *head;
    struct aiv_list_item *prevItem = NULL;
    struct aiv_list_item *nextItem = NULL;
    
    while(current_head)
    {
        nextItem = current_head->next;
        current_head->next = prevItem;
        prevItem = current_head;
        current_head = nextItem;
    }
    *head = prevItem;

    return prevItem;
}

unsigned int aiv_list_lenght(struct aiv_list_item *head)
{
    return head->count;
}

void list_print(struct aiv_list_item **head)
{
    struct aiv_list_item *current_item = *head;
    for(;current_item != NULL; current_item = current_item->next)
    {
        printf(" [ %d ] ", ((int_item*)current_item)->value);
    }
}

int main(int argc, char **argv)
{
    struct aiv_list_item *head = NULL;

    //Adding element in list
    printf("\nAdding Value in List\n");
    struct aiv_int_item int_item1;
    struct aiv_int_item int_item2;
    struct aiv_int_item int_item3;
    struct aiv_int_item int_item4;
    int_item1.value = 100;
    int_item2.value = 101;
    int_item3.value = 102;
    int_item4.value = 103;
    aiv_list_append(&head, AIV_LIST(int_item1));
    aiv_list_append(&head, AIV_LIST(int_item2));
    aiv_list_append(&head, AIV_LIST(int_item3));
    aiv_list_append(&head, AIV_LIST(int_item4));
    list_print(&head);

    //Reverse List
    printf("\n\nReverse List\n");
    reverse_list(&head);
    list_print(&head);

    //Remove Element inside list with value
    aiv_list_remove(&head, AIV_LIST(int_item4));
    list_print(&head);

    // printf("\n\nLenght : %d\n\n", head->count);
    
    return 0;
}