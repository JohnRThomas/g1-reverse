/* readable reconstruction; identity: FUN_00018334 @ 0x00018334
 * public-name: format_bt_addr_str
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   format_bt_addr_str                       <= FUN_00018334 @ 0x00018334
 *   snprintk                                 <= FUN_0007ddbe @ 0x0007ddbe
 *   strcpy                                   <= FUN_00086fee @ 0x00086fee
 * address symbols (name @ address):
 *   rodata_9a1c8                             @ 0x0009a1c8
 *   rodata_9a1cf                             @ 0x0009a1cf
 *   rodata_9a1d6                             @ 0x0009a1d6
 *   rodata_9a1e0                             @ 0x0009a1e0
 *   rodata_9a1ea                             @ 0x0009a1ea
 *   rodata_f5071                             @ 0x000f5071
 */
/* Reconstructed FUN_00018334 @ 0x18334  (parity: 400/400 trials, PROVEN) */
/* Reconstructed FUN_00018334 @ 0x18334  (parity: 300/300 trials, PROVEN) */

extern void snprintk(void *dst, unsigned int n, unsigned int fmt, ...);
extern void strcpy(void *dst, unsigned int src);

void format_bt_addr_str(unsigned char *param_1, void *param_2)
{
    unsigned int uVar1;
    unsigned char auStack_1c[12];
    switch (param_1[0]) {
    case 0: uVar1 = 0x0009a1c8u; break;
    case 1: uVar1 = 0x0009a1cfu; break;
    case 2: uVar1 = 0x0009a1d6u; break;
    case 3: uVar1 = 0x0009a1e0u; break;
    default:
        snprintk(auStack_1c, 10, 0x000f5071u);
        goto LAB;
    }
    strcpy(auStack_1c, uVar1);
LAB:
    snprintk(param_2, 0x1e, 0x0009a1eau,
        param_1[6], param_1[5], param_1[4], param_1[3],
        param_1[2], param_1[1], auStack_1c);
}
