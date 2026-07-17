#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084a24 @ 0x00084a24
 * public-name: ringbuf_flush_chunk
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ringbuf_flush_chunk                      <= FUN_00084a24 @ 0x00084a24
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* Reconstructed FUN_00084a24 @ 0x84a24  (parity: 300/300 trials, PROVEN) */

extern void memcpy(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

unsigned int ringbuf_flush_chunk(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar3 = *(volatile int*)(param_1+0xc);
    unsigned int uVar2 = *(volatile unsigned int*)(iVar3+0xc) - *(volatile unsigned int*)(iVar3+0x1c);
    unsigned int uVar1;
    if (uVar2 == 0) {
        uVar1 = 0;
    } else {
        if (uVar2 > 7) uVar2 = 8;
        *(volatile unsigned int*)(iVar3+0x14) = uVar2;
        *(volatile unsigned int*)(*(volatile int*)(param_1+0xc) + 0x10) = *(volatile unsigned int*)(*(volatile int*)(param_1+0xc)+0x18);
        iVar3 = *(volatile int*)(param_1+0xc);
        memcpy(*(volatile unsigned int*)(iVar3+0x18), *(volatile int*)(iVar3+0x1c)+*(volatile int*)(iVar3+8), uVar2, iVar3, param_4);
        uVar1 = 1;
    }
    return uVar1;
}
