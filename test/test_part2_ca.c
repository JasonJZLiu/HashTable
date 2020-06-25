#include "../utilities.h"
#include "../lab4.h"

// testing closed addressing hash table
// chaining with linked list

void test_create_table(){
	printf("\n== Test: create table of size 2 ========\n\n");
	HashTable * table;
	//closed addressing
	table = create_hash_table(1, CLOSED_ADDRESSING);
	print_status(table);
	print_buckets(table);
	delete_table(table);
	printf("\n========== End of Test =================\n\n");
}

int test_update_key_1(){
	printf("\n== Test: update key (new SIN) ==========\n\n");
	HashTable * table = create_hash_table(1, CLOSED_ADDRESSING);
	PersonalData data_a = {0, 'F', "Alice","Smith","XXX", "YYY", 1995, 12, 12};
	PersonalData data_b = {1, 'M', "Bob","Xu","XXX", "YYY", 1994, 12, 12};
	PersonalData data_c = {10, 'M', "Jeremy","Voyager","XXX", "YYY", 1994, 19, 12};


	update_key(&data_a, &table);
	print_status(table);
	printf("\n");
	update_key(&data_b, &table);
	print_status(table);
	printf("\n");
	update_key(&data_c, &table);
	print_status(table);
	printf("\n");
	print_buckets(table);
		
	int pass = 1;
	if (table->num_buckets != 8) pass = 0;
	if (table->buckets[0]->value->SIN != 0) pass = 0;
	if (table->buckets[1]->value->SIN != 1) pass = 0;
	if (table->buckets[2]->value->SIN != 10) pass = 0;
	if (table->num_keys != 3) pass = 0;

	delete_table(table);
		
	printf("\n========== End of Test =================\n\n");
	return pass;
}



int test_update_key_2(){

	printf("\n=== Test: update key (same SIN) ========\n\n");
	HashTable * table = create_hash_table(1, CLOSED_ADDRESSING);
	PersonalData data = {8, 'M', "Wolfgang","Supernova",
						 "AB12345", "99999-999-999999999999",
						 1960, 31, 12};
	PersonalData data_updated = {8, 'F', "Alexandra","Supernova",
								 "AB12345", "99999-999-999999999999",
								 1970, 31, 12};

	update_key(&data, &table);
	print_status(table);
    print_buckets(table);
	printf("\n");
	print_personal_data(table->buckets[0]->value);
	printf("\n");
	update_key(&data_updated, &table);
	print_status(table);
	printf("\n");
	print_personal_data(table->buckets[0]->value);
	printf("\n");

	int pass = 1;
	if (table->num_buckets != 2) pass = 0;
	if (table->num_keys != 1) pass = 0;
	
	delete_table(table);
	
	printf("\n========== End of Test =================\n\n");
	return pass;
}


int test_delete_key(){

	printf("\n===== Test: delete key =================\n\n");
	HashTable * table = create_hash_table(1, CLOSED_ADDRESSING);
	PersonalData data = {8, 'F', "Alice","Xu",
						 "AB12345", "99999-999-999999999999",
						 1960, 31, 12};
	PersonalData data_b = {9, 'M', "Jeffrey","Smith",
						 "AB12345", "99999-999-999999999999",
						 1990, 31, 12};
	
	update_key(&data, &table);
	print_status(table);
	printf("\n");
	print_buckets(table);
	printf("\n");
	int delete_data = delete_key(data.SIN, table);
	int delete_data_b = delete_key(data_b.SIN, table);
	print_status(table);
	printf("\n");
	print_buckets(table);
	printf("\n");
 
	int pass = 1;
	if (table->num_keys != 0) pass = 0;
	if (delete_data != 1) pass = 0;
	if (delete_data_b != 0) pass = 0;
	
	delete_table(table);
	
	printf("\n========== End of Test =================\n\n");
	return pass;
}



int test_lookup_key(){

	printf("\n== Test: lookup key ====================\n\n");
	HashTable * table = create_hash_table(1, CLOSED_ADDRESSING);
	PersonalData data = {8, 'F', "Alice","Xu",
						 "AB12345", "99999-999-999999999999",
						 1960, 31, 12};
	PersonalData data_b = {9, 'M', "Jeffrey","Smith",
						 "AB12345", "99999-999-999999999999",
						 1990, 31, 12};
	
	update_key(&data, &table);
	print_status(table);
	printf("\n");
	print_buckets(table);
	printf("\n");
	PersonalData * lookup_data = lookup_key(data.SIN, table);
	PersonalData * lookup_data_b = lookup_key(data_b.SIN, table);
	printf("\n");
	print_personal_data(lookup_data);
	printf("\n");
	print_personal_data(lookup_data_b);

	int pass = 1;
	if (lookup_data->SIN != data.SIN) pass = 0;
	if (lookup_data_b) pass = 0;
	
	delete_table(table);
	
	printf("\n========== End of Test =================\n\n");
	return pass;
}


int test_resize_table(){
	
	printf("\n======= Test: resize table =============\n\n");
 
	// should map to 1
	PersonalData data_1 = {1, 'F', "Alice","Xu",
						 "AB12345", "99999-999-999999999999",
						 1960, 31, 12};
	PersonalData data_5 = {5, 'M', "Jeffrey","Smith",
						 "AB32345", "99999-999-999999999999",
						 1990, 31, 12};
	PersonalData data_9 = {9, 'F', "Miranda","Scott",
						 "AB12345", "99999-999-999999999999",
						 1960, 31, 12};
	PersonalData data_13 = {13, 'M', "Leonard","King",
						 "AB12545", "99999-999-999999999999",
						 1950, 22, 12};
	PersonalData data_17 = {17, 'M', "Leonard","King",
						 "AB12355", "99999-999-999999999999",
						 1950, 22, 12};
	PersonalData data_0 = {0, 'F', "Miranda","King",
						 "AB82345", "99999-999-999999999999",
						 1950, 22, 12};
	PersonalData data_4 = {4, 'F', "Diana","King",
						 "AB19945", "99999-999-999999999999",
						 1950, 22, 12};
	
	// create a table of size 4 with this data
	HashTable * table = create_hash_table(2, CLOSED_ADDRESSING);


	update_key(&data_1, &table);
	table->num_keys = 0; // suppress resizing by update_key
print_buckets(table);
	update_key(&data_5, &table);
	table->num_keys = 0; // suppress resizing by update_key
print_buckets(table);
	update_key(&data_9, &table);
	table->num_keys = 0; // suppress resizing by update_key
	update_key(&data_13, &table);
	table->num_keys = 0; // suppress resizing by update_key
	update_key(&data_17, &table);
	table->num_keys = 0; // suppress resizing by update_key
	update_key(&data_0, &table);
	table->num_keys = 0; // suppress resizing by update_key
	update_key(&data_4, &table);
	table->num_keys = 0; // suppress resizing by update_key

	table->num_keys = 7; // assign the correct number of keys
	
	// display table before resizing
	print_status(table);
	printf("\n");
	print_buckets(table);
	printf("\n");
	// resize
	table = resize_table(table);
	printf("\n");
	// display table after resizing
	print_status(table);
	printf("\n");
	print_buckets(table);

	// check
	int pass = 1;
	if (table->num_keys != 7) pass = 0; 
	if (table->num_buckets != 8) pass = 0;
	if (!lookup_key(data_1.SIN, table)) pass = 0;
	if (!lookup_key(data_5.SIN, table)) pass = 0;
	if (!lookup_key(data_9.SIN, table)) pass = 0;
	if (!lookup_key(data_13.SIN, table)) pass = 0;
	if (!lookup_key(data_17.SIN, table)) pass = 0;
	if (!lookup_key(data_0.SIN, table)) pass = 0;
	if (!lookup_key(data_4.SIN, table)) pass = 0;
	
	delete_table(table);
	
	printf("\n========== End of Test =================\n\n");
	return pass;
}


int main(){

	int all_pass = 1;
	
	test_create_table();
	if (test_update_key_1()) printf("PASSED: Y\n");
	else{
		all_pass = 0;
		printf("PASSED: N\n");
	}
	if (test_update_key_2()) printf("PASSED: Y\n");
	else{
		all_pass = 0;
		printf("PASSED: N\n");
	}
	if (test_delete_key()) printf("PASSED: Y\n");
	else{
		all_pass = 0;
		printf("PASSED: N\n");
	}
	if (test_lookup_key()) printf("PASSED: Y\n");
	else{
		all_pass = 0;
		printf("PASSED: N\n");
	}
	if (test_resize_table()) printf("PASSED: Y\n");
	else{
		all_pass = 0;
		printf("PASSED: N\n");
	}
	
	if (all_pass) printf("\nCongratulations! Your part 2 solution passes all tests!\nHowever you are strongly encouraged to test your implementation\nmore thoroughly to make sure it passes all grading tests as well.\n\n");
	else printf("\nOne or more tests still don't work\n\n");
		
	return 0;	
}
