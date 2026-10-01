// user/bench_seq.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static inline uint64 r_cycle(void) {
  uint64 c;
  asm volatile("rdcycle %0" : "=r" (c));
  return c;
}

static void print_cycles(uint64 c) {
  if (c >= 1000000) {
    printf("%d,%03d,%03d", 
      (int)(c / 1000000),
      (int)((c % 1000000) / 1000),
      (int)(c % 1000));
  } else if (c >= 1000) {
    printf("%d,%03d", (int)(c / 1000), (int)(c % 1000));
  } else {
    printf("%d", (int)c);
  }
}

#define MB (1024 * 1024)
#define SIZE (32 * MB)

int
main(int argc, char *argv[])
{
  printf("=========================================\n");
  printf("  xv6 Sequential Streaming (bench_seq)    \n");
  printf("=========================================\n");
  printf("Allocating %d MB buffer...\n", SIZE / MB);

  char *buf = sbrk(SIZE);
  if(buf == (char*)-1){
    printf("Allocation failed\n");
    exit(1);
  }

  // 1. Sequential Write Test (64-byte step)
  printf("Streaming sequential writes (32 MB)...\n");
  uint64 start_w = r_cycle();
  for(int i = 0; i < SIZE; i += 64){
    buf[i] = (char)(i & 0x7F);
  }
  uint64 end_w = r_cycle();

  // 2. Sequential Read Test
  printf("Streaming sequential reads (32 MB)...\n");
  volatile int sum = 0;
  uint64 start_r = r_cycle();
  for(int i = 0; i < SIZE; i += 64){
    sum += buf[i];
  }
  uint64 end_r = r_cycle();

  printf("Write elapsed: ");
  print_cycles(end_w - start_w);
  printf(" cycles\n");

  printf("Read elapsed:  ");
  print_cycles(end_r - start_r);
  printf(" cycles\n");

  printf("Checksum: %d\n", sum);
  printf("=========================================\n");

  sbrk(-SIZE);
  exit(0);
}
