#include <stdio.h>
#include <stdlib.h>

void sse(float a[], float b[], float c[]) {
  asm volatile (
                "movups %[a], %%xmm0\n"
                "movups %[b], %%xmm1\n"
                "mulps %%xmm1, %%xmm0\n"
                "movups %%xmm0, %[c]\n"
                :
                : [a]"m"(*a), [b]"m"(*b), [c]"m"(*c)
                : "%xmm0", "%xmm1");
}

int main(int argc, char** argv) {

  int iterations_num = atoi(argv[1]);

  float a[4] = { 300.0, 4.0, 4.0, 12.0 };
  float b[4] = { 1.5, 2.5, 3.5, 4.5 };
  float c[4] = { 0.0, 0.0, 0.0, 0.0 };

  for (int i = 0; i < iterations_num; i++) {
    sse(a, b, c);
  }

  return 0;
}
