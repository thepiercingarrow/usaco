/*
ID: thepier1
LANG: C
TASK: runround
*/
#include <stdio.h>

#define N_MAX 40

int isround(unsigned long int x);
int digitsdistinct(char num[11]);

int main() {
  unsigned long int M;
  FILE *fio = fopen("runround.in", "r");
  fscanf(fio, "%lu\n", &M);
  fclose(fio);

  while (!isround(++M))
    ;

  fio = fopen("runround.out", "w");
  fprintf(fio, "%lu\n", M);
}

int isround(unsigned long int x) {
  char num[11], yet[11] = {0}, yetcount = 0; // round numbers cannot have more than 10 digits
  sprintf(num, "%lu", x);
  int len;
  if (!(len = digitsdistinct(num)))
    return 0;
  int i = 0;
  while (++yetcount < len) {
    yet[i] = 1;
    i = (i + num[i] - '0') % len;
    if (yet[i])
      return 0;
  }
  return  (i + num[i] - '0') % len == 0;
}

int digitsdistinct(char num[11]) { // return legnth if true, otherwise return 0
  int i, j;
  for (i = 0; num[i]; ++i)
    if (num[i] == '0')
      return 0; // just a quick check
  for (i = 0; num[i]; ++i)
    for (j = i + 1; num[i] && num[j]; ++j)
      if (num[i] == num[j])
	return 0;
  return i;
}
