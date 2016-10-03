/*
ID: thepier1
LANG: C
TASK: subset
*/
#include <stdio.h>

#define N_MAX 40

int main() {
  int N;
  FILE *fio = fopen("subset.in", "r");
  fscanf(fio, "%d", &N);
  fclose(fio);
  fio = fopen("subset.out", "w");
  if ((N*(N+1))%4) {
    fprintf(fio, "0\n");
    return 0;
  }  
  int i, j;
  long long int ways[N_MAX * (N_MAX + 1) / 4 + 1] = {0};
  ways[0] = 1; // 1 way to make nothing!
  for (i = 1; i <= N; ++i) // using integers 1, 2, ... i
    for (j = (N*(N+1)/4); j >= i; --j)
      ways[j] += ways[j - i];
  fprintf(fio, "%lld\n", ways[N * (N + 1) / 4] / 2);
}
