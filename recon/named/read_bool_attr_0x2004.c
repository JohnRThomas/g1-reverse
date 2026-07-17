/* readable reconstruction; identity: FUN_0007ca24 @ 0x0007ca24
 * public-name: read_bool_attr_0x2004
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_send_len_prefixed_packet_locked_retry <= FUN_00025788 @ 0x00025788
 *   read_bool_attr_0x2004                    <= FUN_0007ca24 @ 0x0007ca24
 */
/* Reconstructed FUN_0007ca24 @ 0x7ca24  (parity: 300/300 trials, PROVEN) */

extern int ipc_send_len_prefixed_packet_locked_retry(int,int,int,int,int);
void read_bool_attr_0x2004(int param_1, unsigned char *param_2)
{
    unsigned char stackbuf[4];
    *param_2 = 0;
    int iVar1 = ipc_send_len_prefixed_packet_locked_retry(param_1, 0x2004, (int)&stackbuf[3], 1, param_1);
    if (iVar1 == 0) {
        if (stackbuf[3] != 0) {
            *param_2 = 1;
        } else {
            *param_2 = 0;
        }
    }
}
