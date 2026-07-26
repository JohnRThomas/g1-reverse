/* readable reconstruction; identity: FUN_00067f1c @ 0x00067f1c
 * public-name: nrfx_dppi_channel_slot_reset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_dppi_channel_slot_reset             <= FUN_00067f1c @ 0x00067f1c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f79c8                             @ 0x000f79c8
 *   rodata_f7a3f                             @ 0x000f7a3f
 *   m_dppi_channels                          @ 0x2000b41c
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_00067f1c @ 0x67f1c  (parity: 300/300 trials, PROVEN) */

extern unsigned long long assert_post_action(unsigned int a,unsigned int b);

void nrfx_dppi_channel_slot_reset(int *param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned char idx = *(volatile unsigned char*)((char*)param_1+4);
    volatile unsigned char *tbl = (volatile unsigned char*)0x2000b41cUL;
    int *basePtr;
    int idxVal;
    if (*(volatile char*)(tbl+idx*8) != 2) {
        unsigned long long r;
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0x000f7a3fUL,0x000f79c8UL,0xb8);
        r = assert_post_action(0x000f79c8UL,0xb8);
        basePtr = (int*)(unsigned int)(r & 0xffffffffUL);
        idxVal = (int)(unsigned int)(r >> 32);
    } else {
        basePtr = param_1;
        idxVal = param_2;
    }
    {
        int base = *(volatile int*)basePtr;
        *(volatile unsigned int*)(base + (idxVal+0x180)*4) = 0x6e524635UL;
    }
}
