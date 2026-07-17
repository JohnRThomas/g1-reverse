/* readable reconstruction; identity: FUN_0100a118 @ 0x0100a118
 * public-name: FUN_0100a118
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_net_obj_table_root_ptr                 @ 0x21000bb4
 */
/* net-core FUN_0100a118 @ 0x100a118  (parity 300 trials PROVEN) */
extern void sdc_assertion_fail(int a, int b);
extern int FUN_01027790(int a);

unsigned int FUN_0100a118(unsigned short param_1)
{
    unsigned int local_c = 0;
    unsigned int **base = (unsigned int **)0x21000bb4;

    if (*base == 0) {
        sdc_assertion_fail(0x18, 0xec);
    }
    unsigned char *p = (unsigned char *)*base;
    if (param_1 < p[8] && *(int *)(param_1 * 4 + *(int *)(p + 4)) != 0) {
        local_c = FUN_01027790(*(int *)(param_1 * 4 + *(int *)(p + 4)));
    }
    return local_c;
}
