/**************************
***	BIL105E - Homework1	***
***	Prime Factorization	***
**************************/

#include <stdio.h> // adding standart input&output library

int main(void) {
	int user_input, divisor = 2, divisor_counter = 0;  // creating variables
	printf("Enter a number: "); // asking a number from user
	scanf("%d", &user_input);
	
	// checking if the number is valid, if it isn't, take numbers till he gives a valid one
	while ( user_input <= 1 ) {
		printf("Enter a valid number: ");
		scanf("%d", &user_input);
	}
	
	printf("Prime factorization of %d: ", user_input);
	
	for (; divisor <= user_input; divisor++) {
		while ( user_input % divisor == 0 ) {
			user_input /= divisor;
			divisor_counter++;
		}
		// printing primes and number of them
		if ( divisor_counter != 0 ) {
			printf("%d^%d", divisor, divisor_counter);
		}
		// printing * between different primes
		if ( (user_input != 1) && (divisor_counter != 0) ) {
			printf(" * ");
		}
		divisor_counter = 0;  // reset the divisor_counter
	}
	printf("\n");
	return(0);
}
