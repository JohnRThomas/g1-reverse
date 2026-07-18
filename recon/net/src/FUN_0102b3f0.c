/* CPUNET ESB startup announcement and receive-state service @ 0x0102b3f0.
 * Raw back-map: FUN_0102b3f0@0x0102b3f0; true extent 0x98.
 * CFG_VERIFY_CALL_ARITIES=3,0,4,1,0,1,0,3
 */
#include <stdint.h>

extern void FUN_0103b62e(void *destination, int value, unsigned int length);
extern unsigned int FUN_0102a468(void);
extern void FUN_0103b53a(void *destination, const void *source,
                         unsigned int length, unsigned int destination_size);
extern void FUN_0103b614(void *destination, const void *source,
                         unsigned int length);
extern int FUN_01033660(void *packet);
extern int FUN_010339d0(void);
extern int FUN_01033858(void);

#define g1_esb_identity_read       FUN_0102a468
#define g1_esb_packet_publish      FUN_01033660
#define g1_esb_tx_pending          FUN_010339d0
#define esb_start_tx               FUN_01033858
#define g1_esb_start_announcement  FUN_0102b3f0

void g1_esb_start_announcement(unsigned int announce_start)
{
    volatile uint8_t *const packet = (volatile uint8_t *)0x21004ca1u;
    const uint8_t *const identity = (const uint8_t *)0x21004b9fu;
    volatile uint8_t *const receive_mode = (volatile uint8_t *)0x21004fa2u;
    volatile uint8_t *const service_state = (volatile uint8_t *)0x21004c9bu;
    volatile uint32_t *const idle_count = (volatile uint32_t *)0x21004614u;
    struct {
        uint32_t header;
        uint8_t tail[247];
    } scratch;
    unsigned int identity_byte = 0;
    uint8_t next_service_state;

    scratch.header = 0;
    FUN_0103b62e(scratch.tail, 0, sizeof(scratch.tail));
    if (announce_start != 0) {
        *packet = 0;
        identity_byte = g1_esb_identity_read();
        if (identity_byte != 0) {
            packet[1] = 0;
            packet[3] = 0;
            FUN_0103b53a((void *)(packet + 5), identity, identity_byte, 0xfbu);
            *packet = (uint8_t)identity_byte;
            next_service_state = 1;
        } else {
            packet[1] = 0;
            packet[3] = 0;
            *(uint8_t *)&scratch.header =
                (*receive_mode != 0) ? 0x10u : 0x11u;
            FUN_0103b614((void *)(packet + 5), &scratch, 0xfbu);
            *packet = 0x20u;
            next_service_state = 2;
        }
        if (g1_esb_packet_publish((void *)packet) != 0) {
            goto out;
        }
        if (identity_byte != 0 && *receive_mode == 1 &&
            g1_esb_tx_pending() == 0) {
            (void)g1_esb_packet_publish((void *)packet);
        }
        *service_state = next_service_state;
    }

    if (*receive_mode == 0 && esb_start_tx() == 0) {
        *idle_count = *idle_count + 1;
    }
out:
    return;
}
