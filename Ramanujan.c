#include <stdio.h>
#include <math.h>

// Function to calculate factorial
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int k;
    double sum = 0.0;
    double term;
    const double sqrt2 = sqrt(2);
    const double factor = 2 * sqrt2 / 9801;

    for (k = 0; k < 20; k++) { // Limiting to 100 terms for higher accuracy
        unsigned long long numerator = factorial(4 * k) * (1103 + 26390 * k);
        double denominator = pow(factorial(k), 4) * pow(396, 4 * k);  // Cast denominator to double
        term = (double)numerator / denominator;
        sum += term;
    }

    double pi_inverse = factor * sum;
    double pi = 1 / pi_inverse;

    printf("Approximation of pi: %.15f\n", pi);

    return 0;
}
