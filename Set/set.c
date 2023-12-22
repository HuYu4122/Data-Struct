#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define HASHMAP_SIZE 64
#define HASHMAP_SIZE_LIST 1

struct aiv_set_item
{
    const char *key;
    size_t key_len;
};

struct aiv_set
{
    struct aiv_set_item hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST];
};

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

int check_UniqueKey(struct aiv_set * set,  const char *key)
{
    for(size_t size = 0; size < HASHMAP_SIZE; size++)
    {
        for(size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
        {
            if(set->hashmap[size][i].key && set->hashmap[size][i].key == key)
            {
                printf("\n%s already added\n\n", set->hashmap[size][i].key);
                return -1;
            }
        }
    }
    return 0;
}

void aiv_set_insert(struct aiv_set *set, const char *key)
{
    if(check_UniqueKey(set, key))
    {
        return;
    }
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len == 0)
        {
            set->hashmap[index][i].key = key;
            set->hashmap[index][i].key_len = key_len;
            printf("- Added %s at index %llu slot %llu\n", key, index, i);
            return;
        }
    }

    printf("COLLISION! for %s (index %llu)\n", key, index);
}

void aiv_set_remove(struct aiv_set *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("%s [ %llu ] (index: %llu)\n", key, hash, index);

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len > 0)
        {
            if (set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                set->hashmap[index][i].key = NULL;
                set->hashmap[index][i].key_len = 0;
                return;
            }
        }
    }
}

void aiv_set_find(struct aiv_set *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf(" %s [ %llu ] (index: %llu)\n", key, hash, index);

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len > 0)
        {
            if (set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                printf("%s at index %llu slot %llu\n", key, index, i);
                return;
            }
        }
    }
}

void print_key_list(struct aiv_set * set)
{
    for(size_t size = 0; size < HASHMAP_SIZE; size++)
    {
        for(size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
        {
            if(set->hashmap[size][i].key)
            {
                printf("Key : %s\n", set->hashmap[size][i].key);
            }
        }
    }
}

int main(int argc, char **argv)
{
    struct aiv_set myset;
    memset(&myset, 0, sizeof(struct aiv_set));

    // Adding key
    printf("Adding key\n");
    aiv_set_insert(&myset, "Hello");
    aiv_set_insert(&myset, "Hello2");
    aiv_set_insert(&myset, "Test");
    aiv_set_insert(&myset, "Foobar");
    aiv_set_insert(&myset, "Foobar");
    aiv_set_insert(&myset, "XYZ");
    aiv_set_insert(&myset, "AAAAAA");
    aiv_set_insert(&myset, "AAAAAa");
    aiv_set_insert(&myset, "AAAAAa");

    // Finding key
    printf("\nFind key : ");
    aiv_set_find(&myset, "XYZ");

    //Remove key
    printf("\nRemove key : ");
    aiv_set_remove(&myset, "Hello2");

    // printf("\nCheck Unique Key");
    // check_UniqueKey(&myset, "asd");
    
    //Print Key List
    printf("\nPrint Key List\n");
    print_key_list(&myset);
    return 0;
}