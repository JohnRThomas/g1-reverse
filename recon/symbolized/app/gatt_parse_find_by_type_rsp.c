#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005bbf4 @ 0x0005bbf4
 * public-name: gatt_parse_find_by_type_rsp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_parse_find_by_type_rsp              <= FUN_0005bbf4 @ 0x0005bbf4
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   gatt_discover_next                       <= FUN_00082d2e @ 0x00082d2e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f4ca8                             @ 0x000f4ca8
 */
/* Reconstructed FUN_0005bbf4 @ 0x5bbf4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_msg_create_3arg(unsigned,unsigned,void*);
extern void gatt_discover_next(unsigned long, unsigned long, void*);
extern void memset_bytes(void*,int,int);
typedef int (*fp_t)(unsigned,void*,void*);

void gatt_parse_find_by_type_rsp(unsigned param_1, int param_2, unsigned char *param_3, int param_4, char *param_5){
  fp_t pcVar6;
  if(param_2 != 0){
    pcVar6 = *(fp_t*)(param_5+4);
    pcVar6(param_1, 0, param_5);
    return;
  }
  unsigned uVar3 = *param_3;
  char cVar2 = 0;
  if(uVar3 != 6){
    if(uVar3 == 0x14){ cVar2 = 2; }
    else {
      unsigned st[8];
      st[0]=3; st[5]=((unsigned long)&rodata_f4ca8) /*=0xf4ca8*/; st[6]=uVar3;
      log_msg_create_3arg(((unsigned long)&rodata_88128) /*=0x88128*/, 0x1840, st);
      goto LAB_bc40;
    }
  }
  {
    char local_50 = cVar2;
    unsigned short uVar9 = 0, uVar1;
    unsigned short *puVar10 = (unsigned short*)(param_3 + 1);
    unsigned char blk[0x14];
    unsigned uVar3b = (unsigned)(param_4 - 1);
    while((uVar3b = uVar3b & 0xffff), *param_3 <= uVar3b){
      memset_bytes(blk, 0, 0x14);
      uVar1 = *puVar10;
      if(uVar1==0 || (uVar9=puVar10[1], uVar9==0) || uVar9 < uVar1) goto LAB_bc40;
      volatile unsigned short sink = 0;
      if(local_50 == 0){ sink = puVar10[2]; }
      else if(local_50 == 2){ for(int i=0;i<4;i++) sink = puVar10[2+i]; }
      (void)sink;
      int iVar4 = (*(fp_t*)(param_5+4))(param_1, blk, param_5);
      if(iVar4 == 0) return;
      puVar10 = (unsigned short*)((int)puVar10 + *param_3);
      uVar3b = uVar3b - *param_3;
    }
    if(uVar3b == 0 && uVar9 != 0){
      gatt_discover_next(param_1, uVar9, param_5);
      return;
    }
  }
LAB_bc40:
  pcVar6 = *(fp_t*)(param_5+4);
  pcVar6(param_1, 0, param_5);
}
