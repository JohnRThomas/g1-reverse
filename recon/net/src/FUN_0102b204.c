/* P4 iteration 30 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_210045e0[];
extern unsigned char g1_net_ram_blk_21004c98[];
#define G1N_21004610 ((unsigned long)(g1_net_ram_blk_210045e0 + 0x30))
#define G1N_21004c9d ((unsigned long)(g1_net_ram_blk_21004c98 + 0x5))
#define G1N_21004ca0 ((unsigned long)(g1_net_ram_blk_21004c98 + 0x8))
#else
#define G1N_21004610 0x21004610ul
#define G1N_21004c9d 0x21004c9dul
#define G1N_21004ca0 0x21004ca0ul
#endif
/* net-core FUN_0102b204 @ 0x0102b204  (P4 iteration 30, NEW reconstruction)
 * Readable identity: g1_esb_uplink_worker_thread.
 *
 * Raw back-map: runtime 0x0102ba04..0x0102baac (analysis 0x0102b204, 168 B).
 * This is the function iteration 18 SS18.3 deferred as "the thread ENTRY POINT
 * IS NOT RECONSTRUCTED": FUN_0102b1c8 (= the endpoint `ready` callback that
 * FUN_0102b2ac installs at state+0xb0) creates a thread whose shipped entry is
 * the runtime Thumb pointer 0x0102ba05.  Ghidra folded 0x0102b204..0x0102b2ac
 * into the tail of FUN_0102b1c8, so it had neither a catalogue entry nor a
 * reconstruction, `rodata_102ba05` resolved to the raw original-image address,
 * and the thread was created with K_FOREVER so it could never be scheduled.
 *
 * IT IS THE ONLY CALLER OF FUN_0102a408, the {0x0d, 0x02} relay that sets the
 * app core's device_info[0x105a] = 2 and releases sync_to_slave.  It is also
 * the only caller of FUN_0102a668, which allocates the 251 x 4 ESB uplink
 * message queue at 0x210045b0, and of FUN_0102a474 (staged-frame clear).
 *
 * Structure (r5 = *(void **)0x21004610 = the endpoint object = state + 0xb0,
 * so r5 - 0xb0 = state->role, r5 - 0x8c = state->sem_b, r5 - 8 = state->send):
 *
 *   msg[0..251] = 0
 *   msg[0] = (state->role == 1) ? 6 : 4     ; ipc0 service id of the reply
 *   g1_esb_uplink_msgq_init()
 *   for (;;) {
 *       if (state->mode == 1) { k_sleep(0x28000 ticks = 5 s); continue; }
 *       if (rx_role[0x21004c9d] == 2 && !event_busy[0x21004ca0]) {
 *           g1_esb_pending_frame_clear();
 *           g1_esb_sync_ack_relay(2);        ; -> device_info[0x105a] = 2
 *           rx_role = 0;
 *       }
 *       if (k_msgq_get(&uplink, msg + 1) == 0)
 *           ten-attempt state->send(msg, 252) with a 10 ms back-off;
 *       k_sem_take(state->sem_b, K_FOREVER); ; woken by FUN_0102a4b0 from the
 *   }                                        ; ESB event handler FUN_0102a4c8
 *
 * `rx_role = 2` is written by FUN_0102a4c8 exactly where it calls FUN_0102a4b0
 * (k_sem_give on state->sem_b), i.e. on the ESB RX_RECEIVED event that
 * satisfies `rx_state == 1 && rx_ready == 2`.  The pair is the net core's half
 * of the L<->R sync handshake decoded in armemul/docs/g1-esb-sync-decode.md
 * SS8.1.
 *
 * The two sleeps are k_timeout_t tick counts, verified against the 32768 Hz
 * system clock: 0x28000 = 163840 ticks = 5000 ms, 0x148 = 328 ticks = 10 ms.
 */
#include <stdint.h>

extern void FUN_0103b62e(void *destination, int value, unsigned int length);
extern uint32_t FUN_0102a498(void);
extern void FUN_01037c64(unsigned int ticks_low, unsigned int ticks_high);
extern void FUN_0102a474(void);
extern void FUN_0102a408(uint32_t status);
extern int FUN_0102a6e0(void *destination);
extern void FUN_0103689c(void *object, int ignored, int timeout_low,
                         int timeout_high);
extern int FUN_0102a668(void);

typedef int (*g1_ipc_send_fn)(const void *message, uint32_t size);

void FUN_0102b204(void *unused_p1, void *unused_p2, void *unused_p3)
{
    volatile uint8_t *const rx_role = (volatile uint8_t *)G1N_21004c9d;
    volatile uint8_t *const event_busy = (volatile uint8_t *)G1N_21004ca0;
    unsigned char message[252] __attribute__((aligned(4)));
    unsigned char *service;

    (void)unused_p1;
    (void)unused_p2;
    (void)unused_p3;

    service = *(unsigned char *volatile *)G1N_21004610;

    *(uint32_t *)message = 0;
    FUN_0103b62e(message + 4, 0, 0xf8u);
    message[0] = (*(volatile int32_t *)(service - 0xb0) == 1) ? 6u : 4u;

    FUN_0102a668();

    for (;;) {
        uint8_t role;

        if (FUN_0102a498() == 1) {
            FUN_01037c64(0x28000u, 0u);
            continue;
        }

        role = *rx_role;
        if (role == 2) {
            uint8_t busy = *event_busy;

            if (busy == 0) {
                FUN_0102a474();
                FUN_0102a408(role);
                *rx_role = busy;
            }
        }

        if (FUN_0102a6e0(message + 1) == 0) {
            unsigned char retries = 10;

            for (;;) {
                g1_ipc_send_fn send =
                    *(g1_ipc_send_fn *)(service - 8);

                if (send(message, 0xfcu) > 0) {
                    break;
                }
                retries = (unsigned char)(retries - 1u);
                if (retries == 0) {
                    break;
                }
                FUN_01037c64(0x148u, 0u);
            }
        }

        FUN_0103689c(service - 0x8c, 0, -1, -1);
    }
}
