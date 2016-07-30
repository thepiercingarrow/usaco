/*
ID: thepier1
LANG: C
TASK: holstein
*/
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_V 25
#define MAX_G 15

void scoop(int scoops[], int num, int minvit);
int healthy(int scoops[], int num);

int V, G, req[MAX_V], vit[MAX_G][MAX_V], opt[MAX_G * MAX_V], minscoop = INT_MAX;

int main() {
  FILE *fio = fopen("holstein.in", "r");
  fscanf(fio, "%d\n", &V);
  for (int i = 0; i < V; ++i)
    fscanf(fio, "%d", req + i);
  fscanf(fio, "%d\n", &G);
  for (int i = 0; i < G; ++i)
    for (int j = 0; j < V; ++j)
      fscanf(fio, "%d", &vit[i][j]);
  fclose(fio);
  scoop(NULL, 0, -1);
  fio = fopen("holstein.out", "w");
  fprintf(fio, "%d ", minscoop);
  for (int i = 0; i < minscoop; ++i)
    fprintf(fio, i + 1 == minscoop? "%d\n" : "%d ", opt[i] + 1);
}

void scoop(int scoops[], int num, int minvit) {
  if (minvit == G)
    return;
  if (healthy(scoops, num)) {
    if (num < minscoop) {
      minscoop = num;
      for (int i = 0; i < num; ++i)
	opt[i] = scoops[i];
    }
    return;
  }
  for (int i = minvit + 1; i < G; ++i) {
    int myscoops[MAX_V];
    memcpy(myscoops, scoops, num * sizeof(int));
    myscoops[num] = i;
    scoop(myscoops, num + 1, i);
  }
}

int healthy(int scoops[], int num) {
  int myvits[MAX_V];
  memset(myvits, 0, V * sizeof(int));
  for (int i = 0; i < num; ++i)
    for (int j = 0; j < V; ++j)
      myvits[j] += vit[scoops[i]][j];
  for (int i = 0; i < V; ++i)
    if (myvits[i] < req[i])
      return 0;
  return 1;
}
