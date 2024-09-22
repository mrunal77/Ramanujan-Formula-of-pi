#include <stdio.h>
#include <gmp.h>
#include <math.h>

// Function to calculate factorial using GMP
void factorial(mpz_t result, int n) {
    mpz_set_ui(result, 1);
    for (int i = 1; i <= n; i++) {
        mpz_mul_ui(result, result, i);
    }
}

int main() {
    int k;
    mpf_set_default_prec(33210); // Set precision to about 1000 decimal places (bits of precision)

    mpf_t sum, term, pi_inverse, pi, factor, temp1, temp2, sqrt2, denominator;
    mpz_t numerator, factorial_k, factorial_4k;

    // Initialize variables
    mpf_init(sum);
    mpf_init(term);
    mpf_init(pi_inverse);
    mpf_init(pi);
    mpf_init(factor);
    mpf_init(temp1);
    mpf_init(temp2);
    mpf_init(sqrt2);
    mpf_init(denominator);
    mpz_init(numerator);
    mpz_init(factorial_k);
    mpz_init(factorial_4k);

    // Compute sqrt(2)
    mpf_sqrt_ui(sqrt2, 2);

    // Calculate the factor 2 * sqrt(2) / 9801
    mpf_set_ui(factor, 2);
    mpf_mul(factor, factor, sqrt2);
    mpf_div_ui(factor, factor, 9801);

    // Set sum to 0 initially
    mpf_set_ui(sum, 0);

    // Iterate for 20 terms to approximate pi
    for (k = 0; k < 20; k++) {
        // Calculate factorial(4*k)
        factorial(factorial_4k, 4 * k);

        // Calculate factorial(k)^4
        factorial(factorial_k, k);
        mpz_pow_ui(factorial_k, factorial_k, 4);

        // Calculate numerator = factorial(4 * k) * (1103 + 26390 * k)
        mpz_set_ui(numerator, 1103 + 26390 * k);
        mpz_mul(numerator, numerator, factorial_4k);

        // Calculate denominator = (factorial(k)^4 * 396^(4*k))
        mpf_set_z(denominator, factorial_k);
        mpf_pow_ui(temp1, denominator, 1); // factorial(k)^4 as mpf
        mpf_set_ui(temp2, 396);
        mpf_pow_ui(temp2, temp2, 4 * k); // 396^(4*k)
        mpf_mul(denominator, temp1, temp2); // Denominator

        // term = numerator / denominator
        mpf_set_z(temp1, numerator);
        mpf_div(term, temp1, denominator);

        // Add term to sum
        mpf_add(sum, sum, term);
    }

    // pi_inverse = factor * sum
    mpf_mul(pi_inverse, factor, sum);

    // pi = 1 / pi_inverse
    mpf_ui_div(pi, 1, pi_inverse);

    // Print the result with 1000 decimal places
    gmp_printf("Approximation of pi: %.1000Ff\n", pi);

    // Clear memory
    mpf_clear(sum);
    mpf_clear(term);
    mpf_clear(pi_inverse);
    mpf_clear(pi);
    mpf_clear(factor);
    mpf_clear(temp1);
    mpf_clear(temp2);
    mpf_clear(sqrt2);
    mpf_clear(denominator);
    mpz_clear(numerator);
    mpz_clear(factorial_k);
    mpz_clear(factorial_4k);

    return 0;
}
