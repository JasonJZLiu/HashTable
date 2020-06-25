#ifndef LAB4
#define LAB4

#include "utilities.h"
#define CLOSED_ADDRESSING 0
#define LINEAR_PROBING 1
#define QUADRATIC_PROBING 2
#define CUCKOO 3

INT_HASH trivial_hash(INT_SIN SIN, INT_HASH num_buckets);
INT_HASH pearson_hash(INT_SIN SIN, INT_HASH num_buckets);
INT_HASH fibonacci_hash(INT_SIN SIN, INT_HASH num_buckets);

INT_HASH (* hash_funcs[3])(INT_SIN SIN, INT_HASH num_buckets);

HashTable* create_hash_table(int m, int mode);
void update_key(PersonalData * data, HashTable **table);
int delete_key(INT_SIN SIN, HashTable *table);
PersonalData* lookup_key(INT_SIN SIN, HashTable *table);
void delete_table(HashTable *table);
HashTable *resize_table(HashTable *table);

PersonalData** parse_data(char* fn);
void counter_intelligence(char* load, char* update, char* validate, char* outfile);

#endif
