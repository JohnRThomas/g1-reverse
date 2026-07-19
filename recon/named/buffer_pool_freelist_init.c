/* readable reconstruction; identity: FUN_00085cf2 @ 0x00085cf2
 * public-name: buffer_pool_freelist_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   buffer_pool_freelist_init                <= FUN_00085cf2 @ 0x00085cf2
 */
/* Reconstructed FUN_00085cf2 @ 0x85cf2  (parity: 300/300 trials, PROVEN) */

void buffer_pool_freelist_init(unsigned int param_1, unsigned int param_2, int param_3, int param_4, int param_5)
{
    *(volatile int*)(param_1+0) = param_3;
    *(volatile int*)(param_1+8) = param_5;
    *(volatile int*)(param_1+0xc) = param_3 + param_4;
    *(volatile unsigned short*)(param_1+0x10) = 0;
    if (param_2 < 2) {
        *(volatile int*)(param_1+0x14) = 0;
    } else {
        unsigned int off = param_2*24 - 24;
        unsigned int p5 = param_1 + off;
        *(volatile unsigned int*)(param_1+0x14) = p5;
        *(volatile int*)p5 = 0;
        *(volatile unsigned int*)(p5+8) = param_2 - 2;
        *(volatile int*)(p5+4) = 0;
        *(volatile int*)(p5+0xc) = 0;
        *(volatile unsigned char*)(p5+0x10) = 0;
        if (param_2 != 2) {
            *(volatile unsigned int*)p5 = param_1 + 0x18;
        }
    }
}
