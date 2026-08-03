#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102ece0 @ 0x0102ece0
 * public-name: FUN_0102ece0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102ece0 @ 0x102ece0  (parity 300 trials PROVEN) */

/* This is Zephyr's arch_new_thread(): it plants the initial exception frame
 * (r0..r3 = entry/p1/p2/p3 at stack_ptr-0x20.., PC at stack_ptr-8, xPSR
 * 0x01000000 at stack_ptr-4) and stores the PSP in thread->callee_saved.psp.
 *
 * P4 iteration 18: the planted PC literal 0x0102cc3d is the shipped image's
 * Thumb pointer to `z_thread_entry`, i.e. a CPUNET *runtime* address; its
 * analysis address is 0x0102cc3d - 0x800 = 0x0102c43d, and disassembling
 * netcore_image.bin at analysis 0x0102c43c gives
 *     push {r7, lr} / mov r5,r0 / mov r6,r1 / mov r7,r2 / mov r8,r3 /
 *     bl <z_impl_z_current_get> / mov r3,r0 / bl <__aeabi_read_tp> /
 *     mov r4,r0 / ldr.w r9,[pc,#24] / mov r2,r8 / str.w r3,[r9,r0] /
 *     mov r1,r6 / mov r0,r7 / blx r5
 * which is instruction-for-instruction our linked z_thread_entry.  Left
 * unrelocated, EVERY CPUNET thread started life with PC = 0x0102cc3c, which in
 * the cohesive link is the middle of FUN_01033354's `ldmia.w sp!, {r4, lr}` —
 * so the first thread ever scheduled popped a garbage LR and took a
 * USAGE FAULT ("Illegal use of the EPSR") on the following `bx lr`.  Measured
 * in iteration 18 §18.3 (net PC trace index 318350, right after the first
 * z_arm_pendsv). */
#ifdef G1_COHESIVE_BUILD
extern void z_thread_entry(void *entry, void *p1, void *p2, void *p3);
#define G1_NET_THREAD_ENTRY ((unsigned int)(unsigned long)&z_thread_entry)
#else
#define G1_NET_THREAD_ENTRY 0x0102cc3du
#endif

void FUN_0102ece0(int param_1, unsigned int param_2, int param_3, unsigned int param_4,
                   unsigned int param_5, unsigned int param_6, unsigned int param_7)
{
  *(unsigned int*)(param_3 - 0x20) = param_4;
  unsigned int uVar1 = G1_NET_THREAD_ENTRY;
  *(unsigned int*)(param_3 - 0x1c) = param_5;
  *(unsigned int*)(param_3 - 0x18) = param_6;
  *(unsigned int*)(param_3 - 8) = uVar1 & 0xfffffffe;
  *(unsigned int*)(param_3 - 0x14) = param_7;
  *(unsigned int*)(param_3 - 4) = 0x1000000;
  *(int*)(param_1 + 0x50) = param_3 - 0x20;
  *(unsigned int*)(param_1 + 0x8c) = 0;
}
