/* readable reconstruction; identity: FUN_000549ec @ 0x000549ec
 * public-name: FUN_000549ec
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atomic_or                                <= FUN_00080e6a @ 0x00080e6a
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f322e                             @ 0x000f322e
 *   g_ble_dev_state                          @ 0x20002000
 */
/* Reconstructed FUN_000549ec @ 0x549ec  (parity: 300/300 trials, PROVEN) */

extern void FUN_00080ea2(unsigned int a, unsigned int b, void *c);
extern void atomic_or(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_000548b8(void);

unsigned int FUN_000549ec(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile unsigned char *base = (volatile unsigned char*)0x20002000UL;
    unsigned char flag = base[7];
    if (flag == 0) {
        struct { unsigned int f0; unsigned int f1; } s;
        s.f0 = 2;
        s.f1 = 0x000f322eUL;
        FUN_00080ea2(0x00088138UL, 0x10c0, &s);
    } else {
        atomic_or(0x20002000UL + 0xd4, 8, param_3, flag);
        FUN_000548b8();
    }
    return 0;
}
