/* readable reconstruction; identity: FUN_000639d4 @ 0x000639d4
 * public-name: gpio_pin_configure_dt
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_configure_dt                    <= FUN_000639d4 @ 0x000639d4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_99c53                             @ 0x00099c53
 *   rodata_99c84                             @ 0x00099c84   [INLINED -- G6 literal batch]
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_99cda                             @ 0x00099cda   [INLINED -- G6 literal batch]
 *   rodata_99dad                             @ 0x00099dad   [INLINED -- G6 literal batch]
 *   rodata_99de0                             @ 0x00099de0   [INLINED -- G6 literal batch]
 *   rodata_99e1e                             @ 0x00099e1e   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_000639d4 @ 0x639d4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../headers/g1_log.h"
typedef unsigned (*codep)(int,unsigned,unsigned);
extern void assert_post_action(int,unsigned);
extern int z_device_is_ready(int);
unsigned gpio_pin_configure_dt(int param_1){
  unsigned char bVar1; int iVar2; unsigned uVar3; unsigned uVar4; unsigned *puVar5; unsigned uVar6; unsigned uVar7;
  puVar5 = *(unsigned **)(param_1 + 4);
  iVar2 = z_device_is_ready(*puVar5);
  if (iVar2 != 0) {
    if (puVar5[1] == 0) { return 0; }
    iVar2 = z_device_is_ready(puVar5[1]);
    if (iVar2 != 0) {
      uVar7 = (unsigned)*(unsigned short *)((int)puVar5 + 10);
      iVar2 = puVar5[1];
      bVar1 = *(unsigned char *)(puVar5 + 2);
      puVar5 = *(unsigned **)(iVar2 + 8);
      if ((uVar7 & 0x30) == 0x30) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"(flags & ((1 << 4) | (1 << 5))) != ((1 << 4) | (1 << 5))"),0x00099c53,0x3ca);
        printk(((unsigned long)"\tPull Up and Pull Down should not be enabled simultaneously\n"));
        uVar3 = 0x3ca;
      } else if ((uVar7 & 6) == 4) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"(flags & (1 << 1)) != 0 || (flags & (1 << 2)) == 0"),0x00099c53,0x3d1);
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
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"(cfg->port_pin_mask & (gpio_port_pins_t)(1UL << (pin))) != 0U"),0x00099c53,0x3e4);
        printk(((unsigned long)"\tUnsupported pin\n"));
        uVar3 = 0x3e4;
      }
      assert_post_action(0x00099c53,uVar3);
    }
  }
  return 0xffffffed;
}
