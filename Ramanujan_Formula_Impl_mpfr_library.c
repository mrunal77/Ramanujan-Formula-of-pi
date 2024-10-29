#include <stdio.h>
#include <mpfr.h>

void calculate_pi(int digits) {
    mpfr_t pi, sum, term, factor, temp;
    mpfr_inits2(digits * 3.32193, pi, sum, term, factor, temp, (mpfr_ptr) 0);

    // Constants for Ramanujan's formula
    mpfr_t constant, sqrt2;
    mpfr_inits2(digits * 3.32193, constant, sqrt2, (mpfr_ptr) 0);

    // constant = 2 * sqrt(2) / 9801
    mpfr_sqrt_ui(sqrt2, 2, MPFR_RNDN);
    mpfr_mul_ui(constant, sqrt2, 2, MPFR_RNDN);
    mpfr_div_ui(constant, constant, 9801, MPFR_RNDN);

    mpfr_set_ui(sum, 0, MPFR_RNDN); // sum = 0

    // Ramanujan series computation
    for (int k = 0; k < digits / 14 + 1; ++k) {
        // term = (1103 + 26390 * k) * (4k)! / (k!)^4
        mpfr_set_ui(term, 1103 + 26390 * k, MPFR_RNDN);

        // Compute (4k)!
        mpfr_fac_ui(factor, 4 * k, MPFR_RNDN);
        mpfr_mul(term, term, factor, MPFR_RNDN);

        // Divide by (k!)^4
        mpfr_fac_ui(factor, k, MPFR_RNDN);
        mpfr_pow_ui(factor, factor, 4, MPFR_RNDN);
        mpfr_div(term, term, factor, MPFR_RNDN);

        // Add term to sum
        mpfr_add(sum, sum, term, MPFR_RNDN);
    }

    // Multiply sum by constant to get pi approximation
    mpfr_mul(pi, sum, constant, MPFR_RNDN);

    // Print the result
    //mpfr_printf("Pi with %d digits precision: %..*Rf\n", digits, digits, pi);
    mpfr_printf("Pi with %d digits precision: %.*Rf\n", digits, digits, pi);


    // Clear memory
    mpfr_clears(pi, sum, term, factor, temp, constant, sqrt2, (mpfr_ptr) 0);
}


int main() {
    int digits = 100000; // Set desired precision
    calculate_pi(digits);
    return 0;
}

// Compilation command : gcc Ramanujan_Formula_Impl_mpfr_library.c -o Ramanujan_Formula_Impl_mpfr_library -lmpfr -lgmp