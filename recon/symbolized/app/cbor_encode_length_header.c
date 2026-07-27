#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086208 @ 0x00086208
 * public-name: cbor_encode_length_header
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_min_encoded_size                    <= FUN_0007158c @ 0x0007158c
 *   value_encode_len                         <= FUN_000715b8 @ 0x000715b8
 *   cbor_encode_length_header                <= FUN_00086208 @ 0x00086208
 */
/* Reconstructed FUN_00086208 @ 0x86208  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern unsigned int cbor_min_encoded_size(char *, unsigned int);
extern int value_encode_len(int*,u32,u8*,int);
int cbor_encode_length_header(int* param_1, u32 param_2, u8* param_3, u32 param_4){
    int iVar2 = cbor_min_encoded_size(param_3, param_4);
    return value_encode_len(param_1, param_2, param_3, iVar2);
}
