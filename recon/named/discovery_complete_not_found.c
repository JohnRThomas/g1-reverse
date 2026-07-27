/* readable reconstruction; identity: FUN_0007f438 @ 0x0007f438
 * public-name: discovery_complete_not_found
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   svc_attr_memory_release                  <= FUN_0007f3c2 @ 0x0007f3c2
 *   atomic_and_0                             <= FUN_0007f3f0 @ 0x0007f3f0
 *   discovery_complete_not_found             <= FUN_0007f438 @ 0x0007f438
 */
/* Reconstructed FUN_0007f438 @ 0x7f438  (parity: 300/300 trials, PROVEN) */

extern void svc_attr_memory_release(unsigned long);
extern long atomic_and_0(volatile long*, long);

void discovery_complete_not_found(unsigned int *param_1)
{
    unsigned int base;
    unsigned int fptr;
    svc_attr_memory_release(param_1);
    atomic_and_0(param_1 + 0x4e, 0xfffffffeUL);
    base = param_1[0x57];
    fptr = *(volatile unsigned int*)(base + 4);
    if (fptr != 0) {
        ((void(*)(unsigned int,unsigned int))fptr)(param_1[0], param_1[1]);
    }
}
