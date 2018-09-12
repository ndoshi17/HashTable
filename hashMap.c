#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{

	int i;
	ht->table = (struct hashLink **) malloc(sizeof(struct hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(i = 0; i < tableSize; i++){
		ht->table[i] = 0;
	}
}

void freeMap (struct hashMap * ht)
{  
	int i;
	struct hashLink *temp;
	struct hashLink *temp2;
	for(i = 0; i < ht->tableSize; i++){
		temp = ht->table[i];
		while(temp != NULL){
			temp2 = temp->next;
			free(temp);
			temp = temp2;
		}
	}
	free(ht->table);
	ht->count=0;
	ht->table=0;
	ht->tableSize=0;	
}

/* Add an element to the Hash Table */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  

	int hash;
	int hashIdx;
	struct hashLink *newLink;

	if(HASHING_FUNCTION == 1) hash = stringHash1(k);
	else hash = stringHash2(k);
	
	hashIdx = (labs(hash) % ht->tableSize);

	
	newLink = (struct hashLink *) malloc(sizeof(struct hashLink));

	newLink->key = k;
	newLink->value = v;
	newLink->next = ht->table[hashIdx];

	ht->table[hashIdx] = newLink;
	ht->count++;

}



/* Returns a pointer to the value of element with key k in the Hash Table 
   If the element is not in the Hash Table, returns NULL */ 
ValueType* atMap (struct hashMap * ht, KeyType k)
{ 

	int hash;
	int hashIdx;
	struct hashLink *link;
	if(HASHING_FUNCTION == 1) hash = stringHash1(k);
	else hash = stringHash2(k);


	hashIdx = (labs(hash) % ht->tableSize);

	link = ht->table[hashIdx];
	while(link != 0){ 
		if(strcmp(k, link->key) == 0){
			return &(link->value);
		}
		link = link->next;
	}

	return 0;
	
}

int containsKey (struct hashMap * ht, KeyType k)
{  
	if (atMap(ht,k)==0){
		return 0;
	}else{
		return 1;
	}
}

void removeKey (struct hashMap * ht, KeyType k)
{  
	int bucket = stringHash2(k)%ht->tableSize;
	struct hashLink *cur; 
	struct hashLink *prev;  
	if(ht->table[bucket] == 0){
		return;
	}else{
		cur=ht->table[bucket];
		prev=ht->table[bucket];
		while(cur!=0){
			if(strcmp(cur->key,k)==0){
				if(cur==ht->table[bucket]){
					ht->table[bucket]=cur->next;
					
				}else{
				prev->next=cur->next;
				}
				free(cur);
				ht->count--;
				return;
			}else{
				prev=cur;
				cur=cur->next;
			} 
		}
	}
}

int sizeMap (struct hashMap *ht)
{  
	return ht->count;
}

int capacityMap(struct hashMap *ht)
{  
	return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{  
	int runner = 0;
	int i;
	for(i=0; i<ht->tableSize; i++){
		if(ht->table[i]==0){
			runner++;
		}
	}
	return runner;
}

float tableLoad(struct hashMap *ht)
{  
   return (float)sizeMap(ht)/(float)capacityMap(ht);
}
