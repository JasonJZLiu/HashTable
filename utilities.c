#include "utilities.h"
#include <math.h>
#include <string.h>

void print_personal_data(PersonalData * data){
	if (!data){
		printf("PersonalData * to be printed is a NULL pointer\n");
		return;
	}
	printf("SIN:\t\t%ld\n", data->SIN);
	printf("Gender:\t\t%c\n", data->gender);
	printf("Name:\t\t%s, %s\n", data->last_name, data->first_name);
	printf("Passport #:\t%s\n", data->passport_num);
	printf("Bank account #:\t%s\n", data->bank_acc_num);	
	printf("Date of birth:\t%d-%d-%d\n", data->dob_day, data->dob_month, data->dob_year);
}


void print_status(HashTable* table){
	printf("Table capacity:\t\t%ld\n",  table->num_buckets);
	printf("Table load:\t\t%ld\n",  table->num_keys);
	printf("Table load factor:\t%.2f\n", (float)table->num_keys / table->num_buckets);
	char * mode;
	switch(table->mode){
		case 0: mode = "closed"; break;
		case 1: mode = "linear"; break;
		case 2: mode = "quadratic"; break;
		case 3: mode = "cuckoo"; break;
	}
	printf("Mode:\t\t\t%s\n", mode);
}


void print_buckets(HashTable * table){
	for (INT_HASH b = 0; b < table->num_buckets; b++){ 
		Node * bucket = table->buckets[b];
		printf("Bucket %ld:\t", b);
		while (bucket != NULL){
			if (bucket->value == NULL) printf(" - \t");
			else printf("SIN: %09ld\t", bucket->value->SIN);
			bucket = bucket->next;
		}
		printf("\n");
	}
}


