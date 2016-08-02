/*
ID: thepier1
LANG: C
TASK: hamming
*/
#include <stdio.h>

#define N_MAX 64

void append(int seq[], int num);
int works(int seq[], int num, int new);
int hamming(int a, int b);
int pow2(int x);

int N, B, D;

int main() {
  FILE *fio = fopen("hamming.in", "r");
  fscanf(fio, "%d %d %d\n", &N, &B, &D);
  fclose(fio);

  int seq[N_MAX];
  seq[0] = 0;
  append(seq, 1);
}

void append(int seq[], int num) {
  if (num == N) {
    FILE *fio = fopen("hamming.out", "w");
    for (int i = 0; i < num; ++i)
      fprintf(fio, i == num - 1 || !((i + 1) % 10) ? "%d\n" : "%d ", seq[i]);
    return;
  }
  int i = seq[num - 1] + 1;
  while (!works(seq, num, i))
    ++i;
  seq[num] = i;
  append(seq, num + 1);
}

int works(int seq[], int num, int new) {
  for (int i = 0; i < num; ++i)
    if (hamming(seq[i], new) < D)
      return 0;
  return 1;
}

int hamming(int a, int b) {
  int i, dist = 0, xor = a ^ b;
  for (i = 0; i < B; ++i)
    dist += xor & pow2(i) ? 1 : 0;
  return dist;
}

int pow2(int x) {
  int i, pow = 1;
  for (i = 0; i < x; ++i)
    pow *= 2;
  return pow;
}
