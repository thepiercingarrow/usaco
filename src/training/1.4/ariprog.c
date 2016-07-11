/*
ID: thepier1
LANG: C
TASK: ariprog
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_BISQ 251
#define MAX_SEQ 10000

struct Test {
  int start, gap;
};

int works(int i, int gap, int N, int k, int bisq[]);
int cmpInt(int *a, int *b);
int cmpTest(struct Test *a, struct Test *b);

int main() {
  FILE *fin = fopen("ariprog.in", "r");
  FILE *fout = fopen("ariprog.out", "w");
  int i, j, k, N, M, bisq[MAX_BISQ * (MAX_BISQ + 1) / 2], count = 0;
  struct Test solutions[MAX_SEQ];
  fscanf(fin, "%d\n%d", &N, &M);
  fclose(fin);
  for (k = i = 0; i <= M; ++i) // generate bisquare list
    for (j = 0; j <= i; ++j) {
      bisq[k++] = i*i + j*j;
    }
  qsort(bisq, k, sizeof(int), (int (*)(const void *, const void *))cmpInt);
  i = 1;
  int leap = 0;
  while (bisq[i] != bisq[i - 1])
    ++i;
  while (i < k) {
    if (bisq[i] == bisq[i - 1])
      ++leap;
    else
      bisq[i - leap] = bisq[i];
    ++i;
  }
  k -= leap;
  for (i = 0; i < k; ++i)
    for (j = i + 1; j < k; ++j) { // check seq begins with bisq[i], bisq[j]...
      int gap = bisq[j] - bisq[i];
      if (works(i, gap, N, k, bisq)) {
	solutions[count].start = bisq[i];
	solutions[count].gap = gap;
	++count;
      }
    }
  qsort(solutions, count, sizeof(struct Test), (int (*)(const void *, const void *))cmpTest);
  for (i = 0; i < count; ++i)
    fprintf(fout, "%d %d\n", solutions[i].start, solutions[i].gap);
  if (!count)
    fprintf(fout, "NONE\n");
}

int works(int i, int gap, int N, int k, int bisq[]) {
  int l = N, target = bisq[i] + l * gap;
  int low, high = k - 1;
  int m = high;
  if (target - gap > bisq[k - 1])
    return 0;
  while (--l >= 2 ) {
    target -= gap;
    low = 0;
    m /= 2;
    while (bisq[m] != target) {
      if (bisq[m] > target) {
	if (bisq[m - 1] < target)
	  return 0;
    	high = m - 1;
    	m = (low + high) / 2;
      }
      else { // bisq[m] < target
	if (bisq[m + 1] > target)
	  return 0;
    	low = m + 1;
    	m = (high + low) / 2;
      }
    }
  }
  return 1;
}

int cmpInt(int *a, int *b) {
  return *a - *b;
}

int cmpTest(struct Test *a, struct Test *b) {
  if (a->gap - b->gap)
    return a->gap - b->gap;
  return a->start - b->start;
}
