#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00025290 @ 0x00025290
 * public-name: st25dv_read_chip_ids
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   adc_nfc_init                             <= FUN_00024b98 @ 0x00024b98
 *   st25dv_read_chip_ids                     <= FUN_00025290 @ 0x00025290
 *   serialization_ipc_ept_register           <= FUN_000259d4 @ 0x000259d4
 *   clear_pending_state_flags                <= FUN_0002ebc8 @ 0x0002ebc8
 * address symbols (name @ address):
 *   rodata_9f145                             @ 0x0009f145
 *   rodata_9f176                             @ 0x0009f176
 *   rodata_9f186                             @ 0x0009f186
 *   g_st25dv_dev                             @ 0x20007a44
 *   g_board_rev_flag                         @ 0x20018c69
 */
/* Reconstructed FUN_00025290 @ 0x25290  (parity: 300/300 trials, PROVEN) */
extern int serialization_ipc_ept_register(void);
extern void FUN_00074844(int,int);
extern void FUN_0007c932(int,void*);
extern void DEBUG_PRINT(int,...);
extern void FUN_0007c944(int,void*);
extern void FUN_0007c956(int,void*);
extern void adc_nfc_init(void);
extern void clear_pending_state_flags(void);
int st25dv_read_chip_ids(void){
  unsigned local_10=0, local_c=0;
  unsigned char local_12=0, local_11;
  int iVar2;
  volatile int *piVar1 = (volatile int*)((unsigned long)&g_st25dv_dev) /*=0x20007a44*/;
  iVar2 = serialization_ipc_ept_register();
  *piVar1 = iVar2;
  if (iVar2!=0 && *(volatile int*)(iVar2+4)!=0 && *(volatile int*)(iVar2+0x10)!=0 && *(volatile int*)(iVar2+8)!=0){
    unsigned uVar4; unsigned char uVar3; unsigned puVar5; unsigned char *puVar6;
    FUN_00074844(0x290,0);
    (*(void(**)(void))((*(volatile int*)((*piVar1)+8))+8))();
    FUN_0007c932(*piVar1,&local_10);
    uVar4 = (local_10>>8)&0xff;
    DEBUG_PRINT(((unsigned long)&rodata_9f145) /*=0x9f145*/, local_10&0xff, uVar4, (local_10>>0x10)&0xff, local_10>>0x18, local_c&0xff, (local_c>>8)&0xff, (local_c>>0x10)&0xff, local_c>>0x18);
    uVar3 = (unsigned char)uVar4;
    puVar5 = ((local_c>>8)&0xff) - 0x50;
    puVar6 = (unsigned char*)puVar5;
    if (puVar5 < 2){ uVar3=1; puVar6=(unsigned char*)((unsigned long)&g_board_rev_flag) /*=0x20018c69*/; }
    iVar2 = *piVar1;
    if (puVar5 < 2){ *(volatile unsigned char*)puVar6 = uVar3; }
    FUN_0007c944(iVar2,&local_12);
    DEBUG_PRINT(((unsigned long)&rodata_9f176) /*=0x9f176*/,(unsigned)local_12);
    FUN_0007c956(*piVar1,&local_11);
    DEBUG_PRINT(((unsigned long)&rodata_9f186) /*=0x9f186*/,(unsigned)local_11);
    adc_nfc_init();
    clear_pending_state_flags();
  }
  return 0;
}
