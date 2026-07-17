#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008635c @ 0x0008635c
 * public-name: thunk_FUN_00086354
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_encode_break                        <= FUN_00086354 @ 0x00086354
 */
/* Tail thunk @ 0x8635c. */
extern int cbor_encode_break(int,int,int,int); int thunk_FUN_00086354(int a,int b,int c,int d){return cbor_encode_break(a,b,c,d);}
