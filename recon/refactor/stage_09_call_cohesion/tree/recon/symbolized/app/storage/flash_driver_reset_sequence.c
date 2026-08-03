#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000301bc @ 0x000301bc
 * public-name: flash_driver_reset_sequence
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_retry_delay                   <= FUN_0003016c @ 0x0003016c
 *   attr_store_set                           <= FUN_00030178 @ 0x00030178
 *   flash_driver_reset_sequence              <= FUN_000301bc @ 0x000301bc
 * address symbols (name @ address):
 *   rodata_ff20                              @ 0x0000ff20
 */
/* Reconstructed FUN_000301bc @ 0x301bc  (parity: 300/300 trials, PROVEN) */

extern int attr_store_retry_delay(int);
extern int attr_store_set(unsigned,unsigned,...);
int flash_driver_reset_sequence(unsigned p1,unsigned p2,unsigned p3,unsigned p4){
  int iVar1;
  iVar1 = attr_store_set(((unsigned long)&rodata_ff20) /*=0xff20*/, 0x3c00f091, p3, p4, p4);
  if(iVar1 >= 0 && (iVar1=attr_store_set(0x4700,0x110), iVar1>=0)){
    attr_store_retry_delay(1);
    iVar1 = attr_store_set(0x4444,0);
    if(iVar1 != 0) return iVar1;
    attr_store_retry_delay(0x14);
    iVar1 = attr_store_set(0xff18,0x3c);
    if(iVar1 >= 0){
      attr_store_retry_delay(0x19);
      iVar1 = attr_store_set(0x4700,0x102);
      return iVar1 >> 0x1f;
    }
  }
  return -1;
}
