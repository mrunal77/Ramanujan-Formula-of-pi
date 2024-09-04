#include <stdio.h>
#include <gmp.h>

// Function to calculate arctan using Taylor series
void mpf_arctan(mpf_t result, mpf_t x, unsigned long int precision) {
    mpf_t term, x_pow, temp;
    mpf_init(term);
    mpf_init(x_pow);
    mpf_init(temp);

    mpf_set(x_pow, x); // x^1
    mpf_set(result, x); // First term is x

    for (unsigned long int n = 1; n < precision; n++) {
        mpf_mul(x_pow, x_pow, x); // x^(2n)
        mpf_mul(x_pow, x_pow, x); // x^(2n+1)
        mpf_set_ui(temp, 2*n+1); // 2n+1
        mpf_div(term, x_pow, temp); // x^(2n+1) / (2n+1)

        if (n % 2 == 0) {
            mpf_add(result, result, term); // Add term if n is even
        } else {
            mpf_sub(result, result, term); // Subtract term if n is odd
        }
    }

    mpf_clear(term);
    mpf_clear(x_pow);
    mpf_clear(temp);
}

int main() {
    mpf_set_default_prec(1000000); // Set precision to 1,000,000 bits

    mpf_t arctan_half, arctan_third, sum, pi, one_half, one_third;
    mpf_init(arctan_half);
    mpf_init(arctan_third);
    mpf_init(sum);
    mpf_init(pi);
    mpf_init_set_d(one_half, 0.5);
    mpf_init_set_d(one_third, 1.0 / 3.0);

    // Calculate arctan(1/2) and arctan(1/3)
    mpf_arctan(arctan_half, one_half, 100000);
    mpf_arctan(arctan_third, one_third, 100000);

    // Sum the arctan values
    mpf_add(sum, arctan_half, arctan_third);

    // Calculate pi
    mpf_mul_ui(pi, sum, 4);

    // Print the result
    gmp_printf("Calculated value of pi: %.100000Ff\n", pi);

    // Clear memory
    mpf_clear(arctan_half);
    mpf_clear(arctan_third);
    mpf_clear(sum);
    mpf_clear(pi);
    mpf_clear(one_half);
    mpf_clear(one_third);

    return 0;
}
