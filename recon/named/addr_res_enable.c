/* readable reconstruction; identity: FUN_00081050 @ 0x00081050
 * public-name: addr_res_enable
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_send_sync                     <= FUN_00053d70 @ 0x00053d70
 *   addr_res_enable                          <= FUN_00081050 @ 0x00081050
 */
/* Reconstructed addr_res_enable @ 0x00081050 from NCS 2.5.1 id.c.
 * Raw backmap: FUN_00081050@0x00081050. */

#include <stdint.h>
#define addr_res_enable addr_res_enable
extern void *bt_hci_cmd_create(uint32_t opcode,uint32_t length);
extern void net_buf_push_u8(void *buffer,uint32_t value);
extern int bt_hci_cmd_send_sync(uint32_t opcode,void *buffer,uint32_t response); /* bt_hci_cmd_send_sync */
int addr_res_enable(uint32_t enable){void *buf=bt_hci_cmd_create(0x202du,1u);if(!buf)return -105;net_buf_push_u8((uint8_t*)buf+0x0cu,enable);return bt_hci_cmd_send_sync(0x202du,buf,0u);}
