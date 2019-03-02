/************************************
****	   BIL105E - Homework2	   ****
****	    Disease Detection	     ****
****          İskender Akyüz     ****
**** 	         150150150		     ****
************************************/

#include <stdio.h>

int main (void) {
	// initializing required variables
	char dna;
	int inputCounter;
	int dna_counter = 0;
	int A = 0, T = 0, C = 0, G = 0;
	int temp = 1;
	char error, error2;

	printf("Enter a seq.: ");
	//  getting first 25 characters of input
	for (inputCounter = 0; inputCounter < 25; inputCounter++) {
		dna = getchar();  // getting dna sequence from user
		if (temp == 1) {
			printf("DNA seq.:     ");
			temp = 0;
		}
		// if user enter \n, finish the taking inputs
		if ((dna == '\n') || (dna == EOF)) {
			break;
		}
		// counting dna taken in order not to get more than 10
		if ( dna_counter < 10 ) {
			switch (dna) {
				case 'A':
				case 'a':
					if ( (T == A) || (T - A == 1) ) {
						printf("A");
						A++; //  incrementing Adenine
						dna_counter++;
					}
					break;
				case 'T':
				case 't':
					if ( (A == T) || (A - T == 1) ) {
						printf("T");
						T++; //  incrementing Thymine
						dna_counter++;
					}
					break;
				case 'C':
				case 'c':
					if ( (G == C) || (G - C == 1) ) {
						printf("C");
						C++; //  incrementing Cytosine
						dna_counter++;
					}
					break;
				case 'G':
				case 'g':
					if ( (C == G) || (C - G == 1) ) {
						printf("G");
						G++; //  incrementing Guanine
						dna_counter++;
					}
					break;
				// in case of entering "x", terminate the process
				case 'X':
				case 'x':
					puts("\nTerminated!");
					return(1);
			}
		}
	}
	printf("\n");
	// checking if there is enough data to test
	if ( A + T + C + G == 0 ) {
		puts("No data to test!");
	}
	// checking all A's match with T's and C's with G's
	else if ( ( A == T ) && ( C == G ) ) {
		puts("Healthy!");
	}
	// detecting disease
	else {
		printf("Disease: ");
		if ( G == C ) {
			error = (A > T) ? 'A' : 'T';
			printf("%c nucleotide.\n", error);
		}
		else if ( A == T ) {
			error = (C > G) ? 'C' : 'G';
			printf("%c nucleotide.\n", error);
		}
		else {
			error = (A > T) ? 'A' : 'T';
			error2 = (C > G) ? 'C' : 'G';
			printf("%c and %c nucleotides.\n", error, error2);
		}
	}
	return(0);
}
