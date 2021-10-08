// Sydney Hnat
// NetID:shnat

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, const char* argv[]){

    //initialize int variables for input
    mpz_t m, x, g, p, h, c11, c12, c21, c22, c31, c32;
    mpz_inits(m, g, x, p, h, c11, c12, c21, c22, c31, c32, NULL);
    // Assign x to private key given in directions
    //mpz_init2(x, 200);
    //mpz_set_ui(x, 1234567890123456789012345678901234567890);
    const char str[] = "1234567890123456789012345678901234567890";
    mpz_set_str(x, str, 10);    // parse the string as a base-10 number

    FILE *fp;
    char buf[5000];
    fp = fopen("./input", "r");

    // check if file is empty
    if (fp == NULL){
        printf("\"./input\" does not exist\n");
        return 0;
    }

    fgets(buf, 5000, (FILE*)fp); 
    gmp_sscanf(buf, "%Zd", m); // read input into variables
    fclose(fp); // close file and release memory

    // generate p s.t p > 2000 bits
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    mpz_init(rand);
    mpz_urandomb(rand, state, 2000);
    mpz_nextprime(p, rand);
    mpz_urandomb(g,state,2000);
    
    //make sure g is greaater than x
    while( mpz_cmp(g,x)<0 ){ 
        mpz_urandomb(9,state,n);
    }
    
    // Make sure that p > g
    while(mpz_cmp(p,g)<0){
        mpz_urandomb(p,state,2000);
        mpz_nextprime(p, p);
    }
    
    gmp_randclear(state);
    
    mpz_powm(h,g,x,p);







    fp = fopen("./output", "w+");
    if (fp == NULL){
        printf("\"./output\" does not exist.\n");
        return 0;
    }
    gmp_fprintf(fp, "%Zd,%Zd,%Zd\n%Zd,%Zd,%Zd\n%Zd,%Zd,%Zd", c11, c12, p, c21, c22, p, c31, c32, p);
    
    fclose(fp);

    return 0;
}
