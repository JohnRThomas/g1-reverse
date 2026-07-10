/* named: libc_fatal_error_and_abort */
/* globals referenced:
//   0x20002d20  g_libc_heap_ctrl             
*/
/* Reconstructed libc_fatal_error_and_abort @ 0x76a94  (parity: 300/300 trials, PROVEN) */

extern void fprintf_stream(int,int);
extern int abort(void);
void libc_fatal_error_and_abort(void)
{
    int uVar1 = *(volatile int*)(*(volatile int*)0x20002d20UL + 0xc);
    for (;;) {
        fprintf_stream(uVar1, 0);
        uVar1 = abort();
    }
}

