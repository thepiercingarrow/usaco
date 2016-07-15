/*
ID: thepier1
LANG: C
TASK: pprime
*/
#include <stdio.h>
#include <math.h>

#define MAX_P 100000000
#define SQRT_MAX 10000

void search(int len);
int genpal(int len, int seed);
int isprime(int p);

FILE *fout;
int a, b, primes[SQRT_MAX], count_p = 0;

int main() {
  FILE *fin = fopen("pprime.in", "r");
  fout = fopen("pprime.out", "w");
  fscanf(fin, "%d %d\n", &a, &b);
  int i, j;
  for (i = 2; i < sqrt(b); ++i) { // generate primes
    int prime = 1;
    for (j = 0; primes[j] <= sqrt(i) && j < count_p; ++j)
      if (i % primes[j] == 0) {
	prime = 0;
	break;
      }
    if (prime)
      primes[count_p++] = i;
  }
  int k, l;
  for (j = 10, l = 1; j < a; ++l)
    j *= 10;
  for (k = l; j < b; ++k)
    j *= 10;
  for (i = l; i <= k; ++i)
    search(i);
}

void search(int len) {
  int i, pal;
  for (i = pow(10, (len - 1) / 2); i < pow (10, (len + 1) / 2); ++i) {
    pal = genpal(len, i);
    if (pal > b)
      return;
    if (pal < a)
      continue;
    if (isprime(pal))
      fprintf(fout, "%d\n", pal);
  }
}

int genpal(int len, int seed) {
  int pal = seed;
  if (len % 2)
    seed /= 10;
  while (seed > 0) {
    pal = 10 * pal + seed % 10;
    seed /= 10;
  }
  return pal;
}

int isprime(int p) {
  int i;
  for (i = 0; primes[i] <= sqrt(p) && i < count_p; ++i)
    if (p % primes[i] == 0)
      return 0;
  return 1;
}
