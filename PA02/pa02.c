// Sydney Hnat
// NetID:shnat

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

int main(int argc, const char* argv[]){
	int count = 3;
	int i= 0;
	time_t t;

	//initialize int variables for input
	mpz_t m, x, g, p, q, h, r, hr, p_qr, g2, gx, random, gen, one, two, seed; 
	mpz_t c1[count];
	mpz_t c2[count];	
	
	// Assign x to private key given in directions
	const char str[] = "1234567890123456789012345678901234567890";
	mpz_set_str(x, str, 10);    // parse the string as a base-10 number
	mpz_init_set_str(one, "1", 10);
	mpz_init_set_str(two, "2", 10);

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

	while (count !=0){
		
		mpz_inits(m, g, x, p, q, h, r, hr, p_qr, g2, gx, gen, seed, NULL);

		for( int j = 0; j< 3; j=j+1){
			mpz_init(c1[j]);
			mpz_init(c2[j]);
		}
		
		// generate p s.t p > 2000 bits
		gmp_randstate_t state;
		gmp_randinit_mt(state);

		//srand((unsigned) time(&t));
		//int seed = getpid();
		mpf_urandomb(seed, state,2000);
		mpz_init(random);
		mpz_urandomb(random, state, 2000);
		

		mpz_nextprime(q, random);
		mpz_mul(p, q, two);
		mpz_add(p, p, one);

		//find random g
		gmp_randseed_ui(state, seed);
		mpz_urandomb(g,state,2000); //find random g
		//mpz_urandomb(r,state,2000);


		mpz_set(p_qr, p);
		//mpz_set_ui(one, 1);
		mpz_submul_ui(p_qr, one, 0.5);

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
    
		mpz_powm(h,gen,x,p);

		//------------------------Encryption-------------------------//

		mpz_urandomb(r,state,2000);

		// make sure that p is greater than k
		while( mpz_cmp(p,r)<0 ) {
			mpz_urandomb(r,state,2000);
		}

		mpz_powm(c1[i], gen, r, p);  // calculate c11
		mpz_powm(hr, h, r, p);  // calculate h^r
		mpz_mul(c2[i], m, hr); // calculate c12 

		gmp_randclear(state);

		count = count -1;
		i= i +1;

	}

	fp = fopen("./output", "w+");
	if (fp == NULL){
		printf("\"./output\" does not exist.\n");
		return 0;
	}

	for( int k = 0; k< 3; k=k+1){
		gmp_fprintf(fp,"%Zd,%Zd,%Zd\n", c1[k], c2[k], p);		
	}	
		


	fclose(fp);

	return 0;
}
