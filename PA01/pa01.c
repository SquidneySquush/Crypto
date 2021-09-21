/// Sydney Hnat PA01.c
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, const char* argv[]){

    //initialize int variables for input
    mpz_t m_original, c2, d2, p2, q2, rand, p, q, n;
    mpz_inits(m_original, c2, d2, p2, q2, NULL);

    FILE *fp;
    char buf[5000];
    fp = fopen("./input", "r");

    // check if file is empty
    if (fp == NULL){
        printf("\"./input\" does not exist\n");
        return 0;
    }

    fgets(buf, 5000, (FILE*)fp); 
    gmp_sscanf(buf, "%Zd,%Zd,%Zd,%Zd,%Zd", m_original, c2, d2, p2, q2); // read input into variables
    fclose(fp); // close file and release memory

    // generate random p/q s.t n > 1000 bits
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    // mpz_t rand, p, q, n;
    mpz_init(rand);
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_urandomb(rand, state, 1000); // maybe change int value to be less (2^n -1)

    // while bit value of n< 1000 keep generating the next prime numbers of p and q
    while( mpz_sizeinbase(n , 2) < 1000){
        mpz_nextprime(p, q);
        mpz_nextprime(q, p);
        mpz_mul(n, p, q);
    } 

    // key generation
    // Compute Eulers totient function
    mpz_t p_sub, q_sub, phi, c, d, one;
    //mpz_t one; // has to be initiali
    mpz_init_set_str(one, "1", 10);
    mpz_sub(p_sub, p, one);
    mpz_sub(q_sub, q, one);
    mpz_mul(phi, p_sub, q_sub);

    mpz_t e, gcd;
    gmp_randstate_t state2;
    gmp_randinit_mt(state2);
    mpz_urandomm(e, state2, phi); // randomly choose e

    // find e's multiplicative inverse mod phi and set = d
    mpz_invert(d, e, phi); 

    // encryption result is c-ciphertext
    mpz_powm(c, m_original, e, n);

    // Decryption 
    mpz_t m2;
    mpz_powm(m2, c, d, n);


    fp = fopen("./input", "w+");
    if (fp == NULL){
        printf("\"./output\" does not exist.\n");
        return 0;
    }
    gmp_fprintf(fp, "%Zd,%Zd,%Zd,%Zd,%Zd", c, e, d, n, m2);

    fclose(fp);

    return 0;
}