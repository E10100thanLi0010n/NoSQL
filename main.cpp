


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h> //uint32_t

//const int listMapCap = 20;
//#define COLUMN_USER_SIZE 32
//#define COLUMN_EMAIL_SIZE 127

#define VALUE_STRING_MAX 100
#define LISTMAP_MAX 20
#define DATABASE_MAX 10
#define LISTNAME_MAX 20


#define CAPACITY 30



typedef struct 
{
    uint32_t key; //char* key;
    //void* value; 
    char* value;
    size_t value_size;
    char value_type;  //'S'=string 'N'=num, 'B'
}KeyValue;



typedef struct
{
    KeyValue** items;
    uint32_t size;
    size_t count;
    char* name;
}HashTable;





/*
struct Database {
    struct ListMap LM[DATABASE_MAX];
    size_t count;

};
*/





//CREATE :C
KeyValue* create_item(HashTable* hash,uint32_t key, char* value)
{
    //allocate memory
    KeyValue* newitem = (KeyValue*)malloc(sizeof(KeyValue));
    //caching failed
    if (newitem == NULL)
    {
        printf("create new item fail \n");
        return;
    }

    //Dynamical Memory Allocation
    if (newitem != NULL) 
    {

       // newitem->key = (char*)malloc(strlen(sizeof(key+1)));
        
        newitem->key = key;
        //newitem->value = (void*)malloc(strlen(value) + 1);

        newitem->value = value;


        /*if (newitem->value != NULL)
        {
            strcpy(newitem->value, value);
        }else //value fail
         {
            free(newitem);
            newitem == NULL;
        }*/

        
        
    }
    
    /*
    newitem->value = (void*)malloc(strlen(value) + 1);
    strcpy(newitem->key, key); 
    strcpy(newitem->value, value);
    */
    return newitem;
}

/*typedef struct
{
    KeyValue** items;
    uint32_t size;
    size_t count;

}HashTable;*/

HashTable* create_table(uint32_t size)
{
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));

    table->size = size;
    table->count = 0;

    table->items = (KeyValue**)calloc(table->size, sizeof(KeyValue*));

    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL;

    return table;
}
//FIXME
unsigned int hash_function(int key)
{
    unsigned int i = 0;
    //change to int 
    for (int j = 0; str[j]; j++) //str[j]=='\0'
        i += str[j];

    return i % CAPACITY;
}

//DELETE :D
void free_item(KeyValue* kv)
{
    //free(kv->key);
    free(kv->value);
    free(kv);
}

void free_table(HashTable* table)
{

    for (int i = 0; i < table->size; i++)
    {
        KeyValue* item = table->items[i];
        if (item != NULL) free(item);

    }

    free(table->items);
    free(table);
}


void print_table(HashTable* table)
{
    printf("----------hahtable---------\n");
    printf(table->name);

    for (int i = 0; i < table->size; i++)
    {

        if (table->items[i])
        {
            printf("index : %d ,key : %d ,value : %s \n",i,table->items[i]->key, table->items[i]->value);

        }
    }
    printf("-------------------\n");
}
//FIXME
void KV_collision(HashTable* table,uint32_t key)
{
    for(int i=0;i<;i++)



}


void insertKV(HashTable *table,uint32_t key,char* value)
{
    KeyValue* item = create_item(table,key, value);

    int index = hash_function(key);

    KeyValue* current_item = table->items[index];




    if (current_item==NULL)
    {

        if (table->count == table->size) //can't be inserted
        {
            printf("insert error : hashtable is full\n");
            free_item(item);
            return;
        }
        

    }
    else
    {
        //there has have same key in hash table
        KV_collision(table, key);
        return;

    }

    table->items[index] = item;
    table->count++;


}

//READ :D
char* search_item(HashTable* table, uint32_t key)
{

    int index = hash_function(key);
    if (table->items[index]->value==NULL)
    {
        printf("not exist \n");
        return NULL;

    }


    return table->items[index]->value;

}


/*
bool ListMap_insert(ListMap* collection, int key,char value[])
{

    if (collection->count ==LISTMAP_MAX)
    {

        return false;
    }
    size_t count = collection->count;

    collection->kvPairs[count].key = key;
    //collection->kvPairs[count].value = strdup(value);
    strcpy(collection->kvPairs[count].value,value);
    count++;



    return true;
}


*/


/*
//find the value of the key
char* ValueforKey(struct ListMap* collection, int key)
{
    char* value=NULL;

    for (size_t i = 0; i < collection->count && value == NULL; i++)
    {
        if (collection->kvPairs[i].key == key)
        {
            value = strdup(collection->kvPairs[i].value);
            return value;
 
        }

    }

    //return collection->kvPairs[i].value;
}


//update
void updateValue(struct ListMap* collection, int key)
{
    char *newstr=(char*)malloc(sizeof(char)*10);

    if (collection == NULL)
    {
        printf("there is no data in data table.\n");
        return;
    }

    for (size_t i = 0; i < collection->count; i++)
    {
        if (collection->kvPairs[i].key == key)
        {

            printf("enter your new value\n");
            scanf_s("%s",&newstr);
            strcpy(collection->kvPairs[i].value,newstr);
            printf("ok. your new data in %d is : %s\n", key, newstr);
            return;
        }

    }


}

void freeListMap(struct ListMap* collection)
{
    if (collection == NULL) return;

    for (size_t i = 0; i < collection->count; i++)
        free(collection->kvPairs[i].value);

    free(collection);
    printf("you have cleared all the data table \n");
}

*/

int main()
{
    int numbers_of_keys = 10;
    struct ListMap* mydata = (ListMap*)malloc(sizeof(struct key_value) * numbers_of_keys);


    //struct key_value *kv=(key_value* )malloc(sizeof(struct key_value)* numbers_of_keys);

/*
    if(mydata==NULL)
  {

      perror("nalloc");
      exit(EXIT_FAILURE);
  }
  */
    char a1[10] = "aaa";
    char* str1 = a1;
    //char* str2 = "4f4";
    if (ListMap_insert(mydata, 1, str1)) printf("%s has been stored in %d", str1, 1);


   // ListMap_insert(mydata, 3, str2);

    printf("you got %s \n", ValueforKey(mydata, 3));
    printf("\n\n");

    freeListMap(mydata);


    return 0;
}