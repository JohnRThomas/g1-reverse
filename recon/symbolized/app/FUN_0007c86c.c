#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c86c @ 0x0007c86c
 * public-name: FUN_0007c86c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   (none)
 * address symbols (name @ address):
 *   (none)
 *
 * Ghidra function-catalog gap (iteration 10): the catalog stops
 * FUN_0007c85e (ipc_transport_ops_dispatch) at 0x0007c86c and resumes at the
 * thunk 0x0007c872, leaving these 6 bytes unowned.  Reconstructed from the
 * image:
 *   7c86c  ldr r3, [r0, #4]
 *   7c86e  ldr r0, [r3, #0xc]
 *   7c870  bx  lr
 * i.e. `return descriptor->i2c_spec->page_size`, where descriptor is the
 * ST25DV descriptor at g_st25dv_i2c_cfg (whose +4 is set to
 * &g_st25dv_i2c_dev and whose +0xc is set to 0x1000 by
 * serialization_ipc_ept_register).  It is the THIRD entry of the 3-word ops
 * vtable at rodata_88a38, reached from st25dv_read_chip_ids as
 *   (*(void (**)(void))(*(int *)(descriptor + 8) + 8))().
 * Proof: recon_kit.prove pass=True checked=300 cfg_status=PASS;
 * tools/cfg_verify.py app FUN_0007c86c -> PASS cases=0 (straight-line body,
 * no branch or switch selector exists to drive).
 */
/* Reconstructed FUN_0007c86c @ 0x7c86c */

unsigned int FUN_0007c86c(int param_1)
{
    return *(volatile unsigned int *)(*(volatile int *)(param_1 + 4) + 0xc);
}
