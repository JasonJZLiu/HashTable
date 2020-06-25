#include "../utilities.h"
#include "../lab4.h"

/**
Testing part 3 of the lab (data loading)
**/

void test1(){
	printf("===== Test 1: simple parse data test =====\n");
	//PersonalData** data = parse_data("test_data_LOAD.txt");
	PersonalData** data = parse_data("test/test_data_UPDATE.txt");


}

void test2(){
	printf("===== Test 2: counter_intelligence =====\n");
	//char* load_fn = "test_data_LOAD.txt";
	//char* update_fn = "test_data_UPDATE.txt";
	//char* validate_fn = "test_data_VALIDATE.txt";

	char* load_fn = "test/test_data_LOAD.txt";
    char* update_fn = "test/test_data_UPDATE.txt";
    char* validate_fn = "test/test_data_VALIDATE.txt";


	char* spies_fn = "spies.txt";
	counter_intelligence(load_fn, update_fn, validate_fn, spies_fn);
}

void test3(){
	printf("===== Test 3: counter_intelligence full data =====\n");
	//char* load_fn = "full_data_LOAD.txt";
	//char* update_fn = "full_data_UPDATE.txt";
	//char* validate_fn = "full_data_VALIDATE.txt";

	char* load_fn = "test/full_data_LOAD.txt";
    char* update_fn = "test/full_data_UPDATE.txt";
    char* validate_fn = "test/full_data_VALIDATE.txt";

	char* spies_fn = "full_spies.txt";
	counter_intelligence(load_fn, update_fn, validate_fn, spies_fn);
}


int main(){
	test1();
	test2();
	test3();
	return 0;
}
