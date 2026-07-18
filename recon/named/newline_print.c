/* readable reconstruction; identity: FUN_0004da90 @ 0x0004da90
 * public-name: newline_print
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   print_formatted                          <= FUN_0004da6c @ 0x0004da6c
 *   newline_print                            <= FUN_0004da90 @ 0x0004da90
 * address symbols (name @ address):
 *   rodata_f5400                             @ 0x000f5400
 */
/* Reconstructed FUN_0004da90 @ 0x4da90  (parity: 300/300 trials, PROVEN) */

extern void print_formatted(unsigned int, unsigned int, unsigned int, unsigned int);

void newline_print(unsigned int param_1, int param_2)
{
    unsigned int uVar1;
    if ((int)((unsigned int)param_2 << 0x1b) < 0) {
        return;
    }
    uVar1 = 0x000a8c94;
    if ((int)((unsigned int)param_2 << 0x1a) < 0) {
        uVar1 = 0x000f5400;
    }
    print_formatted(param_1, uVar1, (unsigned int)param_2 << 0x1b,
                 (unsigned int)param_2 << 0x1a);
}
