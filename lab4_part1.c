#include "lab4.h"
#include <math.h>

INT_HASH trivial_hash(INT_SIN SIN, INT_HASH num_buckets) {
	/**
	   return the hash of SIN scaled to num_buckets

	   Sample IO
	   printf(“%ld”, trivial_hash(10, 8));

	   stdout:
	   2
	**/

    return (INT_HASH)(SIN % num_buckets);
}


INT_HASH pearson_hash(INT_SIN SIN, INT_HASH num_buckets) {
	/**
	   return the hash of SIN scaled to num_buckets

	   Sample IO
	   printf(“%ld”, pearson_hash(10, 8))

	   stdout:
	   7

	**/
    int h = 0;
    for (SIN; SIN > 0; SIN = SIN/10){
        h = PEARSON_LOOKUP [((SIN % 10)+48) ^ h];
    }
    return (INT_HASH)h % num_buckets;

}


INT_HASH fibonacci_hash(INT_SIN SIN, INT_HASH num_buckets) {
	/**
	return the hash of SIN scaled to num_buckets

	Sample IO
	printf(“%ld”, fibonacci_hash(10, 8))
	printf(“%ld”, fibonacci_hash(999999999, 8))
	printf(“%ld”, fibonacci_hash(999999999, W))

	stdout:
	1
	0
	69107783
	**/
	unsigned long long int a = W/PHI + 0.5;

	return (INT_HASH)((long double)((a * SIN)% W ) / ((long double) W / num_buckets));

}


/*
int main(){
    printf("%ld \n", trivial_hash(10, 8));
    printf("%ld \n", pearson_hash(10, 8));


    printf("%ld \n", fibonacci_hash(10, 8));
	printf("%ld \n", fibonacci_hash(999999999, 8));
	printf("%d \n", (int)(4/((float)23/12)));

}
*/

