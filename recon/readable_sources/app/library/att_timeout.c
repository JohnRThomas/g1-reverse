#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00059920 @ 0x00059920
 * public-name: att_timeout
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_att_disconnected                      <= FUN_00059834 @ 0x00059834
 *   att_timeout                              <= FUN_00059920 @ 0x00059920
 *   snprintk                                 <= FUN_0007ddbe @ 0x0007ddbe
 *   bt_conn_get_field_0x90                   <= FUN_00081526 @ 0x00081526
 *   att_log_emit_3arg                        <= FUN_00081ddc @ 0x00081ddc
 *   strcpy                                   <= FUN_00086fee @ 0x00086fee
 * address symbols (name @ address):
 *   rodata_88100                             @ 0x00088100
 *   rodata_9a1c8                             @ 0x0009a1c8
 *   rodata_9a1cf                             @ 0x0009a1cf
 *   rodata_9a1d6                             @ 0x0009a1d6
 *   rodata_9a1e0                             @ 0x0009a1e0
 *   rodata_9a1ea                             @ 0x0009a1ea
 *   rodata_f4697                             @ 0x000f4697
 *   rodata_f5071                             @ 0x000f5071
 */
/* Reconstructed FUN_00059920 @ 0x59920  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint8_t* bt_conn_get_field_0x90(uint32_t);
extern void snprintk(void*, int, uint32_t, ...);
extern void strcpy(void*, uint32_t);
extern void att_log_emit_3arg(uint32_t, int, void*);
extern void bt_att_disconnected(int);

void att_timeout(int param_1){
  uint8_t *puVar1;
  uint32_t uVar2;
  struct {
    uint32_t type;
    uint32_t format;
    uint8_t *text;
    uintptr_t style;
  } record;
  uint8_t auStack_44[12];
  uint8_t auStack_38[32];
  puVar1 = bt_conn_get_field_0x90(**(uint32_t**)(param_1 - 0x160));
  switch(puVar1[0]){
    case 0: uVar2 = ((unsigned long)&rodata_9a1c8) /*=0x9a1c8*/; break;
    case 1: uVar2 = ((unsigned long)&rodata_9a1cf) /*=0x9a1cf*/; break;
    case 2: uVar2 = ((unsigned long)&rodata_9a1d6) /*=0x9a1d6*/; break;
    case 3: uVar2 = ((unsigned long)&rodata_9a1e0) /*=0x9a1e0*/; break;
    default:
      snprintk(auStack_44, 10, ((unsigned long)&rodata_f5071) /*=0xf5071*/);
      goto LAB;
  }
  strcpy(auStack_44, uVar2);
LAB:
  snprintk(auStack_38, 0x1e, ((unsigned long)&rodata_9a1ea) /*=0x9a1ea*/, puVar1[6], puVar1[5], puVar1[4]);
  record.type = 0x1000003;
  record.format = ((unsigned long)&rodata_f4697) /*=0xf4697*/;
  record.text = auStack_38;
  record.style = ((uintptr_t)auStack_44 & 0xffff0000) | 0x200;
  att_log_emit_3arg(((unsigned long)&rodata_88100) /*=0x88100*/, 0x1c40, &record);
  bt_att_disconnected(param_1 - 0x158);
}
