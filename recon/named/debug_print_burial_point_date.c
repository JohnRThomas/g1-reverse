/* named: debug_print_burial_point_date */
/* Reconstructed debug_print_burial_point_date @ 0x4a2a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(int,...);
extern int unix_timestamp_to_datetime(int,void*);
extern int compute_day_of_week(int,int,int);
extern int get_localized_weekday_name(int);
void debug_print_burial_point_date(int param_1){
  uint32_t local_24=0, local_20=0, local_1c=0;
  unix_timestamp_to_datetime(param_1, &local_24);
  uint32_t uVar3 = local_24 & 0xffff;
  uint32_t uVar1 = local_24 >> 0x10;
  uint32_t uVar4 = local_20 & 0xffff;
  DEBUG_PRINT(0x0009bbbf, param_1, uVar3, uVar1, uVar4, local_20>>0x10, local_1c & 0xffff, local_1c>>0x10);
  int cVar2 = compute_day_of_week(uVar3, uVar1, uVar4);
  get_localized_weekday_name((int)(uint8_t)(cVar2 + 0x3b));
}

