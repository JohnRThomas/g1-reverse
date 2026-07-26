#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   0x000661cc       => struct g1_layout_nrfx_pdm_cb__global_1324               [global_1324; library]
 *   param_1          => struct g1_layout_nrfx_pdm_config__param_0334            [param_0334; library]
 * Raw function identity: 0x0006615c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0006615c @ 0x0006615c
 * public-name: nrfx_pdm_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   pdm_configure_pins                       <= FUN_00066050 @ 0x00066050
 *   nrfx_pdm_init                            <= FUN_0006615c @ 0x0006615c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6abf                             @ 0x000f6abf   [INLINED -- G6 literal batch]
 *   rodata_f6c00                             @ 0x000f6c00   [INLINED -- G6 literal batch]
 *   rodata_f6ceb                             @ 0x000f6ceb
 *   g_pdm_cb                                 @ 0x2000b330
 */
/* Reconstructed FUN_0006615c @ 0x6615c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned,unsigned,unsigned,unsigned);
extern long long assert_post_action(unsigned,unsigned);
extern void pdm_configure_pins(void);
unsigned nrfx_pdm_init(int param_1, int param_2){
    unsigned r0v = (unsigned)param_1;
    unsigned r1v = (unsigned)param_2;
    if (r0v != 0) goto L_174;
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"p_config") /*=0xf6c00*/,((unsigned long)&rodata_f6ceb) /*=0xf6ceb*/,0x78);
    { long long r=assert_post_action(((unsigned long)&rodata_f6ceb) /*=0xf6ceb*/,0x78); r0v=(unsigned)r; r1v=(unsigned)((unsigned long long)r>>32);}
L_174:
    if (r1v != 0) goto L_186;
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"event_handler") /*=0xf6abf*/,((unsigned long)&rodata_f6ceb) /*=0xf6ceb*/,0x79);
    { long long r=assert_post_action(((unsigned long)&rodata_f6ceb) /*=0xf6ceb*/,0x79); r0v=(unsigned)r; r1v=(unsigned)((unsigned long long)r>>32);}
    goto L_174;
L_186:
    {
        volatile unsigned char* p = (volatile unsigned char*)((unsigned long)&g_pdm_cb) /*=0x2000b330*/;
        if (*(volatile unsigned char*)(p + 0x10) != 0) return 0xbad0005;
        *(volatile int*)(p + 4) = 0;
        *(volatile int*)(p + 8) = 0;
        *(volatile unsigned short*)(p + 0x12) = 0;
        *(volatile unsigned char*)(p + 0x11) = 0;
        unsigned char uVar1 = *(unsigned char*)(r0v + 0x15);
        *(volatile int*)p = (int)r1v;
        *(volatile unsigned char*)(p + 0x15) = uVar1;
        if (*(unsigned char*)(r0v + 0x10) > 0x50) return 0xbad0004;
        if (*(unsigned char*)(r0v + 0x11) > 0x50) return 0xbad0004;
        pdm_configure_pins();
        *(volatile unsigned char*)(p + 0x10) = 1;
        return 0xbad0000;
    }
}
