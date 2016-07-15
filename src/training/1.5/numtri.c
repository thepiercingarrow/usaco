/*
ID: thepier1
LANG: C
TASK: numtri
*/
#include <stdio.h>
#include <string.h>

#define MAX_R 1000

#define max(a, b) ((a)>(b)?(a):(b))

void scanRow(int row[MAX_R], int maxsums[MAX_R], int R);

int main() {
  FILE *fin = fopen("numtri.in", "r");
  FILE *fout = fopen("numtri.out", "w");
  int i, j, R, rows[MAX_R][MAX_R], maxsums[MAX_R];
  fscanf(fin, "%d\n", &R);
  for (i = 0; i < R; ++i)
    for (j = 0; j <= i; ++j)
      fscanf(fin, "%d", &rows[i][j]);
  maxsums[0] = rows[0][0];
  for (i = 1; i < R; ++i)
      scanRow(rows[i], maxsums, i + 1);
  int max = 0;
  for (i = 0; i < R; ++i)
    if (maxsums[i] > max)
      max = maxsums[i];
  fprintf(fout, "%d\n", max);
}

void scanRow(int row[MAX_R], int maxsums[MAX_R], int R) {
  int i, prevsums[MAX_R];
  memcpy(prevsums, maxsums, R * sizeof(int));
  maxsums[0] += row[0];
  maxsums[R - 1] = prevsums[R - 2] + row[R - 1];
  for (i = 1; i < R - 1; ++i)
    maxsums[i] = row[i] + max(prevsums[i - 1], prevsums[i]);
}
