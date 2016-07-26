/*
ID: thepier1
LANG: C
TASK: sort3
*/
#include <stdio.h>
#include <string.h>

#define MAX_N 1000

int main() {
  FILE *fio = fopen("sort3.in", "r");
  int N, seq[MAX_N], num1 = 0, num2 = 0, num3 = 0;
  fscanf(fio, "%d\n", &N);
  int i;
  for (i = 0; i < N; ++i) {
    fscanf(fio, "%d\n", seq + i);
    if (seq[i] == 1)
      ++num1;
    else if (seq[i] == 2)
      ++num2;
    else
      ++num3;
  }
  fclose(fio);
  int nums[4][4];
  memset(nums, 0, sizeof nums);
  for (i = 0; i < num1; ++i) {
    if (seq[i] == 1)
      ++nums[1][1];
    else if (seq[i] == 2)
      ++nums[1][2];
    else
      ++nums[1][3];
  }
  for (num2 += i; i < num2; ++i) {
    if (seq[i] == 1)
      ++nums[2][1];
    else if (seq[i] == 2)
      ++nums[2][2];
    else
      ++nums[2][3];
  }
  for (num3 += i; i < num3; ++i) {
    if (seq[i] == 1)
      ++nums[3][1];
    else if (seq[i] == 2)
      ++nums[3][2];
    else
      ++nums[3][3];
  }
  int swaps = 0, tmp;
#define min(a, b) ((a) < (b) ? (a) : (b))
  tmp = min(nums[1][2], nums[2][1]);
  nums[1][2] -= tmp, nums[2][1] -= tmp;
  swaps += tmp;
  tmp = min(nums[1][3], nums[3][1]);
  nums[1][3] -= tmp, nums[3][1] -= tmp;
  swaps += tmp;
  tmp = min(nums[3][2], nums[2][3]);
  nums[3][2] -= tmp, nums[2][3] -= tmp;
  swaps += tmp;
#undef min
#define max(a, b) ((a) > (b) ? (a) : (b))
  if (nums[1][2] || nums[2][1])
    swaps += max(nums[1][2], nums[2][1]) * 2;
#undef max
  fio = fopen("sort3.out", "w");
  fprintf(fio, "%d\n", swaps);
}
