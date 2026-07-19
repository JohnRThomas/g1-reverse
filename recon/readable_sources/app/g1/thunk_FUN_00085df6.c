#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085fce @ 0x00085fce
 * public-name: thunk_FUN_00085df6
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decode_leave_container              <= FUN_00085df6 @ 0x00085df6
 */
/* Tail thunk @ 0x85fce. */
extern int cbor_decode_leave_container(int,int,int,int); int thunk_FUN_00085df6(int a,int b,int c,int d){return cbor_decode_leave_container(a,b,c,d);}
