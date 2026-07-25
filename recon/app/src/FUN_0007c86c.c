/* Reconstructed FUN_0007c86c @ 0x7c86c  (CFG-directed candidate) */
/* 6-byte accessor: returns descriptor->i2c_spec->page_size.
 *   ldr r3,[r0,#4]   ; descriptor->spec  (set to &g_st25dv_i2c_dev)
 *   ldr r0,[r3,#0xc] ; spec[12]          (set to 0x1000)
 *   bx  lr
 * It is the third entry of the 3-word ops vtable at rodata_88a38. */

unsigned int FUN_0007c86c(int param_1)
{
    return *(volatile unsigned int *)(*(volatile int *)(param_1 + 4) + 0xc);
}
