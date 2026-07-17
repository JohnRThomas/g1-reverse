/* readable reconstruction; identity: FUN_00021d78 @ 0x00021d78
 * public-name: ble_packet_receive_dispatch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_packet_receive_dispatch              <= FUN_00021d78 @ 0x00021d78
 *   debug_print_hex_dump                     <= FUN_0004a424 @ 0x0004a424
 *   ble_requeue_command_via_dispatch         <= FUN_0007c244 @ 0x0007c244
 * address symbols (name @ address):
 *   rodata_9dec8                             @ 0x0009dec8
 */
/* Reconstructed FUN_00021d78 @ 0x21d78  (parity: 300/300 trials, PROVEN) */

extern void debug_print_hex_dump(unsigned int a, unsigned int b, unsigned int c);
extern int spec_ble_command_hook(unsigned int a, unsigned int b);
extern void ble_requeue_command_via_dispatch(unsigned int a, unsigned int b);

void ble_packet_receive_dispatch(unsigned int param_1, unsigned int param_2, int param_3)
{
    int iVar1;
    if (param_3 != 0) {
        debug_print_hex_dump(0x0009dec8UL, param_1, param_2);
    }
    iVar1 = spec_ble_command_hook(param_1, param_2);
    if (iVar1 != 0) {
        ble_requeue_command_via_dispatch(param_1, param_2);
    }
}
