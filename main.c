#include <stdio.h>
#include <string.h>

unsigned long search(unsigned long, unsigned long, char);

int main() {
  char *data = "helloassembly!";
  unsigned long len = strlen(data);
  for (unsigned long i = 0; i < len; i++)
    printf("Found '%c' at index: %lu\n", data[i],
           search((unsigned long)data, (unsigned long)len, data[i]));
}
