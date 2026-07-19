### FUN_00081ddc  @ 0x00081ddc  (size=6)

callers (11): find_type_cb, att_get, bt_att_chan_create_pdu, bt_att_accept, FUN_00058a54, bt_att_recv, bt_att_create_pdu, bt_att_create_rsp_pdu, att_handle_rsp, att_timeout, att_send_error_rsp
callees (1): FUN_0004d944

```c
/* readable reconstruction; identity: FUN_00081ddc @ 0x00081ddc
 * public-name: FUN_00081ddc
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00081ddc @ 0x81ddc  (parity: 300/300 trials, PROVEN) */

extern void FUN_0004d944(unsigned int, unsigned int, unsigned int, unsigned int);
void FUN_00081ddc(unsigned int a, unsigned int b, unsigned int c, unsigned int unused)
{
    (void)unused;
    FUN_0004d944(a, b, c, 0);
}
```