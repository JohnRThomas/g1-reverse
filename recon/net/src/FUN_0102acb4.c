/* net-core FUN_0102acb4 @ 0x102acb4  (parity 300 trials PROVEN) */

extern void FUN_01039722(unsigned int a);

#ifdef G1_COHESIVE_BUILD
#include <stdint.h>
extern int FUN_0102ab50(const void *endpoint);
extern int FUN_0102abac(const void *data, uint32_t size);
#define G1_IPC_SEND_CALLBACK ((unsigned int)(uintptr_t)&FUN_0102abac) /*=0x0102b3ad*/
#define G1_IPC_REGISTER_CALLBACK ((unsigned int)(uintptr_t)&FUN_0102ab50) /*=0x0102b351*/
#else
#define G1_IPC_SEND_CALLBACK 0x0102b3ad
#define G1_IPC_REGISTER_CALLBACK 0x0102b351
#endif

unsigned int FUN_0102acb4(unsigned int param_1)
{
  *(unsigned int *)(param_1 + 0x60) = G1_IPC_SEND_CALLBACK;
  *(unsigned int *)(param_1 + 0x64) = G1_IPC_REGISTER_CALLBACK;
  *(volatile unsigned int *)0x21004604 = param_1;
  if (*(volatile int *)0x21000580 > 1) {
    FUN_01039722(0x0103cf0b);
  }
  return 0;
}
