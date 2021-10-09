// Sydney Hnat
// NetID:shnat

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

int main(int argc, const char* argv[]){

	time_t t;

	//initialize int variables for input
	mpz_t m, x, g, p, h, r, hr, p_qr, g2, gx, random, gen, one, c11, c12;	//, c21, c22, c31, c32;
	mpz_inits(m, g, x, p, h, r, hr, p_qr, g2, gx, gen, one, c11, c12, NULL);		//, c21, c22, c31, c32, NULL);
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


	//find random g
	srand((unsigned) time(&t));
	int seed = rand();
	mpz_init(random);
	mpz_urandomb(rand, state, 2000);
	mpz_nextprime(p, random);
	gmp_randseed_ui(state, seed);
	mpz_urandomb(g,state,2000); //find random g
	//mpz_urandomb(r,state,2000);


	mpz_set(p_qr, p);
	mpz_set_ui(one, 1);
	mpz_submul_ui(p_qr, 1, 0.5);

    //calculate generator that is safe from QR/QNR attacks
	while (mpz_cmp(g, p) != 0) {
		mpz_powm(gx, g, p_qr, p); //g^((p-1)/2) mod p
		mpz_powm_ui(g2, g, 2, p); //g^2 mod p

		if (!(mpz_cmp_ui(gx, 1) == 0) && !(mpz_cmp_ui(g2, 1) == 0)) {
		    mpz_set(gen, g);
		    break;
		}
		else {
		    mpz_urandomb(g, state, 2000);
		}

	}

	/*
	//make sure g is greaater than x
	while( mpz_cmp(g,x)<0 ){ 
	mpz_urandomb(9,state,n);
	}

	// Make sure that p > g
	while(mpz_cmp(p,g)<0){
	mpz_urandomb(p,state,2000);
	mpz_nextprime(p, p);
	}
	*/     
	mpz_powm(h,gen,x,p);

	//------------------------Encryption-------------------------//

	mpz_urandomb(r,state,2000);

	// make sure that p is greater than k
	while( mpz_cmp(p,r)<0 ) {
		mpz_urandomb(r,state,2000);
	}

	mpz_powm(c11, gen, r, p);  // calculate c11
	mpz_powm(hr, h, r, p);  // calculate h^r
	mpz_mul(c12, m, hr); // calculate c12 

	//------------------------Check If QR/QNR safe-------------------------//



	gmp_randclear(state);


	fp = fopen("./output", "w+");
	if (fp == NULL){
		printf("\"./output\" does not exist.\n");
		return 0;
	}
	gmp_fprintf(fp,"%Zd,%Zd,%Zd\n", c11, c12, p);		
		//,%Zd,%Zd\n%Zd,%Zd,%Zd", c11, c12, p, c21, c22, p, c31, c32, p);

	fclose(fp);

	return 0;
}
