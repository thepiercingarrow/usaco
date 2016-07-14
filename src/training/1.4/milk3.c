/*
ID: thepier1
LANG: C
TASK: milk3
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAP 20

struct Bucket {
  int cap, fill;
};

struct Set {
  struct Bucket A, B, C;
};

void search(struct Set set);
void pour(struct Set *set, struct Bucket *from, struct Bucket *to);
int inSnaps(struct Set set);
int cmpset(struct Set a, struct Set b);

int solutions[MAX_CAP + 1], snaps = 0;
struct Set snapshots[(MAX_CAP + 2) * (MAX_CAP + 1) / 2];

int main() {
  FILE *fin = fopen("milk3.in", "r");
  FILE *fout = fopen("milk3.out", "w");
  struct Set set;
  fscanf(fin, "%d %d %d\n", &set.A.cap, &set.B.cap, &set.C.cap);
  memset(solutions, 0, sizeof solutions);
  set.A.fill = set.B.fill = 0;
  set.C.fill = set.C.cap;
  search(set); // recursively search for all solutions
  int i;
  for (i = set.C.cap; i >= 0; ++i)
    if (solutions[i] == 1)
      break;
  if (solutions[i]) {
    int j;
    for (j = 0; j < i; ++j)
      if (solutions[j])
	fprintf(fout, "%d ", j);
    fprintf(fout, "%d", j);
  }
  putc('\n', fout);
}

void search(struct Set set) {
  printf("search\n");
  if (inSnaps(set))
    return; // we've been here before
  snapshots[snaps++] = set; // take a snapshot
  if (set.A.fill == 0)
    solutions[set.C.fill] = 1; // add to solutions
  struct Set virtualSet;
#define Pour(a, b) (virtualSet = set, pour(&virtualSet, &virtualSet.a, &virtualSet.b))
  Pour(A, B);
  Pour(A, C);
  Pour(B, A);
  Pour(B, C);
  Pour(C, A);
  Pour(C, B);
#undef Pour
}

void pour(struct Set *set, struct Bucket *from, struct Bucket *to) {
  printf("pour\n");
  if (from->fill && to->cap != to->fill) {
    if (from->fill > to->cap - to->fill) { // careful fillup
      from->fill -= to->cap - to->fill;
      to->fill = to->cap;
    }
    else { // dump
      to->fill += from->fill;
      from->fill = 0;
    }
    search(*set);
  }
}

int inSnaps(struct Set set) {
  int i;
  for (i = 0; i < snaps; ++i)
    if (cmpset(snapshots[i], set))
      return 1;
  return 0;
}

int cmpset(struct Set a, struct Set b) {
  if (a.A.fill == b.A.fill)
    if (a.B.fill == b.B.fill)
      if (a.C.fill == b.C.fill)
	return 1;
  return 0;
}
