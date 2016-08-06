/*
ID: thepier1
LANG: C
TASK: preface
*/
#include <stdio.h>
#include <string.h>

#define N_MAX 3500

struct Nums {
  int I, V, X, L, C, D, M;
};

void add(int num);

struct Nums takes[N_MAX];

int main() {
  FILE *fio = fopen("preface.in", "r");
  int N;
  fscanf(fio, "%d\n", &N);
  fclose(fio);
  memset(takes, 0, sizeof takes);
  takes[4].I = takes[4].V = 1;
  takes[9].I = takes[9].X = 1;
  for (int i = 1; i <= N; ++i)
    add(i);
  int I, V, X, L, C, D, M;
  I = V = X = L = C = D = M = 0;
  for (int i = 0; i <= N; ++i) {
    I += takes[i].I;
    V += takes[i].V;
    X += takes[i].X;
    L += takes[i].L;
    C += takes[i].C;
    D += takes[i].D;
    M += takes[i].M;
  }
  fio = fopen("preface.out", "w");
  if (N >= 1)
    fprintf(fio, "I %d\n", I);
  if (N >= 5)
    fprintf(fio, "V %d\n", V);
  if (N >= 9)
    fprintf(fio, "X %d\n", X);
  if (N >= 40)
    fprintf(fio, "L %d\n", L);
  if (N >= 100)
    fprintf(fio, "C %d\n", C);
  if (N >= 500)
    fprintf(fio, "D %d\n", D);
  if (N >= 1000)
    fprintf(fio, "M %d\n", M);
}

void add(int num) {
  if (num >= 1000) {
    takes[num] = takes[num - 1000];
    ++takes[num].M;
    return;
  }
  if (num >= 900) {
    takes[num] = takes[num - 900];
    ++takes[num].C;
    ++takes[num].M;
    return;
  }
  if (num >= 500) {
    takes[num] = takes[num - 500];
    ++takes[num].D;
    return;
  }
  if (num >= 400) {
    takes[num] = takes[num - 400];
    ++takes[num].C;
    ++takes[num].D;
    return;
  }
  if (num >= 100) {
    takes[num] = takes[num - 100];
    ++takes[num].C;
    return;
  }
  if (num >= 90) {
    takes[num] = takes[num - 90];
    ++takes[num].X;
    ++takes[num].C;
    return;
  }
  if (num >= 50) {
    takes[num] = takes[num - 50];
    ++takes[num].L;
    return;
  }
  if (num >= 40) {
    takes[num] = takes[num - 40];
    ++takes[num].X;
    ++takes[num].L;
    return;
  }
  if (num >= 10) {
    takes[num] = takes[num - 10];
    ++takes[num].X;
    return;
  }
  if (num == 9)
    return;
  if (num >= 5) {
    takes[num] = takes[num - 5];
    ++takes[num].V;
    return;
  }
  if (num == 4)
    return;
  takes[num] = takes[num - 1];
  ++takes[num].I;
}
