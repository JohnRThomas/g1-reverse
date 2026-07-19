/* readable reconstruction; identity: FUN_000506ac @ 0x000506ac
 * public-name: arm_usage_fault_helper
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arm_usage_fault_helper                   <= FUN_000506ac @ 0x000506ac
 *   arm_fault_forward_handler                <= FUN_00080780 @ 0x00080780
 * address symbols (name @ address):
 *   rodata_88258                             @ 0x00088258
 *   rodata_f1e81                             @ 0x000f1e81
 *   rodata_f1e99                             @ 0x000f1e99
 *   rodata_f1eac                             @ 0x000f1eac
 *   rodata_f1ec6                             @ 0x000f1ec6
 *   rodata_f1ef0                             @ 0x000f1ef0
 *   rodata_f1f0e                             @ 0x000f1f0e
 *   rodata_f1f33                             @ 0x000f1f33
 *   rodata_f1f4d                             @ 0x000f1f4d
 */
/* Reconstructed FUN_000506ac @ 0x506ac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int arm_fault_forward_handler(int,...);
unsigned int arm_usage_fault_helper(void)
{
  unsigned int uVar1;
  unsigned int a[2];
  a[1] = 0xf1e81; a[0] = 2;
  arm_fault_forward_handler(0x88258,0x1040,a);
  if (*(volatile int*)0xe000ed28UL << 6 < 0) { a[0]=2; a[1]=0xf1e99; arm_fault_forward_handler(0x88258,0x1040,a); uVar1=0x1e; }
  else uVar1=0x1d;
  if (*(volatile int*)0xe000ed28UL << 7 < 0) { a[1]=0xf1eac; a[0]=2; arm_fault_forward_handler(0x88258,0x1040,a); uVar1=0x1f; }
  if (*(volatile int*)0xe000ed28UL << 0xb < 0) { a[1]=0xf1ec6; a[0]=2; arm_fault_forward_handler(0x88258,0x1040,a); uVar1=2; }
  if (*(volatile int*)0xe000ed28UL << 0xc < 0) { a[1]=0xf1ef0; a[0]=2; arm_fault_forward_handler(0x88258,0x1040,a); uVar1=0x21; }
  if (*(volatile int*)0xe000ed28UL << 0xd < 0) { a[1]=0xf1f0e; a[0]=2; arm_fault_forward_handler(0x88258,0x1040,a); uVar1=0x22; }
  if (*(volatile int*)0xe000ed28UL << 0xe < 0) { a[1]=0xf1f33; a[0]=2; arm_fault_forward_handler(0x88258,0x1040,a); uVar1=0x23; }
  if (*(volatile int*)0xe000ed28UL << 0xf < 0) { a[1]=0xf1f4d; a[0]=2; arm_fault_forward_handler(0x88258,0x1040,a); uVar1=0x24; }
  *(volatile unsigned int*)0xe000ed28UL = ~((unsigned int)~(*(volatile int*)0xe000ed28UL << 0x10) >> 0x10);
  return uVar1;
}
