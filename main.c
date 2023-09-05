#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "data.c"

double get_time() {
  struct timeval t;
  struct timezone tzp;
  gettimeofday(&t, &tzp);
  return t.tv_sec + t.tv_usec * 1e-6;
}

unsigned long search(unsigned long, unsigned long, unsigned char);

unsigned long search_c(unsigned char *data, unsigned long len,
                       unsigned char key) {
  int i = 0;
  while (i < len && data[i++] != key)
    ;
  return (i < len) * (i - 1) + (i >= len) * -1;
}

int main() {
  unsigned long len = sizeof(data);
  unsigned char const key = 172;
  int count = 1000000;

  unsigned long asm_result = 0;
  unsigned char key_asm = key;
  double asm_time = get_time();
  for (int i = 0; i < count; i++)
    asm_result += search((unsigned long)data, len, key_asm++);
  asm_time = get_time() - asm_time;

  unsigned long c_result = 0;
  unsigned char key_c = key;
  double c_time = get_time();
  for (int i = 0; i < count; i++)
    c_result += search_c(data, len, key_c++);
  c_time = get_time() - c_time;
  if (c_result != asm_result) {
    printf("Failed!: %lu vs %lu\n", asm_result, c_result);
  }
  printf("ASM: %lf vs LLVM: %lf\n", asm_time, c_time);
  double ratio = c_time / asm_time;
  if (ratio > 1) {
    printf("ASM faster by %.2lfx\n", ratio);
  } else {
    printf("LLVM faster by %.2lfx\n", ratio);
  }
}
