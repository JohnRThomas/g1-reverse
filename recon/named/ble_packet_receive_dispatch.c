/* named: ble_packet_receive_dispatch */
/* Reconstructed ble_packet_receive_dispatch @ 0x21d78  (parity: 300/300 trials, PROVEN) */

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

