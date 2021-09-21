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
    //printf("input accessed\n");

    // generate random p/q s.t n > 1000 bits
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    // mpz_t rand, p, q, n;
    mpz_init(rand);
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_urandomb(rand, state, 1000); // maybe change int value to be less (2^n -1)

    mpz_nextprime(p, rand);
    mpz_nextprime(q, p);

    mpz_mul(n, p, q);
    gmp_randclear(state);

    // while bit value of n< 1000 keep generating the next prime numbers of p and q
    while( mpz_sizeinbase(n , 2) < 1000){
        mpz_nextprime(p, q);
        mpz_nextprime(q, p);
        mpz_mul(n, p, q);
    } 
    //printf("prime numbers found\n");
    // key generation
    // Compute Eulers totient function
    mpz_t p_sub, q_sub, phi, c, d;//, e, gcd;
    mpz_t one; // has to be initiali
    mpz_inits(p_sub, q_sub, phi, c, d, NULL);
    mpz_init_set_str(one, "1", 10);
    mpz_sub(p_sub, p, one);
    mpz_sub(q_sub, q, one);
    
    mpz_mul(phi, p_sub, q_sub);
    
    //printf("euler totient complete\n");
    mpz_t e, gcd;
    mpz_init(e);
    mpz_init(gcd);
    gmp_randstate_t state2;
    gmp_randinit_mt(state2);
    mpz_urandomm(e, state2, phi); // randomly choose e
    
    // get gcd of phi and e and then change e until gcd =1
    mpz_gcd(gcd, e, phi); 
    
    while( mpz_get_ui(gcd) != 1){
        mpz_add(e, e, one);
        mpz_gcd(gcd, e, phi);
    }
    
    // find e's multiplicative inverse mod phi and set = d
    mpz_invert(d, e, phi); 

    // encryption result is c-ciphertext
    mpz_powm(c, m_original, e, n);

    // Decryption 
    mpz_t m2, n2;
    mpz_inits(m2, n2, NULL);
    mpz_mul(n2, p2, q2);
    mpz_powm(m2, c2, d2, n2);

    fp = fopen("./output", "w+");
    if (fp == NULL){
        printf("\"./output\" does not exist.\n");
        return 0;
    }
    gmp_fprintf(fp, "%Zd,%Zd,%Zd,%Zd,%Zd", c, e, d, n, m2);
    
    fclose(fp);
    
    return 0;
}