/************************************
****	 BIL105E - Homework4	 ****
****	     Treasure Hunt	     ****
****        İskender Akyüz       ****
****          150150150          ****
************************************/
// gcc homework4.c -lm -o homework4

#include <stdio.h>  // adding standart input&output library
#include <math.h>  // adding math library for trigonometric functions

#define ROW 2  // defining # rows of a matrix
#define COL 2  // defining # columns of a matrix
#define VCTR_COL 1  // defining # columns of a vector
#define PI 3.14159265359  // the value of pi
// function prototypes
void move(double [][COL], double [][VCTR_COL], int, int);
void change_basis(double [][COL], int, int, int, int);
void rotate(double [][COL], double);
void dig(double [][VCTR_COL]);

int main(void) {
    // initializing required variables
    char mode;
    int a_11, a_12, a_21, a_22;  // for matrix's elements
    double degree;
    double basis[ROW][COL] = {{1,0},
                              {0,1}};  // basis vector
    double coordinates[ROW][VCTR_COL] = {{0},
                                         {0}};  // our initial point
    do {
        mode = getchar(); // taking input from user to detect which mode he/she will use
        switch(mode) {
            case 'm':
                scanf("%d %d", &a_11, &a_21);  // getting elements of movement vector from user
                double final[ROW][VCTR_COL] = {0};  // we will keep final result in this matrix
                move(basis, final, a_11, a_21);  // getting result by calling move function
                size_t i;  // counter
                for(i = 0; i < ROW; i++) {  // adding result to our coordinates
                    coordinates[i][0] += final[i][0];
                    final[i][0] = 0;  // setting to zero to use it again
                }
                break;
            case 'c':
                scanf("%d %d %d %d", &a_11, &a_12, &a_21, &a_22);  // getting integers for a new basis
                change_basis(basis, a_11, a_12, a_21, a_22);  // changing the basis by caling change_basis function
                break;
            case 'l':
                scanf("%lf", &degree);  // getting degree which will rotate current basis vectors to the left
                rotate(basis, degree);  // rotating basis by calling rotate function
                break;
            case 'r':
                scanf("%lf", &degree);  // getting degree which will rotate current basis vectors to the right
                rotate(basis, 360-degree);  // rotating basis by calling rotate function
                break;
        }
    }
    while(mode != 'd');  // if the mode is 'd', then user found treasure
    dig(coordinates);  // printing coordinates of the treasure
    return 0;
}
// move the character in the coordinate system
void move(double base[][COL], double final[][VCTR_COL], int a_11, int a_21) {
    double moving[ROW][VCTR_COL] = {{a_11},
                                    {a_21}};  // initializing move vector by using integers taken from user
    size_t i, j;  // counters
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            final[i][0] += base[i][j] * moving[j][0]; // matrix multiplication
        }
    }
}
// customizing basis
void change_basis(double base[][COL], int a_11, int a_12, int a_21, int a_22) {
    int new_base[ROW][COL] = {{a_11, a_12},
                              {a_21, a_22}};  // initializing the new basis
    size_t i, j;  // counters
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            base[i][j] = new_base[i][j];  // converting the previous basis to new one
        }
    }
}
// rotating basis by degree
void rotate(double base[][COL], double degree) {
    degree *= PI / 180;  // converting degree to radian
    double rotation_matrix [ROW][COL] = {{cos(degree), -sin(degree)},
                                         {sin(degree),  cos(degree)}};  // initializing rotation matrix
    double temp[ROW][COL];  // temporary matrix for holding the values of current basis
    size_t a, b;  // counters
    for (a = 0; a < ROW; a++) {
        for (b = 0; b < COL; b++) {
            temp[a][b] = base[a][b];
            base[a][b] = 0;  // setting all elements of base to zero
        }
    }
    size_t i, j, k;  // counters
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            for(k = 0; k < COL; k++) {
                base[i][j] += temp[i][k] * rotation_matrix[k][j];  // rotating the current basis
            }
        }
    }
}
// after finding the coordinates, print them
void dig(double coordinates[][VCTR_COL]) {
    printf("Coordinates: ");
    size_t i;  // counter
    for (i = 0; i < ROW; i++) {
        printf("%.2f ", coordinates[i][0]);  // printing current coordinates
    }
    puts("");
}
