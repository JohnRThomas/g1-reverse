/* Reconstructed local_esbs_ctrl_ipc_service_recv @ 0x7c00c  (CFG-directed candidate) */
/* Reconstructed local_esbs_ctrl_ipc_service_recv @ 0x7c00c
 * (uncatalogued 4-byte Ghidra gap 0x7c00c..0x7c010: "movs r0,#0; bx lr").
 *
 * Handler registered by main() for the IPC service id 5
 * ("cpunet-esbs-ctrl"); dispatched from ipc0_ept_recv as
 * handler(context, data + 1, length - 1).  The shipped body ignores every
 * argument and reports success.
 */
int local_esbs_ctrl_ipc_service_recv(void *context, const void *packet,
                                     int length)
{
    (void)context;
    (void)packet;
    (void)length;
    return 0;
}
