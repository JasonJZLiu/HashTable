#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOAD_FACTOR 0.7
#define MAX_SIN 999999999
#define W ((unsigned long long int) 4294967296) // use at least 64 bits to represent (32 is not enough)
#define PHI 1.618033988749895

#define MAX_NAME_LEN 26
#define BANK_ACC_LEN 23
#define PASSPORT_LEN 9

typedef unsigned long int INT_SIN;
typedef unsigned long int INT_HASH;

static const unsigned char PEARSON_LOOKUP [256] = {
	82, 215, 8, 81, 193, 137, 31, 183, 75, 21, 169, 57, 224,
	184, 155, 69, 54, 192, 88, 225, 109, 99, 223, 213, 83, 25,
	252, 246, 217, 70, 250, 9, 64, 73, 142, 134, 179, 203, 103,
	3, 194, 123, 189, 232, 37, 185, 112, 177, 39, 174, 126, 218,
	205, 181, 170, 63, 125, 23, 24, 245, 212, 58, 206, 107, 172,
	87, 93, 45, 14, 208, 53, 106, 56, 196, 105, 198, 235, 147, 34,
	171, 124, 129, 86, 100, 226, 66, 132, 4, 98, 175, 201, 114,
	111, 12, 2, 195, 243, 136, 140, 127, 28, 97, 168, 1, 149, 10,
	182, 80, 159, 199, 94, 236, 40, 254, 144, 68, 19, 90, 65, 122,
	143, 117, 62, 176, 27, 178, 115, 158, 42, 96, 133, 219, 161,
	61, 20, 190, 166, 234, 230, 228, 154, 76, 253, 120, 74, 43,
	200, 95, 157, 207, 239, 41, 145, 116, 209, 13, 49, 11, 16,
	191, 162, 17, 139, 79, 220, 242, 26, 6, 165, 44, 241, 67, 22,
	77, 38, 138, 59, 221, 216, 152, 249, 186, 153, 187, 238, 128,
	210, 35, 248, 52, 247, 113, 150, 146, 0, 110, 48, 30, 92, 227,
	251, 91, 160, 233, 118, 164, 29, 60, 202, 151, 46, 229, 84, 15,
	237, 214, 180, 167, 72, 5, 211, 204, 163, 156, 173, 188, 33, 7,
	89, 131, 18, 104, 47, 101, 71, 130, 222, 240, 108, 78, 244, 135,
	121, 32, 119, 36, 141, 50, 255, 102, 231, 197, 51, 85, 55, 148};

// Personal data to be stored in the hash tables
typedef struct PersonalData{
	INT_SIN SIN; // 9-digit number
	char gender;
	char first_name[MAX_NAME_LEN];
	char last_name[MAX_NAME_LEN];
	char passport_num[PASSPORT_LEN];
	char bank_acc_num[BANK_ACC_LEN];
	int dob_year;
	int dob_month;
	int dob_day;
} PersonalData;



typedef struct Node {
	PersonalData * value; // the SIN number is the key.
	struct Node * next;
} Node;


typedef struct HashTable{
	INT_HASH num_buckets; // number of buckets in the buckets array
    INT_HASH num_keys; // number of keys stored in the hash table
	Node** buckets; // pointer to array of Node pointers
	// modes are: 0 for closed adressing (linked list chaining)
	// 1 for linear probing, 2 for quadratic probing, and 3 for cuckoo hashing
	int mode;
} HashTable;

void print_personal_data(PersonalData * data);
void print_buckets(HashTable * table);
void print_status(HashTable * table);

#endif






