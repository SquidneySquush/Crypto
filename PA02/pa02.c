// Sydney Hnat
// NetID:shnat

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, const char* argv[]){

    //initialize int variables for input
    mpz_t m, x, p, c11, c12, c21, c22, c31, c32;
    mpz_inits(m, x, p, c11, c12, c21, c22, c31, c32, NULL);
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

    fp = fopen("./output", "w+");
    if (fp == NULL){
        printf("\"./output\" does not exist.\n");
        return 0;
    }
    gmp_fprintf(fp, "%Zd,%Zd,%Zd\n%Zd,%Zd,%Zd\n%Zd,%Zd,%Zd", c11, c12, p, c21, c22, p, c31, c32, p);
    
    fclose(fp);

    return 0;
}