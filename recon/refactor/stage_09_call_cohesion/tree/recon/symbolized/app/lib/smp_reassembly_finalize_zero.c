#include "g1_app_symbols.h"
#include "g1_lib.h"
/* readable reconstruction; identity: FUN_00052854 @ 0x00052854
 * public-name: smp_reassembly_finalize_zero
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_reassembly_finalize_zero             <= FUN_00052854 @ 0x00052854
 *   smp_reassembly_expected                  <= FUN_00080b32 @ 0x00080b32
 *   smp_reassembly_get_ud                    <= FUN_00080bfe @ 0x00080bfe
 * address symbols (name @ address):
 *   g_misc_kobj_abac                         @ 0x2000abac
 */
/* Reconstructed FUN_00052854 @ 0x52854  (parity: 300/300 trials, PROVEN) */

extern int smp_reassembly_expected(int);
extern int* smp_reassembly_get_ud(int);

int smp_reassembly_finalize_zero(int param_1, int param_2)
{
    int iVar1 = smp_reassembly_expected(((unsigned long)&g_misc_kobj_abac) /*=0x2000abac*/);
    if (iVar1 < 0) return iVar1;
    if (param_2 != 0) return iVar1;
    int *puVar2 = smp_reassembly_get_ud(((unsigned long)&g_misc_kobj_abac) /*=0x2000abac*/);
    *puVar2 = param_2;
    *(unsigned char*)((char*)puVar2+4) = (unsigned char)param_2;
    return smp_packet_free(((unsigned long)&g_misc_kobj_abac) /*=0x2000abac*/);
}
