#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000620cc @ 0x000620cc
 * public-name: gpio_nrfx_configure_pin_list
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_nrfx_configure_pin_list             <= FUN_000620cc @ 0x000620cc
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
/* Reconstructed FUN_000620cc @ 0x620cc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../../headers/g1_log.h"
extern int assert_post_action(int, int);
extern int z_device_is_ready(void);

int gpio_nrfx_configure_pin_list(int param_1){
    int iVar5 = *(volatile int*)(param_1+4);
    int iVar6 = iVar5 + 0x28;
    int iVar2; uint32_t uVar7; uint8_t bVar1; volatile uint32_t *puVar8;
    uint32_t uVar9, uVar4, uVar3;
    while (1) {
        if (*(volatile int*)(iVar5+4) != 0){
            iVar2 = z_device_is_ready();
            if (iVar2==0) return -0x13;
            uVar7 = *(volatile uint16_t*)(iVar5+10);
            iVar2 = *(volatile int*)(iVar5+4);
            bVar1 = *(volatile uint8_t*)(iVar5+8);
            puVar8 = *(volatile uint32_t* volatile*)(iVar2+8);
            if ((uVar7 & 0x30)==0x30){
                printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"(flags & ((1 << 4) | (1 << 5))) != ((1 << 4) | (1 << 5))") /*=0x99c84*/,((unsigned long)&rodata_99c53) /*=0x99c53*/,0x3ca);
                printk(((unsigned long)"\tPull Up and Pull Down should not be enabled simultaneously\n") /*=0x99cda*/);
                uVar3 = 0x3ca; goto L62124;
            }
          L6212a:
            if ((uVar7 & 6)==4){
                printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"(flags & (1 << 1)) != 0 || (flags & (1 << 2)) == 0") /*=0x99dad*/,((unsigned long)&rodata_99c53) /*=0x99c53*/,0x3d1);
                uVar3 = 0x3d1; goto L62124;
            }
            uVar9 = 1u << bVar1;
            if ((uVar9 & **(volatile uint32_t* volatile*)(iVar2+4))==0){
                printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"(cfg->port_pin_mask & (gpio_port_pins_t)(1UL << (pin))) != 0U") /*=0x99de0*/,((unsigned long)&rodata_99c53) /*=0x99c53*/,0x3e4);
                printk(((unsigned long)"\tUnsupported pin\n") /*=0x99e1e*/);
                uVar3 = 0x3e4; goto L62124;
            }
            uVar4 = **(volatile uint32_t* volatile*)(iVar2+0x10);
            if ((int)(uVar7 << 0x1f) < 0) uVar9 = uVar9 | uVar4;
            else uVar9 = uVar4 & ~uVar9;
            **(volatile uint32_t* volatile*)(iVar2+0x10) = uVar9;
            iVar2 = ((int(*)(int,uint32_t,uint32_t))(*puVar8))(iVar2,(uint32_t)bVar1, uVar7|0x20000);
            if (iVar2 != 0) return iVar2;
        }
        iVar5 = iVar5 + 8;
        if (iVar6 == iVar5) return 0;
        continue;
      L62124:
        assert_post_action(((unsigned long)&rodata_99c53) /*=0x99c53*/, uVar3);
        goto L6212a;
    }
}
