/// Sydney Hnat PA01.c
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, const char* argv[]){

 /* FILE *fp;
  fp = fopen("./input", "r");

  if (fp == NULL){
        printf("\"./input\" does not exist\n");
        return 0;
  }
  
  fgets(buf, 5000, (FILE*)fp);
  gmp_sscanf(buf, "%Zd,%Zd,%Zd,%Zd,%Zd", c, e, d, n, m2);
  fclose(fp);
  mpz_t m_original, c2, d2, p2, q2;
  mpz_inits(m_original, c2, d2, p2, q2, NULL); */
  //gmp_sscanf(argv[1], "%Zd,%Zd,%Zd,%Zd,%Zd,", m_original, c2, d2, p2, q2);

// generate random p/q s.t n > 1000 bits
/*  gmp_randstate_t state;
  gmp_randinit_mt(state);
  mpz_t rand, p, q, n;
  mpz_init(rand);
  mpz_init(p);
  mpz_init(q);
  mpz_init(n);
  mpz_urandomb(rand, state, 1000);

  mpz_nextprime(p, rand);
  mpz_nextprime(q, p);

  mpz_mul(n, p, q);
  mpz_t size;

  while( mpz_sizeinbase(n , 2) < 1000){
    mpz_nextprime(p, q);
    mpz_nextprime(q, p);
    mpz_mul(n, p, q);
  }
*/

  mpz_t p_sub, q_sub, E_tot;
  mpz_t one;
  mpz_init_set_str(one, "1", 10);
  mpz_sub(p_sub, p, one);
  mpz_sub(q_sub, q, one);
  mpz_mul(E_tot, p_sub, q_sub);

  mpz_t e, gcd;
  gmp_randstate_t state2;
  gmp_randinit_default(state2);
  mpz_urandomm(e, state2, E_tot);

  mpz_gcd(gcd, e, E_tot);
  while( mpz_get_ui(gcd) != 1){
    mpz_add(e, e, one);
    mpz_gcd(gcd, e, E_tot);
  }

  mpz_t d;
  mpz_invert(d, e, E_tot); 

  mpz_t c;
  mpz_powm(c, m_original, e, n);

  mpz_t n2;
  mpz_mul(n2, p2, q2);

  mpz_t m_final;
  mpz_powm(m_final, c2, d2, n2);
  gmp_printf("%Zd,%Zd,%Zd,%Zd,%Zd", c, e, d, n, m_final);

    return 0;
}
