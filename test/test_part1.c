#include "../utilities.h"
#include "../lab4.h"

/** 
test hash functions
**/
int test_trivial_hash(){
	printf("\n=== Test: trivial hash =================\n\n");
	INT_HASH hash = trivial_hash(10, 8);
	printf("%ld\n", hash);
	printf("\n========== End of Test =================\n\n");
	if (hash != 2) return 0;
	return 1;
}

int test_pearson_hash(){
	printf("\n=== Test: Pearson hash =================\n\n");
	INT_HASH hash = pearson_hash(10, 8);
	printf("%ld\n", hash);
	printf("\n========== End of Test =================\n\n");
	if (hash != 7) return 0;
	return 1;
}


int test_fibonacci_hash(){
	printf("\n=== Test: Fibonacci hash ===============\n\n");
	int pass = 1;
	INT_HASH hash;

	hash = fibonacci_hash(10, 8);
	printf("%ld\n", hash);
	if (hash != 1) pass = 0;

	hash = fibonacci_hash(999999999, 8);
	printf("%ld\n", hash);
	if (hash != 0) pass = 0;

	hash = fibonacci_hash(999999999, W);
	printf("%ld\n", hash);
	if (hash != 69107783) pass = 0;
	
	printf("\n========== End of Test =================\n\n");
	return pass;
}


int main(){

	int all_pass = 1;
	
	if (test_trivial_hash()) printf("PASSED: Y\n");
	else{
		all_pass = 0;
		printf("PASSED: N\n");
	}

	if (test_pearson_hash()) printf("PASSED: Y\n");
	else{
		all_pass = 0;
		printf("PASSED: N\n");
	}

	if (test_fibonacci_hash()) printf("PASSED: Y\n");
	else{
		all_pass = 0;
		printf("PASSED: N\n");
	}

	if (all_pass) printf("\nCongratulations! Your part 1 solution passes all tests!\nHowever you are strongly encouraged to test your implementation\nmore thoroughly to make sure it passes all grading tests as well.\n\n");
	else printf("\nOne or more tests still don't work\n\n");

}
