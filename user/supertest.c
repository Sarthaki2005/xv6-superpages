#include "kernel/types.h"
#include "user/user.h"

int main() {
  printf("Running superpage test...\n");

  // Allocate 4MB — enough for 2 superpages
  int size = 4 * 1024 * 1024;
  char *buf = malloc(size);
  if (!buf) {
    printf("malloc failed\n");
    exit(1);
  }

  // Touch each 4KB page — forces page faults + actual mapping
  for (int i = 0; i < size; i += 4096) {
    buf[i] = i % 256;
  }

  printf("Touched every page in a 4MB region.\n");

  sleep(20); // Let you inspect page table manually if needed
  exit(0);
}
