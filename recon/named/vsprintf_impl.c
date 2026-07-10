/* named: vsprintf_impl */
/* globals referenced:
//   0x20002d20  g_libc_heap_ctrl             
*/
/* Reconstructed vsprintf_impl @ 0x77c78  (parity: 300/300 trials, PROVEN) */

extern void FUN_00077c4c(unsigned int, unsigned int, unsigned int, unsigned int);

void vsprintf_impl(unsigned char *param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int v = *(volatile unsigned int*)0x20002d20UL;
    FUN_00077c4c(v, (unsigned int)param_1, param_2, param_3);
}

