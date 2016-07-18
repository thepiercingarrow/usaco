/*
ID: thepier1
LANG: C
TASK: sprime
*/
#include <stdio.h>
#include <math.h>
#include <string.h>

#define SQRT_MAX_R 10000

void append(int rib, int len);
int isPrime(int p);

FILE *fio;
int composite[SQRT_MAX_R + 1], max;
int primes[SQRT_MAX_R], count = 0;

int main() {
  int N;
  fio = fopen("sprime.in", "r");
  fscanf(fio, "%d\n", &N);
  fclose(fio);
  memset(composite, 0, sizeof composite);
  composite[0] = composite[1] = 1;
  int i, j;
  max = sqrt(pow(10, N));
  for (i = 2; i <= max / 2; ++i)
    if (!composite[i])
      for (j = 2 * i; j <= max; j += i)
	composite[j] = 1;
  for (i = 2; i <= max; ++i)
    if (!composite[i])
      primes[count++] = i;
  fio = fopen("sprime.out", "w");
  append(0, N);
}

void append(int rib, int len) {
  if (len == 0) {
    fprintf(fio, "%d\n", rib);
    return;
  }
  rib *= 10;
  int i;
  for (i = 1; i < 10; ++i) {
    if (isPrime(rib + i))
      append(rib + i, len - 1);
  }
}

int isPrime(int p) {
  if (p <= max)
    return !composite[p];
  int i;
  for (i = 0; primes[i] <= sqrt(p) && i < count; ++i)
    if (p % primes[i] == 0)
      return 0;
  return 1;
}
