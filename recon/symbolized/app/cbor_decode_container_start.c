#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085f06 @ 0x00085f06
 * public-name: cbor_decode_container_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   zcbor_entry_backup_and_advance           <= FUN_00085c38 @ 0x00085c38
 *   zcbor_backup_store_count                 <= FUN_00085d70 @ 0x00085d70
 *   cbor_decode_check_major_type             <= FUN_00085da2 @ 0x00085da2
 *   cbor_decode_extract_value                <= FUN_00085e1a @ 0x00085e1a
 *   cbor_decode_container_start              <= FUN_00085f06 @ 0x00085f06
 */
/* Reconstructed FUN_00085f06 @ 0x85f06  (parity: 300/300 trials, PROVEN) */

extern int zcbor_entry_backup_and_advance(unsigned*,unsigned);
extern int zcbor_backup_store_count(unsigned*,int);
extern int cbor_decode_check_major_type(void);
extern int cbor_decode_extract_value(unsigned*,void*,int,unsigned,unsigned*);
int cbor_decode_container_start(unsigned* param_1, unsigned param_2, unsigned param_3){
  int r5; int iVar2; unsigned char bVar3; unsigned* puVar4;
  unsigned local_14, uStack_10;
  puVar4=param_1; local_14=param_2; uStack_10=param_3;
  r5=cbor_decode_check_major_type();
  if(r5==0) return 0;
  bVar3 = (*(unsigned char*)(*param_1)) & 0x1f;
  if(bVar3==0x1f){
    local_14=0xffffffef;
    if(param_1[2]==0){ zcbor_backup_store_count(param_1,3); return 0; }
    *param_1 = *param_1 + 1;
    param_1[2] = param_1[2] - 1;
  } else {
    int t = cbor_decode_extract_value(param_1,&local_14,4,bVar3,puVar4);
    if(t==0) return 0;
    r5=0;
  }
  iVar2 = zcbor_entry_backup_and_advance(param_1, local_14);
  if(iVar2!=0){
    *(char*)((int)param_1+0x10) = (char)r5;
    return iVar2;
  }
  *param_1 = param_1[1];
  param_1[2] = param_1[2] + 1;
  return 0;
}
