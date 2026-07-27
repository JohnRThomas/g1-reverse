#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c8e8 @ 0x0007c8e8
 * public-name: ipc_ept_op_b_guarded
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_ept_op_b_locked_retry                <= FUN_000257ec @ 0x000257ec
 *   ipc_ept_op_b_guarded                     <= FUN_0007c8e8 @ 0x0007c8e8
 */
/* Reconstructed FUN_0007c8e8 @ 0x7c8e8  (parity: 300/300 trials, PROVEN) */

/* BRING-UP WIRING FIX (P4 iteration 32) -- dropped register argument.  The
 * shipped body at 0x7c8e8 is `mov r2,r1 ; cbz r1 ; movs r3,#1 ; mov r1,r3 ;
 * b.w 0x257ec`, i.e. a FOUR-argument tail call whose r3 = 1 is the read
 * LENGTH that FUN_000257ec forwards to FUN_00025740 as i2c_msg[1].len.  The
 * reconstruction declared three parameters and dropped r3; the resulting
 * garbage length tripped NRFX_ASSERT(TWIM_LENGTH_VALIDATE) at
 * nrfx_twim.c:593 on the ST25DV system-port register-1 read.  The parity
 * harness cannot see this: the callee is an order-keyed oracle. */
extern int ipc_ept_op_b_locked_retry(int, unsigned int, unsigned int, int);

unsigned int ipc_ept_op_b_guarded(unsigned int param_1, int param_2)
{
    if (param_2 != 0) {
        return ipc_ept_op_b_locked_retry(param_1, 1, param_2, 1);
    }
    return 0xffffffea;
}
