#include "data.c"
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>

double get_time() {
  struct timeval t;
  struct timezone tzp;
  gettimeofday(&t, &tzp);
  return t.tv_sec + t.tv_usec * 1e-6;
}

unsigned long str_cmp(unsigned long, unsigned long, unsigned long);
unsigned long str_cmp_c(char *s1, char *s2, unsigned long len) {
  for (int i = 0; i <= len; i++) {
    if (s1[i] != s2[i])
      return 1;
  }
  return 0;
}

unsigned long search(unsigned long, unsigned long, unsigned char);

unsigned long search_c(unsigned char *data, unsigned long len,
                       unsigned char key) {
  int i = 0;
  while (i < len && data[i++] != key)
    ;
  return (i < len) * (i - 1) + (i >= len) * -1;
}

void print_results(const char *test_name, double asm_time, double c_time) {
  printf("[%s] =>\n\tASM: %.2lfms vs LLVM: %.2lfms\n", test_name, asm_time * 1000, c_time * 1000);
  double ratio = c_time / asm_time;
  if (ratio > 1) {
    printf("\tASM faster by %.2lfx\n", ratio);
  } else {
    printf("\tLLVM faster by %.2lfx\n", 1 / ratio);
  }
}

void benchmark_search() {
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

  print_results("String Search (scasb)", asm_time, c_time);
}

void benchmark_compare() {
  unsigned long len = sizeof(str_1) / sizeof(char *);
  int count = 10000;

  unsigned long asm_result = 0;
  double asm_time = get_time();
  for (int j = 0; j < count; j++)
    for (int i = 0; i < len; i++)
      asm_result += str_cmp((unsigned long)str_1[i], (unsigned long)str_2[i],
                            str_len[i] + 2);
  asm_time = get_time() - asm_time;

  unsigned long c_result = 0;
  double c_time = get_time();
  for (int j = 0; j < count; j++)
    for (int i = 0; i < len; i++)
      c_result += str_cmp_c(str_1[i], str_2[i], str_len[i]);
  c_time = get_time() - c_time;

  if (c_result != asm_result) {
    printf("Failed!: %lu vs %lu\n", asm_result, c_result);
  }

  print_results("String Compare (cmpsb)", asm_time, c_time);
}

int main() {
  benchmark_search();
  benchmark_compare();
}
