#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h> //uint32_t
#include<stdbool.h>

//const int listMapCap = 20;
//#define COLUMN_USER_SIZE 32
//#define COLUMN_EMAIL_SIZE 127


//#define _CRT_SECURE_NO_WARNINGS




#define VALUE_MAX 100
#define HASH_MAX 100
//#define DATABASE_MAX 10
//#define LISTNAME_MAX 20



struct Key_Value
{
    int key;
    // char value[VALUE_MAX+1];
    char* value;
};

typedef struct LinkedList
{
    struct Key_Value* node;
    struct LinkedList* next;
}LinkedList;

typedef struct Hash
{
    //struct key_value kvPairs[HASH_MAX];
    struct Key_Value** KVPairs;
    size_t count;
    //char ListName[LISTNAME_MAX];
    int capacity;
    struct  LinkedList** overflow_buckets;
}Hash;


// hash function
int hash_function(struct Hash* hm, int key)
{
    int index;
    index = key % (hm->capacity);
    return index;
}

struct LinkedList** create_overbuck(struct Hash* hm)
{
    struct LinkedList** buckets = (struct LinkedList**)calloc(hm->capacity, sizeof(struct LinkedList*));

    for (int i = 0; i < hm->capacity; i++)
        buckets[i] = NULL;

    return buckets;

}

struct LinkedList* allocate_List()
{
    struct LinkedList* list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    return list;
}

struct LinkedList* insert_LinkedList(struct LinkedList* list, struct Key_Value* kv)
{
    struct LinkedList* head = allocate_List();

    //no node in list
    if (!list) 
    {
        head->node = kv;
        head->next = NULL;
        list = head;
        return list;
    }


    //overflow_bucket[index]!=NULL
    struct LinkedList* temp = list;
    while (temp->next)
    {
        temp = temp->next;
    }
    temp->node = kv;
    temp->next = NULL;
    return list;
}



struct Hash* create_table(int capacity)
{
    struct Hash* hm = (struct Hash*)malloc(sizeof(struct Hash));

    hm->count = 0;
    hm->capacity = capacity;
    hm->KVPairs = (struct Key_Value**)calloc(hm->capacity, sizeof(struct Key_Value*));

    for (int i = 0; i < hm->capacity; i++)
        hm->KVPairs[i] = NULL;

    hm->overflow_buckets = create_overbuck(hm);

    return hm;
}






struct Key_Value* create_KV(int key, char* value)
{
    struct Key_Value* newkv = (struct Key_Value*)malloc(sizeof(struct Key_Value));
    newkv->key = key;
    newkv->value = (char*)malloc(strlen(value) + 1);
    strcpy(newkv->value, value);

    return newkv;
}




/*
struct Key_Value* Remove_From_Linkedlist(struct LinkedList* list)
{
    //no kv in the list
    if(!list) return NULL;

    //if(!list->next) return NULL;


    struct LinkedList* temp=list;
    struct LinkedList* newnode=list->next;
    temp->next=NULL;

    list=newnode;
    struct Key_Value *kv=NULL;
    memcpy(temp->node,kv,sizeof(struct Key_Value));

    free(temp->node->value);
    free(temp->node);
    free(temp);






    return kv;
}
*/








// handling_cllision()
void handle_collision(struct Hash* hm, struct Key_Value* kv, unsigned int index)
{
    struct LinkedList* head = hm->overflow_buckets[index];

    if (head == NULL)
    {
        head = allocate_List();
        head->node = kv;
        head->next = NULL;
        return;

    }
    else
    {
        hm->overflow_buckets[index] = insert_LinkedList(head, kv);
        return;
    }

}



//insert
void Hash_insert(struct Hash* hm, int key, char* value)
{
    int index = hash_function(hm, key);
    //struct Key_Value* newKV=(struct Key_Value*)malloc(sizeof(struct Key_Value));
    struct Key_Value* newKV = create_KV(key, value);
    //struct Key_Value* currKV=hm->KVPairs[index];

    //if (hm->count ==hm->capacity) return ;

    if (hm->KVPairs[index] == NULL) //no KV in index
    {
        if (hm->count == hm->capacity)
        {
            printf("insert error: the hash table is full. \n");
            free(newKV);
            return;
        }
        hm->KVPairs[index] = newKV;
    }
    else //has been here, so use seperate chaiing
    {
        struct LinkedList* head = hm->overflow_buckets[index];

        if (head == NULL) // Key not found in the table
        {
            hm->overflow_buckets[index] = insert_LinkedList(head, newKV);

        }
        else
        {

            insert_LinkedList(head, newKV);
        }


    }

    /*
    hm->KVPairs[index]->key = key;
    strcpy(hm->KVPairs[index]->value,value);
    */
    hm->count++;


}



//search
struct Key_Value* search_KV(struct Hash* hm, int key)
{
    int index = hash_function(hm, key);
    //struct Key_Value* currKV=(struct Key_Value*)malloc(sizeof(struct Key_Value));
    struct LinkedList* head = hm->overflow_buckets[index];
    struct Key_Value* currKV = hm->KVPairs[index];


    if(currKV!=NULL)
    {
        if(currKV->key=key) return currKV;
        /*
        if(head==NULL) return NULL;
        currKV=head->node;
        head=head->next;
        
        */
    }
    
    while (head != NULL)
    {
        if (head->node->key == key) return head->node;
        head = head->next;
    }
    //printf("there is no such Key_Value in this Hash table. \n");
    return NULL;
}


//find the value of the key
char* ValueforKey(struct Hash* hm, int key)
{
    int index = hash_function(hm, key);
    struct Key_Value* currKV = search_KV(hm, key);
    if (currKV != NULL) return currKV->value;

    /*
    for (size_t i = 0; i < hm->capacity; i++)
    {
        if (hm->KVPairs[i]->key == key)
        {
            // value = strdup(hm->KVPairs[i]->value);
             //return value;
            return hm->KVPairs[i]->value;
        }
    }
    
    
    
    */
    printf("Sorry, there is no such Key_Value in the hash table.\n");
    return NULL;
}


//update
void updateValue(struct Hash* hm, int key)
{

    if (hm == NULL)
    {
        printf("there is no data in data table.\n");
        return;
    }

    char* newstr = NULL;
    int newstr_len = 100;
    newstr = (char*)malloc(sizeof(char) * newstr_len);

    if (newstr == NULL)
    {
        perror("memory allocation failed. \n");
        return;
    }

    struct Key_Value* currKV = search_KV(hm, key);

    if (currKV != NULL)
    {
        printf("enter your new value: ");
        if (fgets(newstr, newstr_len - 1, stdin) != NULL)
        {
            //len= the actul length of newstr
            size_t len = strlen(newstr);

            if (len > 0 && newstr[len - 1] == '\n') newstr[len - 1] = '\0';
            //put newstr into kvpairs[i].value
            if (strlen(newstr) < newstr_len)
            {
                strcpy(currKV->value, newstr);
                printf("updated data at index %d is : %s\n", key, currKV->value);
            }
            else
            {
                printf("your input value is too long to be stored in data table. \n");
            }
            free(newstr);
            return;
        }
        else
        {
            printf("input read failed.\n");
        }
    }


    for (int i = 0; i < hm->capacity; i++)
    {
        if (hm->KVPairs[i]->key == key)
        {
            printf("enter your new value\n");
            //redesign the length of newstr
            if (fgets(newstr, newstr_len - 1, stdin) != NULL)
            {
                //len= the actul length of newstr
                size_t len = strlen(newstr);

                if (len > 0 && newstr[len - 1] == '\n') newstr[len - 1] = '\0';
                //put newstr into kvpairs[i].value
                if (strlen(newstr) < newstr_len)
                {
                    strcpy(hm->KVPairs[i]->value, newstr);
                    printf("updated data at index %d is : %s\n", key, hm->KVPairs[i]->value);
                }
                else
                {
                    printf("your input value is too long to be stored in data table. \n");
                }

                free(newstr);
                return;
            }
            else
            {
                perror("input read failed. \n");
            }

        }
    }

    printf("key : %d not found in the hash table.\n", key);
    free(newstr);
}


void delete_KV(struct Hash* hm, int key)
{
    int index = hash_function(hm, key);
    struct Key_Value* kv = hm->KVPairs[index];
    struct LinkedList* head = hm->overflow_buckets[index];
    struct LinkedList* prev = NULL;


    /*
    struct Key_Value* currKV = search_KV(hm, key);

    if (currKV != NULL && currKV->key == key) //found in the search_KV
    {
        free(currKV->value);
        free(currKV);
        hm->KVPairs[index] = NULL;
        hm->count--;
        printf("deleted key_value with key %d from KVPairs", key);
        return;


    }
    */

    if (kv != NULL && kv->key == key) //found in KVPairs[index]
    {
        free(kv->value);
        free(kv);
        hm->KVPairs[index] = NULL; //FIXME:what about the leftover of overflow_buckets[index]
        hm->count--;
        printf("deleted key_value with key %d from KVPairs", key);
        return;
    }


    while (head != NULL)  
    {
        if (head->node->key == key)  //found somewhere in the overflow_buckets[index]
        {
            if (prev == NULL) //key in overflow_buckets[index],so prev=NULL
            {
                hm->overflow_buckets[index] = head->next;
            }
            else //other place
            {
                prev->next = head->next;
            }

            free(head->node->value);
            free(head->node);
            free(head);
            hm->count--;
            printf("deleted key_value with key %d from sepe chain", key);
            return;
        }

        prev = head;
        head = head->next;
    }

    printf("Key %d not found in the hash table.\n", key);
}

void free_overbuck(struct Hash* hm)
{
    struct LinkedList** buckets = hm->overflow_buckets;

    for (int i = 0; i < hm->capacity; i++)
        free_list(buckets[i]);

    free(buckets);
    hm->overflow_buckets = NULL;
}

//delete
void free_KV(struct Key_Value* kv)
{
    if (kv != NULL)
    {

        if (kv->value != NULL) 
        {
            free(kv->value);
            kv->value = NULL;
        }

    }

    //free(kv->value);
    free(kv);
}

void free_list(struct LinkedList* list)
{
    
    while (list)
    {
        struct LinkedList* temp = NULL;
        temp = list;
        //avoid Dangling Pointer ,so that segfault
        if (temp->node->value != NULL)
        {
            free(temp->node->value);
            temp->node->value = NULL;
        }
        free(temp->node);
        temp->node = NULL;
        free(temp);
        list = list->next;
    }
}

void free_Hash(struct Hash* hm)
{

    if (hm == NULL) return;

    for (int i = 0; i < hm->count; i++)
    {
        struct Key_Value* kv = hm->KVPairs[i];
        if(kv!=NULL)  
        {
            free_KV(hm->KVPairs[i]);
            hm->KVPairs[i] = NULL;
        }


        struct LinkedList* currlist = hm->overflow_buckets[i];
        free_list(hm->overflow_buckets[i]);
        hm->overflow_buckets[i] = NULL;
        /*while (currlist)
        {
            struct LinkedList* temp = currlist;
            currlist = currlist->next;
            free(temp->node->value);
            free(temp->node);
            free(temp);
        }*/
    }

    free_overbuck(hm);
    free(hm->KVPairs);
    hm->KVPairs = NULL;
    free(hm);
    hm = NULL;
    printf("you have cleared all the data table \n");
}




void show_Hash(struct Hash* hm)
{
    printf("\nHash Table\n--------------------------\n");

    for (int i = 0; i < hm->capacity; i++)
    {
        struct Key_Value* currKV = hm->KVPairs[i];
        struct  LinkedList* head = hm->overflow_buckets[i];
        if (currKV != NULL)
        {
            printf("index: %d, key: %d, value: %s\n", i, currKV->key, currKV->value);
        }

        while (head != NULL)
        {
            printf("index: %d, key: %d, value: %s\n", i, head->node->key, head->node->value);
            head = head->next;
        }

    }

    printf("this Hash table is over \n");
    printf("-------------\n");
}




int main()
{
    //int numbers_of_keys = 10;
    char* str1 = "wang";
    char* str2 = "ma";
    char* str102 = "tian";
    printf("create a table \n");
    struct Hash* table = create_table(100);

    printf("ok, now you can create kv in your hash table \n");

    Hash_insert(table, 1, str1);
    Hash_insert(table, 2, str2);
    Hash_insert(table, 102, str102);


    show_Hash(table);



    printf("valuefor key :1");
    printf("value in key 1: %s", ValueforKey(table, 1));

    printf("after delete 2 \n");
    delete_KV(table, 2);
    printf("\n");

    printf("\n");
    show_Hash(table);


    free_Hash(table);
    return 0;
}