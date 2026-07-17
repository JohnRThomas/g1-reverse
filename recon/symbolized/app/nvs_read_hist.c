#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004cab4 @ 0x0004cab4
 * public-name: nvs_read_hist
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nvs_read_hist                            <= FUN_0004cab4 @ 0x0004cab4
 *   nvs_log_err                              <= FUN_0007e658 @ 0x0007e658
 *   nvs_al_size                              <= FUN_0007e65e @ 0x0007e65e
 * address symbols (name @ address):
 *   rodata_881b8                             @ 0x000881b8
 *   rodata_f0ae4                             @ 0x000f0ae4
 */
/* Reconstructed FUN_0004cab4 @ 0x4cab4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef unsigned int uint;
extern uint FUN_0007e53e(int,uint,unsigned,uint);
extern int nvs_log_err(int,int,void*);
extern int nvs_al_size(unsigned,int);
extern int FUN_0007e672(int,void*);
extern uint FUN_0007e6e2(int,void*,void*);

struct iterator_frame {
  uint32_t reserved_word;
  uint32_t cursor;
  unsigned short item[3];
  unsigned char reserved[2];
  uint32_t log_record[2];
};

uint nvs_read_hist(int param_1, uint param_2, unsigned param_3, uint param_4, unsigned short param_5)
{
  uint uVar1; int iVar2; uint uVar3; unsigned short uVar4;
  struct iterator_frame frame;
  if (*(volatile char*)(param_1 + 0x10) == 0) {
    frame.log_record[1] = ((unsigned long)&rodata_f0ae4) /*=0xf0ae4*/; frame.log_record[0] = 2;
    nvs_log_err(((unsigned long)&rodata_881b8) /*=0x881b8*/, 0x1040, frame.log_record);
    uVar1 = 0xfffffff3;
  } else {
    iVar2 = nvs_al_size(*(volatile unsigned*)(param_1 + 0x2c), 8);
    if ((uint)*(volatile unsigned short*)(param_1 + 0xc) + iVar2 * -2 < param_4) {
      uVar1 = 0xffffffea;
    } else {
      uVar4 = 0;
      frame.cursor = *(volatile uint*)(param_1 + 4);
      uVar1 = frame.cursor;
      do {
        uVar3 = frame.cursor;
        if (param_5 < uVar4) {
          uVar3 = uVar1;
          if (*(volatile uint*)(param_1 + 4) != frame.cursor) goto LAB;
          break;
        }
        uVar1 = FUN_0007e6e2(param_1, &frame.cursor, &frame.item[0]);
        if (uVar1 != 0) return uVar1;
        if ((frame.item[0] == param_2) &&
            (iVar2 = FUN_0007e672(param_1, &frame.item[0]), iVar2 != 0)) {
          uVar4 = uVar4 + 1;
        }
        uVar1 = uVar3;
      } while (*(volatile uint*)(param_1 + 4) != frame.cursor);
      if (frame.item[0] == param_2) {
LAB:
        uVar1 = (uint)frame.item[2];
        if ((uVar1 != 0) && (param_5 <= uVar4)) {
          if (param_4 <= uVar1) uVar1 = param_4;
          uVar1 = FUN_0007e53e(param_1,
                               (uVar3 & 0xffff0000) + (uint)frame.item[1],
                               param_3, uVar1);
          if (uVar1 != 0) return uVar1;
          return (uint)frame.item[2];
        }
      }
      uVar1 = 0xfffffffe;
    }
  }
  return uVar1;
}
