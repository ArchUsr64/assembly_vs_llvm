#include <stdio.h>
#include <string.h>

unsigned long search(unsigned long, unsigned long, unsigned char);

unsigned long search_c(unsigned char *data, unsigned long len, unsigned char key) {
  int i = 0;
  while (i < len && data[i++] != key)
    ;
  return (i < len) * (i - 1) + (i >= len) * -1;
}

int main() {
  unsigned char data[] = {
      190, 191, 192, 193, 194, 195, 196, 197, 197, 198, 198, 199, 199, 199, 199,
      200, 200, 200, 199, 199, 199, 199, 198, 198, 197, 197, 196, 195, 194, 194,
      193, 192, 191, 190, 189, 188, 187, 186, 184, 183, 182, 182, 181, 180, 179,
      178, 178, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 178, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 178, 178, 178,
      178, 178, 178, 178, 178, 178, 178, 177, 177, 177, 177, 177, 177, 177, 177,
      177, 177, 177, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176,
      176, 176, 176, 175, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165,
      164, 163, 162, 161, 161, 160, 159, 159, 158, 158, 158, 158, 158, 158, 159,
      159, 160, 160, 161, 162, 163, 165, 166, 167, 169, 170, 172, 174, 175, 177,
      179, 181, 182, 184, 186, 188, 189, 191, 192, 193, 194, 195, 196, 197, 197,
      198, 198, 198, 198, 198, 198, 198, 198, 198, 197, 197, 196, 196, 195, 194,
      193, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 181,
      180, 179, 179, 179, 178, 178, 178, 179, 179, 180, 181, 182, 183, 184, 184,
      185, 186, 187, 188, 188, 189, 189, 190, 190, 191, 191, 191, 192, 192, 192,
      192, 192, 192, 192, 191, 191, 191, 190, 190, 190, 189, 189, 188, 187, 187,
      186, 186, 185, 184, 184, 183, 182, 182, 181, 181, 180, 180, 180, 180, 179,
      179, 179, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 178, 177, 177, 176, 175,
      174, 173, 172, 171, 170, 169, 168, 167, 167, 166, 165, 164, 164, 163, 163,
      163, 163, 163, 163, 163, 163, 163, 164, 165, 165, 166, 167, 168, 169, 171,
      172, 173, 175, 176, 178, 179, 181, 183, 184, 186, 188, 189, 191, 192, 193,
      195, 196, 197, 198, 199, 200, 201, 202, 202, 203, 203, 203, 204, 204, 204,
      204, 203, 203, 203, 202, 202, 201, 200, 199, 199, 198, 197, 195, 194, 193,
      192, 191, 189, 188, 187, 186, 185, 183, 182, 181, 181, 180, 179, 179, 178,
      178, 178, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 180, 180, 180, 180, 180, 180, 180,
      180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 179, 179, 179,
      179, 179, 179, 179, 179, 179, 179, 179, 179, 178, 178, 177, 176, 175, 174,
      173, 172};
  unsigned long len = sizeof(data);
  unsigned char key = 182;
  unsigned long asm_result =
      search((unsigned long)data, (unsigned long)len, key);
  unsigned long c_result = search_c(data, len, key);
  if (c_result != asm_result) {
    printf("Failed!: %lu vs %lu\n", asm_result, c_result);
  }
}
