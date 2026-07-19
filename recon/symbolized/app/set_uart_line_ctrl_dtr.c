#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c882 @ 0x0007c882
 * public-name: set_uart_line_ctrl_dtr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_send_cmd16_payload                   <= FUN_00025670 @ 0x00025670
 *   set_uart_line_ctrl_dtr                   <= FUN_0007c882 @ 0x0007c882
 */
/* Reconstructed FUN_0007c882 @ 0x7c882  (parity: 300/300 trials, PROVEN) */

extern void dev_send_cmd16_payload(void*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void set_uart_line_ctrl_dtr(void *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    dev_send_cmd16_payload(param_1, (*(volatile unsigned short*)((char*)param_1 + 8)) | 4, param_2, param_3, param_4, param_2);
}
