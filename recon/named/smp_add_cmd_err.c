/* readable reconstruction; identity: FUN_0005160c @ 0x0005160c
 * public-name: smp_add_cmd_err
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_add_cmd_err                          <= FUN_0005160c @ 0x0005160c
 *   cbor_encode_uint32                       <= FUN_00086320 @ 0x00086320
 *   cbor_encode_bstr                         <= FUN_0008633e @ 0x0008633e
 *   cbor_encode_map_indef_start              <= FUN_0008634c @ 0x0008634c
 * address symbols (name @ address):
 *   rodata_f0f61                             @ 0x000f0f61
 *   rodata_f2558                             @ 0x000f2558
 *   rodata_f255b                             @ 0x000f255b
 */
/* Reconstructed FUN_0005160c @ 0x5160c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int cbor_encode_uint32(int,...);
extern int cbor_encode_bstr(int,...);
extern int cbor_encode_map_indef_start(int,...);
extern int thunk_FUN_00086354(int,...);
unsigned smp_add_cmd_err(int param_1, unsigned param_2, int param_3){
  volatile unsigned local[2];
  local[0]=0xf0f61;
  if(param_3==0) return 1;
  *(volatile short*)(param_1+0x30)=(short)param_2;
  *(volatile short*)(param_1+0x32)=(short)param_3;
  local[1]=3;
  int iVar1 = cbor_encode_bstr(param_1,(int)local);
  if(iVar1!=0 && (iVar1=cbor_encode_map_indef_start(param_1,2),iVar1!=0)){
    local[0]=0xf255b; local[1]=5;
    iVar1=cbor_encode_bstr(param_1,(int)local);
    if(iVar1!=0 && (iVar1=cbor_encode_uint32(param_1,param_2),iVar1!=0)){
      local[0]=0xf2558; local[1]=2;
      iVar1=cbor_encode_bstr(param_1,(int)local);
      if(iVar1!=0 && (iVar1=cbor_encode_uint32(param_1,param_3),iVar1!=0)){
        unsigned uVar2 = thunk_FUN_00086354(param_1,2);
        return uVar2 & 1;
      }
    }
  }
  return 0;
}
