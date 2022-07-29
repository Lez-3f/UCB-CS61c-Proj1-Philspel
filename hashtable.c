#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
HashTable *createHashTable(int size, unsigned int (*hashFunction)(void *),
                           int (*equalFunction)(void *, void *)) {
  int i = 0;
  HashTable *newTable = malloc(sizeof(HashTable));
  newTable->size = size;
  newTable->bucket_num = 0;
  newTable->data = malloc(sizeof(struct HashBucket *) * size);
  for (i = 0; i < size; ++i) {
    newTable->data[i] = NULL;
  }
  newTable->hashFunction = hashFunction;
  newTable->equalFunction = equalFunction;
  return newTable;
}

/*
 * This inserts a key/data pair into a hash table.  To use this
 * to store strings, simply cast the char * to a void * (e.g., to store
 * the string referred to by the declaration char *string, you would
 * call insertData(someHashTable, (void *) string, (void *) string).
 * Because we only need a set data structure for this spell checker,
 * we can use the string as both the key and data.
 */
void insertData(HashTable *table, void *key, void *data) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket location with table->hashFunction.
  // 2. Allocate a new hash bucket struct.
  // 3. Append to the linked list or create it if it does not yet exist.

  struct HashBucket * newBucket = (struct HashBucket *)malloc(sizeof(struct HashBucket));
  newBucket->data = (char *)malloc(60 * sizeof(char));
  strcpy(newBucket->data, (char*)data);
  newBucket->key = (char *)malloc(60 * sizeof(char));
  strcpy(newBucket->key, (char*)key);

  newBucket->next = NULL;

  unsigned int loc = table->hashFunction(key) % table->size;
  newBucket->next = table->data[loc];
  table->data[loc] = newBucket;

  // printf("insert_loc: %d, insert val:%s \n", loc, (char *)table->data[loc]->key);

  // int t = 0;
  // int bias_sqrt = 0;
  // int bias = 0;
  // while(1){
  //   unsigned int insert_loc = (hash_loc + bias) % table->size;
  //   if (table->data[insert_loc] == NULL){
  //     table->data[insert_loc] = newBucket;  //空位置,插入数据
  //     break;
  //   }
  //   else {
  //     t = t + 1;
  //     bias_sqrt = ((t + 1) >> 1);
  //     bias = (t % 2 == 0) ? (table->size - t * t) : (t * t);
  //   }
  // }
}

/*
 * This returns the corresponding data for a given key.
 * It returns NULL if the key is not found. 
 */
void *findData(HashTable *table, void *key) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket with table->hashFunction.
  // 2. Walk the linked list and check for equality with table->equalFunction.
  unsigned int loc = table->hashFunction(key) % table->size;
  struct HashBucket * p = table->data[loc];
  // printf("loc: %d\n", loc);
  // printf("%d", p==NULL);
  while(p){
    if (table->equalFunction(p->key, key)){
      return p->data;
    }
    p = p->next;
  }
  return NULL;


  // int t = 0;
  // int bias_sqrt = 0;
  // int bias = 0;
  // while(1){
  //   unsigned int current_loc = (hash_loc + bias) % table->size;
  //   if ((struct HashBucket *)table->data[current_loc] == NULL){
  //     //未找到
  //     return NULL;
  //   }
  //   if (table->equalFunction((struct HashBucket *)table->data[current_loc]->key, key)){
  //     //找到了
  //     return ((struct HashBucket *)table->data[current_loc])->data;
  //   }
  //   else {
  //     t = t + 1;
  //     bias_sqrt = ((t + 1) >> 1);
  //     bias = (t % 2 == 0) ? (table->size - t * t) : (t * t);
  //   }
  // }
}
