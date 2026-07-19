#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083dba @ 0x00083dba
 * public-name: dev_ctrl_read1
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_ctrl_write2                          <= FUN_00083d80 @ 0x00083d80
 *   dev_ctrl_read1                           <= FUN_00083dba @ 0x00083dba
 */
/* Reconstructed FUN_00083dba @ 0x83dba  (parity: 300/300 trials, PROVEN) */

extern void dev_ctrl_write2(void);
void dev_ctrl_read1(void)
{
  dev_ctrl_write2();
  return;
}
