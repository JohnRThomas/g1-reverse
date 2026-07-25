/* net-core FUN_0102a4b0 @ 0x102a4b0  (parity 300 trials PROVEN) */

extern void FUN_01036824(int);
void FUN_0102a4b0(void)
{
    /* P4 iteration 30 - MEASURED DEFECT, fixed: ONE dereference too many.
     * Shipped: `ldr r2,[r3,#0]` then `ldr r2,[r2,#0x2c]`, and `ldr r0,[r3,#0];
     * adds r0,#0x24`, i.e. base is the single dereference of the service slot.
     * The previous `*(int *)*p` yielded state->role (= 1), so the guard read
     * address 0x2d and k_sem_give ran on address 0x25 (unmapped, silently a
     * no-op).  Measured: the ESB uplink worker thread that blocks on that
     * semaphore woke exactly once in a 9 s run despite 151 calls here. */
    volatile int * const * const p = (volatile int * const * const)0x210045f4;
    int base = (int)(unsigned long)*p;
    if (*(int*)(base + 0x2c) == 0) {
        FUN_01036824(base + 0x24);
    }
}

