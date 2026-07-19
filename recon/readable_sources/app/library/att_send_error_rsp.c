#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000821f4 @ 0x000821f4
 * public-name: att_send_error_rsp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   send_err_rsp_alloc_failure_log           <= FUN_00058568 @ 0x00058568
 *   bt_att_chan_create_pdu                   <= FUN_000585f0 @ 0x000585f0
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   bt_att_chan_send_rsp                     <= FUN_000821a4 @ 0x000821a4
 *   att_send_error_rsp                       <= FUN_000821f4 @ 0x000821f4
 */
/* Reconstructed FUN_000821f4 @ 0x821f4. */
#include <stdint.h>
extern int bt_att_chan_create_pdu(uintptr_t, unsigned, unsigned);
extern void send_err_rsp_alloc_failure_log(void);
extern unsigned char* net_buf_simple_add(int,int);
extern void bt_att_chan_send_rsp(uintptr_t,int);

void att_send_error_rsp(uintptr_t owner, int opcode, uint16_t handle,
                  unsigned status)
{
    if (opcode == 0)
        return;

    int item = bt_att_chan_create_pdu(owner, 1, 4);
    if (item == 0) {
        send_err_rsp_alloc_failure_log();
        return;
    }

    uint8_t *payload = net_buf_simple_add(item + 0xc, 4);
    *(volatile uint8_t *)(payload + 0) = (uint8_t)opcode;
    *(volatile uint16_t *)(payload + 1) = handle;
    *(volatile uint8_t *)(payload + 3) = (uint8_t)status;
    bt_att_chan_send_rsp(owner, item);
}
