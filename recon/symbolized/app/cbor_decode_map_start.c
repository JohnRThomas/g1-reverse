#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085fa2 @ 0x00085fa2
 * public-name: cbor_decode_map_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decode_undo_and_fail                <= FUN_00085dc4 @ 0x00085dc4
 *   cbor_decode_container_start              <= FUN_00085f06 @ 0x00085f06
 *   cbor_decode_map_start                    <= FUN_00085fa2 @ 0x00085fa2
 */
/* Reconstructed FUN_00085fa2 @ 0x85fa2  (parity: 300/300 trials, PROVEN) */

extern int cbor_decode_container_start(int, int);
extern void cbor_decode_undo_and_fail(int, int);

int cbor_decode_map_start(int param_1)
{
    int iVar1;
    iVar1 = cbor_decode_container_start(param_1, 5);
    if (iVar1 != 0) {
        if (*(char*)(param_1 + 0x10) != 0) {
            return iVar1;
        }
        if (*(unsigned int*)(param_1 + 8) < 0x7fffffffU) {
            *(unsigned int*)(param_1 + 8) = *(unsigned int*)(param_1 + 8) << 1;
            return iVar1;
        }
        cbor_decode_undo_and_fail(param_1, 5);
    }
    return 0;
}
