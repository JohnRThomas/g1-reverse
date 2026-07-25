/* P4 iteration 26/27 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21000570[];
extern unsigned char g1_net_ram_blk_210045e0[];
#define G1N_21000580 ((unsigned long)(g1_net_ram_blk_21000570 + 0x10))
#define G1N_21004604 ((unsigned long)(g1_net_ram_blk_210045e0 + 0x24))
#else
#define G1N_21000580 0x21000580ul
#define G1N_21004604 0x21004604ul
#endif
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
  *(volatile unsigned int *)G1N_21004604 = param_1;
  if (*(volatile int *)G1N_21000580 > 1) {
    FUN_01039722(0x0103cf0b);
  }
  return 0;
}
