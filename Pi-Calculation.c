#include <stdio.h>
#include <math.h>

int main() {
    // Calculate arctan(1/2) and arctan(1/3)
    double arctan_half = atan(1.0 / 2.0);
    double arctan_third = atan(1.0 / 3.0);

    // Sum the arctan values
    double sum = arctan_half + arctan_third;

    // Calculate pi
    double pi = 4 * sum;

    // Print the result
    printf("Calculated value of pi: %.15f\n", pi);

    return 0;
}
