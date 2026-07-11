/* net-core FUN_0100a760 @ 0x100a760  (parity 300 trials PROVEN) */

void FUN_0100a760(void)
{
    /* NVIC enable/disable writes require completion and instruction-stream
     * ordering.  Keep that contract in portable C through sequential fences. */
    volatile unsigned int *base = (volatile unsigned int *)0xe000e100;
    base[0x80/4] = 0x2000;
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
    base[0x180/4] = 0x2000;
    base[0x80/4] = 0x4000;
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
    base[0x180/4] = 0x4000;
}
