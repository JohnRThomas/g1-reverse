#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00051ac0 @ 0x00051ac0
 * public-name: img_mgmt_state_encode_slot
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   img_mgmt_state_encode_slot               <= FUN_00051ac0 @ 0x00051ac0
 *   img_mgmt_ver_str                         <= FUN_00051f88 @ 0x00051f88
 *   img_mgmt_read_info                       <= FUN_00052038 @ 0x00052038
 *   zcbor_tstr_encode_ptr                    <= FUN_0008099e @ 0x0008099e
 *   cbor_encode_uint32                       <= FUN_00086320 @ 0x00086320
 *   zcbor_bstr_encode                        <= FUN_00086338 @ 0x00086338
 *   cbor_encode_map_indef_start              <= FUN_0008634c @ 0x0008634c
 *   cbor_encode_simple                       <= FUN_00086378 @ 0x00086378
 * address symbols (name @ address):
 *   rodata_f272f                             @ 0x000f272f
 *   rodata_f2734                             @ 0x000f2734
 *   rodata_f273a                             @ 0x000f273a
 *   rodata_f2743                             @ 0x000f2743
 *   rodata_f274b                             @ 0x000f274b
 *   rodata_f2755                             @ 0x000f2755
 *   rodata_f349f                             @ 0x000f349f
 *   rodata_f4a01                             @ 0x000f4a01
 *   rodata_f5702                             @ 0x000f5702
 *   rodata_f6589                             @ 0x000f6589
 */
/* Reconstructed FUN_00051ac0 @ 0x51ac0  (parity: 200/200 trials, PROVEN) */

#include <stdint.h>
extern int strlen(int);
extern int img_mgmt_ver_str(void*,void*);
extern int img_mgmt_read_info(unsigned,void*,void*,void*);
extern int zcbor_tstr_encode_ptr(unsigned,void*,int);
extern int cbor_encode_uint32(unsigned,unsigned);
extern int zcbor_bstr_encode(unsigned,void*);
extern int cbor_encode_map_indef_start(unsigned,int);
extern int cbor_encode_simple(unsigned,unsigned);
extern int thunk_FUN_00086354(unsigned,int);
unsigned img_mgmt_state_encode_slot(unsigned param_1,unsigned param_2,unsigned param_3){
  unsigned char buf5c[8], buf54[24], l3c, buf38[36];
  unsigned local_68; unsigned char* local_64=buf38; int local_60=0x20; (void)local_60;
  int iVar1; unsigned uVar2; unsigned char* puVar3; int uVar4;
  iVar1 = img_mgmt_read_info(param_2,buf5c,local_64,&local_68);
  if (iVar1==0){
    iVar1 = cbor_encode_map_indef_start(param_1,0xf);
    uVar2 = 0;
    if (iVar1!=0 && (iVar1=zcbor_tstr_encode_ptr(param_1,(void*)((unsigned long)&rodata_f349f) /*=0xf349f*/,5))!=0 &&
        (iVar1=cbor_encode_uint32(param_1,param_2>>1))!=0 &&
        (iVar1=zcbor_tstr_encode_ptr(param_1,(void*)((unsigned long)&rodata_f272f) /*=0xf272f*/,4))!=0 &&
        (iVar1=cbor_encode_uint32(param_1,param_2&1))!=0 &&
        (iVar1=zcbor_tstr_encode_ptr(param_1,(void*)((unsigned long)&rodata_f6589) /*=0xf6589*/,7))!=0){
      iVar1 = img_mgmt_ver_str(buf5c,buf54);
      if (iVar1<0){ uVar4=5; puVar3=(void*)((unsigned long)&rodata_f2734) /*=0xf2734*/; }
      else { l3c=0; buf54[0]=l3c; uVar4=strlen(buf54); puVar3=buf54; }
      iVar1 = zcbor_tstr_encode_ptr(param_1,puVar3,uVar4);
      if (iVar1!=0 && (iVar1=zcbor_tstr_encode_ptr(param_1,(void*)((unsigned long)&rodata_f4a01) /*=0xf4a01*/,4))!=0 &&
          (iVar1=zcbor_bstr_encode(param_1,&local_64))!=0 &&
          (iVar1=zcbor_tstr_encode_ptr(param_1,(void*)((unsigned long)&rodata_f273a) /*=0xf273a*/,8))!=0 &&
          (iVar1=cbor_encode_simple(param_1,((local_68^0x10)>>4)&1))!=0 &&
          (iVar1=zcbor_tstr_encode_ptr(param_1,(void*)((unsigned long)&rodata_f2743) /*=0xf2743*/,7))!=0 &&
          (iVar1=cbor_encode_simple(param_1,(param_3>>1)&1))!=0 &&
          (iVar1=zcbor_tstr_encode_ptr(param_1,(void*)((unsigned long)&rodata_f274b) /*=0xf274b*/,9))!=0 &&
          (iVar1=cbor_encode_simple(param_1,(param_3>>2)&1))!=0 &&
          (iVar1=zcbor_tstr_encode_ptr(param_1,(void*)((unsigned long)&rodata_f5702) /*=0xf5702*/,6))!=0 &&
          (iVar1=cbor_encode_simple(param_1,param_3&1))!=0 &&
          (iVar1=zcbor_tstr_encode_ptr(param_1,(void*)((unsigned long)&rodata_f2755) /*=0xf2755*/,9))!=0 &&
          (iVar1=cbor_encode_simple(param_1,(param_3>>3)&1))!=0){
        uVar2 = thunk_FUN_00086354(param_1,0xf);
      }
    }
    uVar2 = uVar2 & 1;
  } else uVar2 = 1;
  return uVar2;
}
