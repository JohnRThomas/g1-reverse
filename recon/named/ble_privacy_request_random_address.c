/* readable reconstruction; identity: FUN_000552ac @ 0x000552ac
 * public-name: ble_privacy_request_random_address
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_privacy_request_random_address       <= FUN_000552ac @ 0x000552ac
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 * address symbols (name @ address):
 *   rodata_88150                             @ 0x00088150
 *   rodata_f2b41                             @ 0x000f2b41
 *   rodata_f2b47                             @ 0x000f2b47
 *   rodata_f3733                             @ 0x000f3733
 *   rodata_f374c                             @ 0x000f374c
 */
/* Reconstructed FUN_000552ac @ 0x552ac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00053d70(int,int,void*);
extern void FUN_0008104a(uint32_t,int,void*);
extern int FUN_00086be4(int,uint32_t,int);
extern void FUN_00080fba(int,int);
extern void net_buf_unref(int);
uint32_t ble_privacy_request_random_address(uint8_t* param_1){
  struct {
    uint32_t pad;
    int local_34[5];
    struct { uint32_t kind, site; } log;
    uint32_t tail[2];
  } frame;
  if(param_1==0){
    frame.log.kind=2; frame.log.site=0xf3733;
    FUN_0008104a(0x88150,0x1080,&frame.log);
    return 0;
  }
  int iVar1=FUN_00053d70(0x1009,0,frame.local_34);
  if(iVar1!=0){
    frame.log.kind=2; frame.log.site=0xf374c;
    FUN_0008104a(0x88150,0x1080,&frame.log);
    return 0;
  }
  int iVar2=*(volatile int*)(frame.local_34[0]+0xc)+1;
  int r=FUN_00086be4(iVar2,0xf2b47,6);
  if(r!=0){
    r=FUN_00086be4(iVar2,0xf2b41,6);
    if(r!=0){
      FUN_00080fba((int)param_1+1,iVar2);
      *param_1=0;
      net_buf_unref(frame.local_34[0]);
      return 1;
    }
  }
  net_buf_unref(frame.local_34[0]);
  return 0;
}
