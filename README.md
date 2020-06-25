# HashTable
This is an implementation of Hash Table using C. The included hash functions are Trivial Hash, Pearson Hash, and Fibonacci Hash. Collision handling methods include chaining via linked lists, as well as Linear/Quadratic Probing

To utilize the hash table for your own purpose, only compile part 1 and part 2.
However, if a demonstration of the hash table is required, compile all parts. This will generate a hash table based on the file load.txt, which is then updated according to update.txt. Then the function compares the data in the hash table (which includes some fake identity after it was updated) to the real dataset called validate.txt. The program then generates a list of all fake identities in the file spies.txt. 

To compile this demonstration, run the following command:
gcc -o tester lab4.h lab4_part1.c lab4_part2.c lab4_part3.c utilities.c utilities.h
