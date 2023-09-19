


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h> //uint32_t

//const int listMapCap = 20;
//#define COLUMN_USER_SIZE 32
//#define COLUMN_EMAIL_SIZE 127

#define VALUE_MAX 32
#define LISTMAP_MAX 20
#define DATABASE_MAX 10
#define LISTNAME_MAX 20

/*
typedef struct {

    uint32_t id;
    char username[COLUMN_USER_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];

}Row;

*/




struct key_value
{
    uint32_t key;
    char value[VALUE_MAX+1];


};




struct ListMap
{
    struct key_value kvPairs[LISTMAP_MAX];
    size_t count;
    char ListName[LISTNAME_MAX];
};

/*
struct Database {
    struct ListMap LM[DATABASE_MAX];
    size_t count;

};
*/

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