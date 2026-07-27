/* Reconstructed FUN_000651d8 @ 0x651d8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void printk(unsigned long, ...);
extern void assert_post_action(unsigned int, unsigned int);
extern int arch_irq_is_enabled(int);
extern void arch_irq_enable(int);

void FUN_000651d8(void)
{
  if (*(volatile char*)(0x2000b31cUL + 4) == 0) {
    printk(0x99cbd, 0xf6acd, 0xf6a4e, 0x12e, 0);
    assert_post_action(0xf6a4e, 0x12e);
  }
  int iVar1 = arch_irq_is_enabled(5);
  if (iVar1 == 0) {
    arch_irq_enable(5);
  }
  *(volatile uint32_t*)0x50005518UL = 1;
  *(volatile uint32_t*)0x50005514UL = 1;
  *(volatile uint32_t*)0x50005580UL = 1;
}

