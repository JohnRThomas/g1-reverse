#include "g1_app_symbols.h"
/* named: FUN_000639d4 */
/* Reconstructed FUN_000639d4 @ 0x639d4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef unsigned (*codep)(int,unsigned,unsigned);
extern void assert_post_action(int,unsigned);
extern void printk(int,...);
extern int z_device_is_ready(int);
unsigned FUN_000639d4(int param_1){
  unsigned char bVar1; int iVar2; unsigned uVar3; unsigned uVar4; unsigned *puVar5; unsigned uVar6; unsigned uVar7;
  puVar5 = *(unsigned **)(param_1 + 4);
  iVar2 = z_device_is_ready(*puVar5);
  if (iVar2 != 0) {
    if (puVar5[1] == 0) { return 0; }
    iVar2 = z_device_is_ready(0);
    if (iVar2 != 0) {
      uVar7 = (unsigned)*(unsigned short *)((int)puVar5 + 10);
      iVar2 = puVar5[1];
      bVar1 = *(unsigned char *)(puVar5 + 2);
      puVar5 = *(unsigned **)(iVar2 + 8);
      if ((uVar7 & 0x30) == 0x30) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"(flags & ((1 << 4) | (1 << 5))) != ((1 << 4) | (1 << 5))" /*=0x99c84*/,"WEST_TOPDIR/zephyr/include/zephyr/drivers/gpio.h" /*=0x99c53*/,0x3ca);
        printk("\tPull Up and Pull Down should not be enabled simultaneously\n" /*=0x99cda*/);
        uVar3 = 0x3ca;
      } else if ((uVar7 & 6) == 4) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"(flags & (1 << 1)) != 0 || (flags & (1 << 2)) == 0" /*=0x99dad*/,"WEST_TOPDIR/zephyr/include/zephyr/drivers/gpio.h" /*=0x99c53*/,0x3d1);
        uVar3 = 0x3d1;
      } else {
        uVar6 = 1u << (unsigned)bVar1;
        if ((uVar6 & **(unsigned **)(iVar2 + 4)) != 0) {
          uVar4 = **(unsigned **)(iVar2 + 0x10);
          if ((int)(uVar7 << 0x1f) < 0) { uVar4 = uVar4 | uVar6; }
          else { uVar4 = uVar4 & ~uVar6; }
          **(unsigned **)(iVar2 + 0x10) = uVar4;
          uVar3 = ((codep)*puVar5)(iVar2,(unsigned)bVar1,uVar7 | 0x400);
          return uVar3;
        }
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"(cfg->port_pin_mask & (gpio_port_pins_t)(1UL << (pin))) != 0U" /*=0x99de0*/,"WEST_TOPDIR/zephyr/include/zephyr/drivers/gpio.h" /*=0x99c53*/,0x3e4);
        printk("\tUnsupported pin\n" /*=0x99e1e*/);
        uVar3 = 0x3e4;
      }
      assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/drivers/gpio.h" /*=0x99c53*/,uVar3);
    }
  }
  return 0xffffffed;
}

