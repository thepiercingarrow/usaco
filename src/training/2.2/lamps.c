/*
ID: thepier1
LANG: C
TASK: lamps
 */
#include <stdio.h>

int lamps[101]; // 1 through 100
int lampnum;
int possible = 0;

void c(FILE *fout, int perm);

int main() {
  int presses;
  FILE *fin = fopen("lamps.in", "r");
  fscanf(fin, "%d %d", &lampnum, &presses);
  int i;
  for (i = 1; i <= lampnum; ++i)
    lamps[i] = -1;
  while (1) {
    int tmp;
    fscanf(fin, "%d", &tmp);
    if (tmp == -1)
      break;
    lamps[tmp] = 1;
  }
  while (1) {
    int tmp;
    fscanf(fin, "%d", &tmp);
    if (tmp == -1)
      break;
    lamps[tmp] = 0;
  }
  fclose(fin);
  FILE *fout = fopen("lamps.out", "w");
#define a(b) c(fout, b)
  if (presses == 0)
    a(0b000);
  else if (presses == 1) {
    a(0b110);
    a(0b100);
    a(0b001);
    a(0b010);
  }
  else if (presses == 2) {
    a(0b110);
    a(0b011);
    a(0b100);
    a(0b111);
    a(0b010);
    a(0b101);
    a(0b000);
  }
  else {
    a(0b110);
    a(0b011);
    a(0b100);
    a(0b001);
    a(0b111);
    a(0b010);
    a(0b101);
    a(0b000);
  }
#undef a
  if (!possible)
    fprintf(fout, "IMPOSSIBLE\n");
  return 0;
}

void c(FILE *fout, int perm) {
  int lperm[101];
  int i;
  for (i = 1; i <= lampnum; ++i)
    lperm[i] = 1;
  if (perm & 0b100) {
    // swap odd ones
    for (i = 1; i <= lampnum; i += 2)
      lperm[i] = !lperm[i];
  }
  if (perm & 0b010) {
    // swap even ones
    for (i = 2; i <= lampnum; i += 2)
      lperm[i] = !lperm[i];
  }
  if (perm & 0b001) {
    // swap 3k + 1
    for (i = 1; i <= lampnum; i += 3)
      lperm[i] = !lperm[i];
  }
  // compare lperm[] with lamps[]
  for (i = 1; i <= lampnum; ++i)
    if (lamps[i] > -1 && lamps[i] != lperm[i])
      return;
  for (i = 1; i <= lampnum; ++i)
    fprintf(fout, "%c", lperm[i] + '0');
  putc('\n', fout);
  possible = 1;
  return;
}
