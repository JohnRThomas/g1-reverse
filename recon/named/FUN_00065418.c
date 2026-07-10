/* named: FUN_00065418 */
/* Reconstructed FUN_00065418 @ 0x65418  (parity: 300/300 trials, PROVEN) */

extern void nrfx_flag32_free(unsigned int a, unsigned int b);

void FUN_00065418(unsigned int param_1)
{
    *(volatile unsigned int*)0x50017508UL = 1u << (param_1 & 0xff);
    nrfx_flag32_free(0x20002bbcUL, param_1);
}

