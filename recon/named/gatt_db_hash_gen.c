/* readable reconstruction; identity: FUN_0005aba8 @ 0x0005aba8
 * public-name: gatt_db_hash_gen
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_db_hash_gen                         <= FUN_0005aba8 @ 0x0005aba8
 *   tc_cmac_setup                            <= FUN_0008016a @ 0x0008016a
 *   tc_cmac_final                            <= FUN_00080294 @ 0x00080294
 *   atomic_or_0                              <= FUN_000826e0 @ 0x000826e0
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   bt_gatt_foreach_attr_0                   <= FUN_00082c9c @ 0x00082c9c
 * address symbols (name @ address):
 *   ADDR_gen_hash_m_THUMB                    @ 0x0008260d
 *   rodata_88128                             @ 0x00088128
 *   rodata_f49d4                             @ 0x000f49d4
 *   rodata_f49ed                             @ 0x000f49ed
 *   g_bt_gatt_db_hash                        @ 0x20006380
 *   g_bt_gatt_flags                          @ 0x20006448
 */
/* Reconstructed FUN_0005aba8 @ 0x5aba8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int tc_cmac_setup(void*,void*,void*);
extern void tc_cmac_final(void); /*unused decl replaced*/
extern int FUN_00080294_i(uint32_t,void*);
extern void atomic_or_0(uint32_t);
extern void log_msg_create_3arg(uint32_t,int,void*);
extern void bt_gatt_foreach_attr_0(unsigned short, unsigned short, void*, void*);
void gatt_db_hash_gen(void){
  struct {
    uint32_t header[4];
    uint8_t reserved[16];
    struct { uint32_t level, message; } log;
    uint8_t work[96];
    uint8_t scratch[176];
  } frame;
  frame.header[0]=0; frame.header[1]=0; frame.header[2]=0; frame.header[3]=0;
  int iVar2=tc_cmac_setup(frame.work,frame.header,frame.scratch);
  if(iVar2!=0){
    bt_gatt_foreach_attr_0(1,0xffff,0x8260d,frame.work);
    iVar2=FUN_00080294_i(0x20006380,frame.work);
    if(iVar2!=0){
      volatile uint8_t* puVar3=(volatile uint8_t*)(0x20006380UL+0x10);
      volatile uint8_t* puVar4=(volatile uint8_t*)0x20006380UL;
      int i=0;
      do{
        uint8_t uVar1=*puVar4;
        puVar3=puVar3-1;
        i=i+1;
        *puVar4=*puVar3;
        *puVar3=uVar1;
        puVar4=puVar4+1;
      }while(i!=8);
      atomic_or_0(0x20006448);
      return;
    }
  }
  frame.log.level=2;
  frame.log.message=(iVar2==0) ? 0x000f49d4 : 0x000f49ed;
  log_msg_create_3arg(0x88128,0x1040,&frame.log);
}
