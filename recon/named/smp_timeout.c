/* readable reconstruction; identity: FUN_0005e3e0 @ 0x0005e3e0
 * public-name: smp_timeout
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_pairing_complete                     <= FUN_0005daf0 @ 0x0005daf0
 *   smp_timeout                              <= FUN_0005e3e0 @ 0x0005e3e0
 *   atomic_set_bit                           <= FUN_00083090 @ 0x00083090
 * address symbols (name @ address):
 *   rodata_88180                             @ 0x00088180
 *   rodata_f51ec                             @ 0x000f51ec
 */
/* Reconstructed FUN_0005e3e0 @ 0x5e3e0  (parity: 300/300 trials, PROVEN) */

extern void FUN_00083074(unsigned int, int, void*);
extern void smp_pairing_complete(int, int);
extern void atomic_set_bit(int, int);

void smp_timeout(int param_1)
{
    unsigned int local_10_arr[2];
    local_10_arr[0] = 2;
    local_10_arr[1] = 0xf51ecUL;
    FUN_00083074(0x88180UL, 0x1040, local_10_arr);
    smp_pairing_complete(param_1 - 0x208, 8);
    atomic_set_bit(param_1 - 0x204, 4);
}
