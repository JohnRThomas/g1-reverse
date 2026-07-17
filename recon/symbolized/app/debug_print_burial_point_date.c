#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004a2a4 @ 0x0004a2a4
 * public-name: debug_print_burial_point_date
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   unix_timestamp_to_datetime               <= FUN_0004a1b8 @ 0x0004a1b8
 *   debug_print_burial_point_date            <= FUN_0004a2a4 @ 0x0004a2a4
 *   compute_day_of_week                      <= FUN_0007d280 @ 0x0007d280
 *   get_localized_weekday_name               <= FUN_0007d4b2 @ 0x0007d4b2
 * address symbols (name @ address):
 *   rodata_9bbbf                             @ 0x0009bbbf
 */
/* Reconstructed FUN_0004a2a4 @ 0x4a2a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(int,...);
extern int unix_timestamp_to_datetime(int,void*);
extern int compute_day_of_week(int,int,int);
extern int get_localized_weekday_name(int);
void debug_print_burial_point_date(int param_1){
  uint16_t calendar[6]={0};
  unix_timestamp_to_datetime(param_1, calendar);
  uint32_t uVar3 = calendar[0];
  uint32_t uVar1 = calendar[1];
  uint32_t uVar4 = calendar[2];
  DEBUG_PRINT(((unsigned long)&rodata_9bbbf) /*=0x9bbbf*/, param_1, uVar3, uVar1, uVar4,
              calendar[3], calendar[4], calendar[5]);
  int cVar2 = compute_day_of_week(uVar3, uVar1, uVar4);
  get_localized_weekday_name((int)(uint8_t)(cVar2 + 0x3b));
}
