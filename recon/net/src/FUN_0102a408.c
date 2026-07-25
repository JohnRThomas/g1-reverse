/* P4 iteration 30 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_210045e0[];
#define G1N_210045f4 ((unsigned long)(g1_net_ram_blk_210045e0 + 0x14))
#else
#define G1N_210045f4 0x210045f4ul
#endif
/* net-core FUN_0102a408 @ 0x0102a408  (P4 iteration 30, NEW reconstruction)
 * Readable identity: g1_esb_sync_ack_relay.
 *
 * Raw back-map: runtime 0x0102ac08..0x0102ac48 (analysis 0x0102a408), the
 * function Ghidra left uncatalogued between FUN_0102a394 and FUN_0102a448.
 * Its ONLY caller is the ESB worker thread FUN_0102b204 (runtime 0x0102ba04),
 * which was itself uncatalogued -- see recon/net/src/FUN_0102b204.c.
 *
 * THIS IS THE FRAME THAT RELEASES THE DISPLAY GATE.  It sends an 8-byte
 * message over the net->app ipc0 endpoint whose first byte is the SERVICE ID
 * 0x01 ("cpunet-hw-id") and whose service payload is {0x0d, status}.  The app
 * core's id-1 receiver FUN_000162ec @0x162ec dispatches buf[0]==0x0d to
 *     device_info[0x105a] = buf[1];
 * so status==2 is what ends the `while (device_info[0x105a] != 2)` spin inside
 * sync_to_slave @0x26f74 and lets display_dispatch_thread blit the dashboard
 * (armemul/docs/g1-esb-sync-decode.md SS6).
 *
 * Shipped prologue `push {r0, r1, r2, r4, r5, lr}` reuses the three saved
 * argument slots as the message buffer; only the first 8 bytes are sent.
 *     strd r3,r3,[sp]      msg[0..7] = 0
 *     strh 0x0d01,[sp]     msg[0] = 0x01 (service id), msg[1] = 0x0d
 *     strb r0,[sp,#2]      msg[2] = status
 * then the standard ten-attempt send retry with a 10 ms back-off, identical in
 * shape to FUN_0102a394 (publish_link_state).
 */
#include <stdint.h>

extern void FUN_0103961c(int milliseconds);

typedef int (*g1_ipc_send_fn)(const void *message, uint32_t size);

void FUN_0102a408(uint32_t status)
{
    uint32_t message[2];
    unsigned char *bytes = (unsigned char *)message;
    unsigned char retries = 10;

    message[0] = 0;
    message[1] = 0;
    bytes[0] = 0x01u;                    /* ipc0 service id: cpunet-hw-id */
    bytes[1] = 0x0du;                    /* app id-1 opcode 13 = sync ack */
    bytes[2] = (unsigned char)status;    /* device_info[0x105a] value */

    for (;;) {
        unsigned char *service =
            *(unsigned char *volatile *)G1N_210045f4;
        g1_ipc_send_fn send = *(g1_ipc_send_fn *)(service + 0xa8);

        if (send(message, 8) > 0) {
            break;
        }
        retries = (unsigned char)(retries - 1u);
        if (retries == 0) {
            break;
        }
        FUN_0103961c(10);
    }
}
