#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081a60 @ 0x00081a60
 * public-name: FUN_00081a60
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   conn_ctx_cleanup_if_pending              <= FUN_00081720 @ 0x00081720
 */
/* Reconstructed FUN_00081a60 @ 0x81a60  (parity: 300/300 trials, PROVEN) */

extern void conn_ctx_cleanup_if_pending(void);
extern int FUN_00081a4e(unsigned int, unsigned short);

void FUN_00081a60(unsigned int param_1, void *param_2, int param_3)
{
    if (param_3 == 0) {
        int iVar1 = FUN_00081a4e(param_1, *(volatile unsigned short*)((char*)param_2 + 4));
        if (iVar1 != 0) {
            conn_ctx_cleanup_if_pending();
            return;
        }
    }
}
