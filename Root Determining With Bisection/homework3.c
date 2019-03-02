/*******************************************
****	     BIL105E - Homework3	    ****
****  Root Determining With Bisection	****
****           İskender Akyüz           ****
****              150150150             ****
*******************************************/

#include <stdio.h>  // adding standart input&output library
// declaration of functions which I have created
float equation(int factorA, int factorB, int factorC, float point);
float bisection(float lower, float higher, int factorA, int factorB, int factorC);
void findRoots(float lower, float higher, int a, int b, int c);

int main(void) {
    // initializing required variables
    int factorA, factorB, factorC, lowerLmt, upperLmt;

    scanf("%d %d %d %d %d", &factorA, &factorB, &factorC, &lowerLmt, &upperLmt);
    printf("Entered equation: %dx^2 + %dx + %d\n", factorA, factorB, factorC);
    printf("Domain: %d, %d\n", lowerLmt, upperLmt);
    // calling the function to find the roots if any
    findRoots((float)lowerLmt, (float)upperLmt, factorA, factorB, factorC);

    return(0);
}
// finding f(x) by using point and parameters
float equation(int a, int b, int c, float point) {
    return a * point * point + b * point + c;
}
// finding roots with bisection method
float bisection(float lower, float higher, int a, int b, int c) {
    float result1 = equation(a, b, c, lower); // finding f(lower)
    float mid = (lower + higher) / 2;
    float result2 = equation(a, b, c, mid); // finding f(mid)

    if ( (result2 >= 0.001) || (result2 <= -0.001) ) { // our error rate is 0.001
        if (result1 * result2 > 0) {
            return bisection(mid, higher, a, b, c); // replacing mid with lower point and initializing bisection again
        }
        else if (result1 * result2 < 0) {
            return bisection(lower, mid, a, b, c); // replacing mid with higher point and initializing bisection again
        }
    }
    else {
        return mid; // returning the root
    }
}
// the function printing roots if any
void findRoots(float lower, float higher, int a, int b, int c) {
    int discriminant = b * b - 4 * a * c;
    // if delta is less than or equal to zero, that means there is no root
    if (discriminant <= 0) {
        puts("No roots found");
    }
    else {
        // if a is not equal to zero, that means it is second degree polynomial
        if (a != 0) {
            float extrm = (float)-b / (2 * a); // finding peak point to dichotomy domain
            float root1 = bisection(lower, extrm, a, b, c);
            float root2 = bisection(extrm, higher, a, b, c);
            printf("Roots: x=%.3f, x=%.3f\n", root1, root2);
        }
        else {  // this is the line case, so there exist only one root
            printf("Root: x=%.3f\n", bisection(lower, higher, a, b, c));
        }
    }
}
