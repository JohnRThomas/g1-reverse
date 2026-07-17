#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100a118 @ 0x0100a118
 * public-name: FUN_0100a118
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_buffer_data_get                      <= FUN_01027790 @ 0x01027790
 * address symbols (name @ address):
 *   g_net_obj_table_root_ptr                 @ 0x21000bb4
 */
/* net-core FUN_0100a118 @ 0x100a118  (parity 300 trials PROVEN) */
extern void sdc_assertion_fail(int a, int b);
extern int sdc_buffer_data_get(int a);

unsigned int FUN_0100a118(unsigned short param_1)
{
    unsigned int local_c = 0;
    unsigned int **base = (unsigned int **)((unsigned long)&g_net_obj_table_root_ptr) /*=0x21000bb4*/;

    if (*base == 0) {
        sdc_assertion_fail(0x18, 0xec);
    }
    unsigned char *p = (unsigned char *)*base;
    if (param_1 < p[8] && *(int *)(param_1 * 4 + *(int *)(p + 4)) != 0) {
        local_c = sdc_buffer_data_get(*(int *)(param_1 * 4 + *(int *)(p + 4)));
    }
    return local_c;
}
