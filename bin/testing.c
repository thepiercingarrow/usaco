#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE *ftests = fopen(argv[0], "r");
  FILE *fin = fopen(argv[1], "w");
  chdir(
  int time, tsize;
  fscanf(test, "Time: %d\n", &time);
  while (fscanf(ftests, "------- test %d [length %d bytes] ----", NULL, &tsize) != EOF) {
    int i;
    for (i = 0; i < tsize; ++i)
      putc(getc(ftests), fin);
    execl
  }
}
