/************************************
****	 BIL105E - Homework5	 ****
****	      Cryptology	     ****
****        İskender Akyüz       ****
****          150150150          ****
************************************/
// gcc homework5.c -o homework5

#include <stdio.h>  // adding standart input&output library
#include <stdlib.h>

#define NAME_SIZE 10  // defining length of the name matrix
#define NUM_SIZE 3  // defining length of the number matrix
#define MODE_SIZE 2  // defining length of mode matrix
#define MODIFIER_SIZE 3  // defining length of the modifier matrix
// function prototypes
int power(int , int);
int modulus(int, int);
void decryptName(char [], int, int);
void decryptNumber(char [][NUM_SIZE]);
int decryptAuxiliaries(char [], size_t );
int checkCorruption(char [], char [][NUM_SIZE], char [], char []);

int main(void) {
    // initializing required variables
    size_t i, j; // counters
    char name[NAME_SIZE];  // a matrix to keep the name
    char number[NUM_SIZE][NUM_SIZE];  // a 2D matrix to keep the number
    char mode_b[MODE_SIZE];  // a matrix to keep the mode
    char modifier_b[MODIFIER_SIZE];  // a matrix to keep the modifier
    int mode, modifier;

    printf("Enter the data to decrypt:");
    for(i = 0; i < NAME_SIZE; i++) {
        scanf("%c", name+i);  // getting the name from user
    }
    for(i = 0; i < NUM_SIZE; i++) {
        for(j = 0; j < NUM_SIZE; j++) {
            scanf("%c", *(number+i)+j);  // getting the number from user
        }
    }
    for(i = 0; i < MODE_SIZE; i++) {
        scanf("%c", mode_b+i);  // getting the mode from user
    }
    for(i = 0; i < MODIFIER_SIZE; i++) {
        scanf("%c", modifier_b+i);  // getting the modifier from user
    }
    if(checkCorruption(name, number, mode_b, modifier_b)) { // checking if the input is valid to decrypt
        puts("Data is corrupted");
        return 1;
    }
    else {
        mode = decryptAuxiliaries(mode_b, MODE_SIZE);  // converting mode in binary to decimal
        modifier = decryptAuxiliaries(modifier_b, MODIFIER_SIZE);  // converting modifier in binary to decimal
        decryptName(name, mode, modifier);  // decrypting name by using mode and modifier
        decryptNumber(number);  // decrypting number by transpozing
        puts("Decrypted ---");
        printf("Name: ");
        for(i = 0; i < NAME_SIZE; i++) {
            printf("%c", *(name+i));  // printing decrypted name
        }
        printf("\nNumber: ");
        for(i = 0; i < NUM_SIZE; i++) {
            for(j = 0; j < NUM_SIZE; j++) {
                printf("%c", *(*(number+i)+j));  // printing decrypted number
            }
        }
        printf("\nMode: %d\n", mode);  // printing mode
        printf("Modifier: %d\n", modifier);  // pinting modifier
    }
    return 0;
}
// function that computes exponential expression
int power(int num, int pwr) {
    size_t i;  // counters
    int result = 1;
    for(i = 0; i < pwr; i++) {
        result *= num;
    }
    return result;  // returning the result
}
// function that calculates modulo
int modulus(int num, int divider) {
    int result = num % divider;
    return (result < 0) ? (result + divider) :  result;
}
// function that decrypts the name
void decryptName(char name[], int mode, int modifier) {
    char temp_name[NAME_SIZE];
    size_t i;  // counter
    switch(mode) {
        case 0:  // if the mode is 0, do nothing
            break;
        case 1:  // if the mod is 1, do negative caesar
            for(i = 0; i < NAME_SIZE; i++) {
                *(name+i) = (modulus(((*(name+i) - modifier)-97),26)+97);
            };
            break;
        case 2:  // if the mod is 2, do positive caesar
            for(i = 0; i < NAME_SIZE; i++) {
                *(name+i) = (modulus(((*(name+i) + modifier)-97),26)+97);
            };
            break;
        case 3:  // if the mode is 3, take reverse of it
            for(i = 0; i < NAME_SIZE; i++) {
                *(temp_name+i) = *(name+i);  // holding it's characters on temporary matrix
            };
            for(i = 0; i < NAME_SIZE; i++) {
                *(name+i) = *(temp_name+(NAME_SIZE - i - 1));
            };
            break;
    }
}
// function that decrypts the number
void decryptNumber(char number[][NUM_SIZE]) {
    size_t i, j;  // counters
    char temp_number[NUM_SIZE][NUM_SIZE];  // creating temporary matrix to hold values of original matrix
    for(i = 0; i < NUM_SIZE; i++) {
        for(j = 0; j < NUM_SIZE; j++) {
            *(*(temp_number+i)+j) = *(*(number+i)+j);  // holding values of matrix on temporary one
        }
    }
    for(i = 0; i < NUM_SIZE; i++) {
        for(j = 0; j < NUM_SIZE; j++) {
            *(*(number+j)+i) = *(*(temp_number+i)+j);  // transpozing process
        }
    }
}
// function that derypts axuiliaries by converting binary numbers to decimal
int decryptAuxiliaries(char array[], size_t n) {
    int result = 0;  // initializing required variable
    size_t i;  // counter
    for(i = 0; i < n; i++) {
        if ( *(array+i) == '1' ) {
            result += 1 * power(2, n-i-1);
        }
    }
    return result;  // returning the result
}
// function that checks if the input given is valid to decrypt
int checkCorruption(char name[], char number[][NUM_SIZE], char mode_b[], char modifier_b[]) {
    int corruption = 0;  // at the beginining, we set the corruption to false
    size_t i, j;  // counters
    for(i = 0; i < NAME_SIZE; i++) {
        if( *(name+i) < 97 || *(name+i) > 122 ) {  // checking if name part has any other than English alphabet
            corruption = 1;  // if it has, then corruption is true
            return corruption;
        }
    }
    for(i = 0; i < NUM_SIZE; i++) {
        for(j = 0; j < NUM_SIZE; j++) {
            if( (*(*(number+i)+j) < 48) || (*(*(number+i)+j) > 57) ) {  // checking if number part has any other characters than numbers
                corruption = 1;  // if it has, then corruption is true
                return corruption;
            }
        }
    }
    for(i = 0; i < MODE_SIZE; i++) {
        if( !(*(mode_b+i) == '0') && !(*(mode_b+i) == '1') ) {  // checking mode part has any other character than '0' or '1'
            corruption = 1;  // if it has, then corruption is true
            return corruption;
        }
    }
    for(i = 0; i < MODIFIER_SIZE; i++) {
        if( !(*(modifier_b+i) == '0') && !(*(modifier_b+i) == '1') ) {  // checking modifier part has any other character than '0' or '1'
            corruption = 1;  // if it has, then corruption is true
            return corruption;
        }
    }
    return corruption;
}
