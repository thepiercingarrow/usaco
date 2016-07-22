/*
ID: thepier1
LANG: C
TASK: frac1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 160

typedef char bool;

struct Frac {
  int num, den;
};

int compar(struct Frac *a, struct Frac *b);

int main() {
  struct Frac fractions[MAX_N * MAX_N + 2];
  bool snapshots[MAX_N + 1][MAX_N + 1];
  memset(snapshots, 0, sizeof snapshots);
  int N, num_frac = 1;
  FILE *fio = fopen("frac1.in", "r");
  fscanf(fio, "%d\n", &N);
  fclose(fio);
  fractions[0].num = 0;
  fractions[0].den = 1;
  for (int den = 1; den <= N; ++den)
    for (int num = 1; num < den; ++num) {
      if (snapshots[num][den])
	continue; // duplicate
      fractions[num_frac].num = num;
      fractions[num_frac].den = den;
      ++num_frac;
      int sden = den, snum = num;
      while (sden <= N) {
	snapshots[snum][sden] = 1;
	sden += den, snum += num;
      }
    }
  fractions[num_frac].num = 1;
  fractions[num_frac++].den = 1;
  qsort(fractions, num_frac, sizeof(struct Frac), (int (*)(const void *, const void *))compar);
  fio = fopen("frac1.out", "w");
  for (int i = 0; i < num_frac; ++i)
    fprintf(fio, "%d/%d\n", fractions[i].num, fractions[i].den);
}

int compar(struct Frac *a, struct Frac *b) {
  return a->num * b->den - a->den * b->num;
}
