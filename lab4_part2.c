#include "lab4.h"
#define NUM_HASH_FUNCS 3


HashTable *create_hash_table(int m, int mode){
/**
    create a new hash table of size 2^m and return the pointer to the newly created table.
    Fully initialize the state of the table.

    Sample IO

    HashTable* table0 = create_hash_table(1, CLOSED_ADDRESSING);
    print_status(table0);

	HashTable* table1 = create_hash_table(1, LINEAR_PROBING);
	print_status(table1);

	HashTable* table2 = create_hash_table(1, CUCKOO);
	print_status(table2);

    Stdout:
    Table capacity:    		2
    Table load:        		0
    Table load factor: 		0.00
	Mode:			   		closed

	Table capacity:         2
	Table load:             0
	Table load factor:      0.00
	Mode:                   linear

	Table capacity:         2
	Table load:        		0
	Table load factor:      0.00
	Mode:                   cuckoo

**/

    hash_funcs[0] = trivial_hash;
    hash_funcs[1] = pearson_hash;
    hash_funcs[2] = fibonacci_hash;

    HashTable* ht = malloc (sizeof(HashTable));
    if (ht){
        long int b = 1;
        for (long int i = 0; i < m; i ++){b = b * 2;}
        ht -> num_buckets = b;
        ht -> num_keys = 0;
        ht -> buckets = calloc (ht -> num_buckets, sizeof(Node*));
        ht -> mode = mode;
    }
    return ht;
}

void update_without_resize(PersonalData * data, HashTable *table) {
	/**
	Insert/update the data corresponding to SIN of data.
	Update all book-keeping information.
	**/
	INT_SIN SIN = data -> SIN;
    INT_HASH hash_num = (*hash_funcs[table -> mode])(SIN, table -> num_buckets);
    //printf("hash_num is %d \n", hash_num);

    if (table -> mode == CLOSED_ADDRESSING){
        if (table -> buckets[hash_num] == NULL){
            Node* entry = malloc(sizeof(Node));
            entry -> value = data;
            entry -> next = NULL;
            table -> buckets[hash_num] = entry;
            table -> num_keys += 1;
        }else{
            Node* curr = table -> buckets[hash_num];
            while (curr -> next || curr -> value -> SIN == SIN){
                if (curr -> value -> SIN == SIN){
                    curr -> value = data;
                    break;
                }else{
                    curr = curr -> next;
                }
            }
            if (curr -> value -> SIN != SIN){
                Node* entry = malloc(sizeof(Node));
                entry -> value = data;
                entry -> next = NULL;
                curr -> next = entry;
                table -> num_keys += 1;
            }
        }

    }

    if (table -> mode == LINEAR_PROBING){
        int bstar;
        for (long int p =0; p < table -> num_buckets; p++){
            bstar = (hash_num + p) % table -> num_buckets;
            if (table -> buckets[bstar] == NULL){
                Node* entry = malloc(sizeof(Node));
                entry -> value = data;
                entry -> next = NULL;
                table -> buckets[bstar] = entry;
                table -> num_keys += 1;
                return;
            }else if(table -> buckets[bstar] -> value -> SIN == SIN){
                table -> buckets[bstar] -> value = data;
                return;
            }
        }
    }

    if (table -> mode == QUADRATIC_PROBING){
        int bstar;
        for (long int p =0; p < table -> num_buckets; p++){
            bstar = (hash_num + p*p) % table -> num_buckets;
            if (table -> buckets[bstar] == NULL){
                Node* entry = malloc(sizeof(Node));
                entry -> value = data;
                entry -> next = NULL;
                table -> buckets[bstar] = entry;
                table -> num_keys += 1;
                return;
            }else if(table -> buckets[bstar] -> value -> SIN == SIN){
                table -> buckets[bstar] -> value = data;
                return;
            }
        }
    }

}

void update_key(PersonalData * data, HashTable **table){
	/**
	Using update_without_resize and resize_table,
	update the hash table while ensuring the final table's
	load factor does not exceed MAX_LOAD_FACTOR.

	Note that this function updates the pointer to the table with the
	return of resize_table and deletes the original table.

	Sample IO
	HashTable * table1 = create_hash_table(1, CLOSED_ADDRESSING);
	PersonalData data_a = {0, 'F', "Alice","Smith","XXX", "YYY", 1995, 12, 12};
	PersonalData data_b = {1, 'M', "Bob","Xu","XXX", "YYY", 1994, 12, 12};
	PersonalData data_c = {10, 'M', "Jeremy","Voyager","XXX", "YYY", 1994, 19, 12};
	update_key(&data_a, &table1);
	update_key(&data_b, &table1);
	update_key(&data_c, &table1);
	print_buckets(table1);

	PersonalData data1 = {2, 'F', "Alice", "Li", "XXX", "YYY", 1986, 1, 1};
	PersonalData data2 = {7, 'M', "Bob", "Kim", "XXX", "YYY", 1999, 5, 12};
	PersonalData data3 = {10, 'F', "Eve", "Pooh", "XXX", "YYY", 1993, 4, 20};
	HashTable* table2 = create_hash_table(3, LINEAR_PROBING);
	update_key(&data1, &table2);
	update_key(&data2, &table2);
	update_key(&data3, &table2);
	print_buckets(table2);

	Stdout:
	Bucket 0:    SIN: 000000000
	Bucket 1:    SIN: 000000001
	Bucket 2:    SIN: 000000010
	Bucket 3:
	Bucket 4:
	Bucket 5:
	Bucket 6:
	Bucket 7:

	Bucket   0:
	Bucket   1:     SIN:    2
	Bucket   2:     SIN:    7
	Bucket   3:
	Bucket   4:
	Bucket   5:     SIN:    10
	Bucket   6:
	Bucket   7:
	**/


    update_without_resize(data, *table);
    float load_factor = ((float)((*table) -> num_keys)) / (float)((*table) -> num_buckets);
    if (load_factor > MAX_LOAD_FACTOR){
        HashTable* temp = resize_table(*table);
        delete_table(*table);
        *table = temp;
    }
}

int delete_key(INT_SIN SIN, HashTable *table){
/**
	Delete key value, return 1 if successful,
	0 if key not in table - update book-keeping information.
	Ensure no memory leaks. Do not free memory that you did not allocate.

	Sample IO
	HashTable * table = create_hash_table(1, CLOSED_ADDRESSING);
	PersonalData data_a = {0, 'F', "Alice","Smith","XXX", "YYY", 1995, 12, 12};
	update_key(&data_a, table);
	delete_key(0, table);
	print_status(table);
	print_buckets(table);

	Stdout:
	Table capacity:    2
	Table load:        0
	Table load factor: 0.00
	Bucket 0:
	Bucket 1:
	Bucket 2:
	Bucket 3:
	Bucket 4:
	Bucket 5:
	Bucket 6:
	Bucket 7:

**/
    int state = 0;
    INT_HASH hash_num = (*hash_funcs[table -> mode])(SIN, table -> num_buckets);
    //printf("hash_num is %d \n", hash_num);

    if (table -> mode == CLOSED_ADDRESSING){
        Node* curr = table -> buckets[hash_num];
        while (curr != NULL){
            if (curr -> value -> SIN == SIN){
                state = 1;
                table -> buckets[hash_num] = curr -> next;
                free(curr);
                curr = NULL;
                table -> num_keys += -1;
                return state;
            }else if (curr -> next && curr -> next -> value -> SIN == SIN){
                state = 1;
                Node* temp = curr -> next;
                curr -> next = curr -> next -> next;
                free(temp);
                temp = NULL;
                table -> num_keys += -1;
                return state;
            }
			curr = curr -> next;
		}
        return state;
    }

    if (table -> mode == LINEAR_PROBING){
        int bstar;
        for (long int p =0; p < table -> num_buckets; p++){
            bstar = (hash_num + p) % table -> num_buckets;
            if (table -> buckets[bstar] && table -> buckets[bstar] -> value -> SIN == SIN){
                state = 1;
                free(table -> buckets[bstar]);
                table -> buckets[bstar] = NULL;
                table -> num_keys += -1;
                return state;
            }
        }
        return state;
    }

     if (table -> mode == QUADRATIC_PROBING){
        int bstar;
        for (long int p =0; p < table -> num_buckets; p++){
            bstar = (hash_num + p*p) % table -> num_buckets;
            if (table -> buckets[bstar] && table -> buckets[bstar] -> value -> SIN == SIN){
                state = 1;
                free(table -> buckets[bstar]);
                table -> buckets[bstar] = NULL;
                table -> num_keys += -1;
                return state;
            }
        }
        return state;
    }

}



PersonalData* lookup_key(INT_SIN SIN, HashTable *table){
	/**
	return pointer to the PersonalData struct associated with SIN.
	return NULL if the SIN is not in table.

	Sample IO
	HashTable * table = create_hash_table(1, CLOSED_ADDRESSING);
	PersonalData data = {8, 'F', "Alice","Xu", "AB12345", "99999-999-999999999999", 1960, 31, 12};
	update_key(&data, table);
	print_personal_data(lookup_key(data.SIN, table));

	Stdout:
	SIN:        		8
	Gender:     		F
	Name:        		Xu, Alice
	Passport #:    		AB12345
	Bank account #:		99999-999-999999999999
	Date of birth:		12-31-1960
	**/

    INT_HASH hash_num = (*hash_funcs[table -> mode])(SIN, table -> num_buckets);
    //printf("hash_num is %d \n", hash_num);
    PersonalData* ptr;

    if (table -> mode == CLOSED_ADDRESSING){
        Node* curr = table -> buckets[hash_num];
        while (curr){
            if (curr -> value -> SIN == SIN){
                ptr = curr -> value;
                return ptr;
            }
            curr = curr -> next;
        }
        return NULL;
    }

    if (table -> mode == LINEAR_PROBING){
        int bstar;
        for (long int p =0; p < table -> num_buckets; p++){
            bstar = (hash_num + p) % table -> num_buckets;
            if (table -> buckets[bstar] && table -> buckets[bstar] -> value -> SIN == SIN){
                ptr = table -> buckets[bstar] -> value;
                return ptr;
            }
        }
        return NULL;
    }

    if (table -> mode == QUADRATIC_PROBING){
        int bstar;
        for (long int p =0; p < table -> num_buckets; p++){
            bstar = (hash_num + p*p) % table -> num_buckets;
            if (table -> buckets[bstar] && table -> buckets[bstar] -> value -> SIN == SIN){
                ptr = table -> buckets[bstar] -> value;
                return ptr;
            }
        }
        return NULL;
    }




}




void delete_table(HashTable *table){
	/**
	Delete the table and ensure no memory leaks. Do NOT free memory that you
	did not allocate.

	Sample IO
	HashTable * table = create_hash_table(1, CLOSED_ADDRESSING);
	delete_table(table);
	**/

    for (long int i =0; i < table -> num_buckets; i++){
        Node* curr;
        while (curr = table -> buckets[i]){
            table -> buckets[i] = curr -> next;
            free(curr);
        }
        curr = NULL;
    }
    free (table -> buckets);
    table -> buckets = NULL;
    free(table);
    table = NULL;

}


HashTable *resize_table(HashTable *table){
	/**
	Return a pointer to a new table with size m+1, where
	the original table "table" has size 2^m.
	Delete the original table, ensure no memory leaks.
	Update all book-keeping information.

	SampleIO
	HashTable * table = create_hash_table(2, CLOSED_ADDRESSING);
	table = resize_table(table);
	print_status(table);

	Stdout:
	Table capacity:    8
	Table load:        0
	Table load factor: 0.00
	**/

	long int bnum = table -> num_buckets;
	long int m = 0;
    while (bnum != 1){
        bnum = bnum/2;
        m += 1;
    }
    HashTable* new_table = create_hash_table (m+1, table -> mode);

    for (INT_HASH b = 0; b < table -> num_buckets; b++){
		Node* curr = table -> buckets[b];
		while (curr != NULL){
		    update_without_resize(curr -> value, new_table);
			curr = curr -> next;
		}
    }
    //delete_table(table);
    return new_table;
}






/*
int main(){
    //gcc -o test2 lab4.h lab4_part1.c lab4_part2.c utilities.c utilities.h

/*
    HashTable* table0 = create_hash_table(3, 1);
    print_status(table0);

    PersonalData data0;
    data0.SIN = 10;
    data0.gender = 'M';

    PersonalData data1;
    data1.SIN = 2;
    data1.gender = 'M';


    PersonalData data2;
    data2.SIN = 2;
    data2.gender = 'F';

    PersonalData data3;
    data3.SIN = 26;
    data3.gender = 'M';

    update_without_resize(&data0, table0);
    update_without_resize(&data1, table0);
    update_without_resize(&data2, table0);
    update_without_resize(&data3, table0);


    print_buckets (table0);

    printf("\n");
    HashTable* new_table = resize_table (table0);
    print_buckets (new_table);

    delete_table (new_table);

	table0 = NULL;
	new_table = NULL;
*/

/*
int main(){
    PersonalData data1 = {131, 'F', "Alice", "Li", "XXX", "YYY", 1986, 1, 1};
	PersonalData data2 = {13953, 'M', "Bob", "Kim", "XXX", "YYY", 1999, 5, 12};
	PersonalData data3 = {175, 'F', "Eve", "Pooh", "XXX", "YYY", 1993, 4, 20};
    PersonalData data4 = {11, 'F', "Eve", "Pooh", "XXX", "YYY", 1993, 4, 20};
    PersonalData data5 = {11+16, 'F', "Eve", "Pooh", "XXX", "YYY", 1993, 4, 20};
    PersonalData data6 = {131, 'M', "Eve", "Pooh", "XXX", "YYY", 1993, 4, 20};
    PersonalData data7 = {7, 'M', "Eve", "Pooh", "XXX", "YYY", 1993, 4, 20};


	HashTable* table2 = create_hash_table(3, CLOSED_ADDRESSING);

	update_key(&data1, &table2);
	update_key(&data2, &table2);
	update_key(&data3, &table2);
    update_key(&data4, &table2);
    update_key(&data5, &table2);
    print_buckets(table2);

    PersonalData* f1 = lookup_key(131, table2);
    //print_personal_data(f1);

    update_key(&data6, &table2);

    PersonalData* f2 = lookup_key(131, table2);
    //print_personal_data(f2);

    printf("\n");

    int a = delete_key(131, table2);
    printf ("%d \n", a);
    print_buckets(table2);
    printf("\n");

    update_key(&data7, &table2);
    print_buckets(table2);

    delete_table(table2);
    table2 = NULL;

}
*/


