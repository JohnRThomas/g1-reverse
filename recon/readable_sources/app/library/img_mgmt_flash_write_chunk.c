#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007f110 @ 0x0007f110
 * public-name: img_mgmt_flash_write_chunk
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   stream_flash_erase_page                  <= FUN_0004e124 @ 0x0004e124
 *   nullsub_3                                <= FUN_0007ef7e @ 0x0007ef7e
 *   stream_flash_buffered_write              <= FUN_0007f088 @ 0x0007f088
 *   img_mgmt_flash_write_chunk               <= FUN_0007f110 @ 0x0007f110
 *   subtract_32                              <= FUN_000836d8 @ 0x000836d8
 */
/* Reconstructed FUN_0007f110 @ 0x7f110  (parity: 300/300 trials, PROVEN) */

extern int stream_flash_erase_page(int,int,int,int,int);
extern void nullsub_3(int);
extern int stream_flash_buffered_write(int);
extern int subtract_32(int);

int img_mgmt_flash_write_chunk(int param_1,int param_2,int param_3,int param_4)
{
  int iVar1;
  int iVar2;
  iVar2 = param_4;
  iVar1 = stream_flash_buffered_write(param_1 + 0x204);
  if (param_4 != 0) {
    iVar1 = subtract_32(*(volatile int*)(*(volatile int*)(param_1+0x200)+8));
    iVar1 = stream_flash_erase_page(param_1+0x204, *(volatile int*)(*(volatile int*)(param_1+0x200)+4)+iVar1, param_3, *(volatile int*)(param_1+0x200), iVar2);
    if (iVar1==0) {
      nullsub_3(*(volatile int*)(param_1+0x200));
      *(volatile int*)(param_1+0x200)=0;
    }
  }
  return iVar1;
}
