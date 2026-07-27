/* readable reconstruction; identity: FUN_0007f40c @ 0x0007f40c
 * public-name: discovery_complete_error
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   svc_attr_memory_release                  <= FUN_0007f3c2 @ 0x0007f3c2
 *   atomic_and_0                             <= FUN_0007f3f0 @ 0x0007f3f0
 *   discovery_complete_error                 <= FUN_0007f40c @ 0x0007f40c
 */
/* Reconstructed FUN_0007f40c @ 0x7f40c  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(unsigned int, unsigned int, unsigned int);
extern void svc_attr_memory_release(unsigned long);
extern long atomic_and_0(volatile long*, long);

void discovery_complete_error(unsigned int *param_1, unsigned int param_2)
{
    svc_attr_memory_release(param_1);
    atomic_and_0(param_1 + 0x4e, 0xfffffffeU);
    fn_t f = *(fn_t*)(param_1[0x57] + 8);
    if (f != (fn_t)0) {
        f(param_1[0], param_2, param_1[1]);
        return;
    }
    return;
}
