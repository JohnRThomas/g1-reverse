/* named: discovery_complete_not_found */
/* Reconstructed discovery_complete_not_found @ 0x7f438  (parity: 300/300 trials, PROVEN) */

extern void svc_attr_memory_release(void);
extern void atomic_and_0(void *a, unsigned int b);

void discovery_complete_not_found(unsigned int *param_1)
{
    unsigned int base;
    unsigned int fptr;
    svc_attr_memory_release();
    atomic_and_0(param_1 + 0x4e, 0xfffffffeUL);
    base = param_1[0x57];
    fptr = *(volatile unsigned int*)(base + 4);
    if (fptr != 0) {
        ((void(*)(unsigned int,unsigned int))fptr)(param_1[0], param_1[1]);
    }
}

