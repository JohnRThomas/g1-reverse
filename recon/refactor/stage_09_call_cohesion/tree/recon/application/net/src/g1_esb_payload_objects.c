/* P4 iteration 29 -- REAL storage for the two `struct esb_payload` objects the
 * Even ESB session layer hands to the (now stock) ESB core.
 *
 * WHY
 * ---
 * recon/application/gen_net_ram_relocs.py sizes a relocation block from the
 * addresses the recovered corpus REFERENCES, not from the object's true
 * extent (iteration 26 SS26.3's stated limitation; iteration 28 SS28.9(3)).
 * Only the base address of each payload is ever named, so both objects were
 * standing on 24 bytes:
 *
 *     PROVIDE(g_esb_rx_payload          = g1_net_ram_blk_21004da0 + 0x1);  /  24 B
 *     PROVIDE(g_esb_sync_response_packet = g1_net_ram_blk_21004ea0 + 0x1); /  24 B
 *
 * The objects are `struct esb_payload` (nrf/include/esb.h):
 *     uint8_t length; uint8_t pipe; int8_t rssi; uint8_t noack; uint8_t pid;
 *     uint8_t data[CONFIG_ESB_MAX_PAYLOAD_LENGTH];
 * i.e. 5 + 251 = 256 bytes each.  The shipped addresses PROVE the size:
 *     g_esb_rx_payload           0x21004da1
 *     g_esb_sync_response_packet 0x21004ea1  = 0x21004da1 + 0x100
 * exactly one sizeof(struct esb_payload) apart, the same 256-byte stride the
 * shipped rx_payload/tx_payload FIFO arrays use (0x21005256 -> 0x21005a56,
 * 8 x 256 B) -- see recon/ownership/net_esb_core_singleton_adoption.json.
 *
 * `esb_read_rx_payload()` MEMCPYs 5 + length bytes INTO g_esb_rx_payload, so a
 * 24-byte block overruns by up to 232 bytes into whatever the linker placed
 * next -- in this link the sibling blocks that carry
 * g_esb_sync_pending_flag / the clock-ready and receive-mode bytes
 * (g1_net_ram_blk_21004fa0).  Measured frames are 32-byte payloads, i.e. a
 * 13-byte overrun on every single received ESB frame.
 *
 * These definitions are ordinary C objects, so the generated PROVIDE() lines
 * become inert (PROVIDE only defines an otherwise-undefined symbol).  Nothing
 * else pins into either block: g1_net_globals.ld binds exactly one symbol to
 * each of the two blocks.
 */

#include <stdint.h>

#define G1_ESB_PAYLOAD_HEADER_BYTES 5
#define G1_ESB_PAYLOAD_BYTES \
	(G1_ESB_PAYLOAD_HEADER_BYTES + CONFIG_ESB_MAX_PAYLOAD_LENGTH)

#define G1_ESB_PAYLOAD_OBJECT __attribute__((used, retain, aligned(4)))

/* MEASURED CONSEQUENCE -- why this is OFF by default (iteration 29 builds
 * `g1-i29b-net` = both objects real, `g1-i29c-net` = rx only).
 *
 * Both variants build clean, pass every gate, and then HALT BOTH CORES ~0.3 s
 * after the virtual slave injects its first ESB ACK (`g1-i29c-net`: ACK at
 * 01:46:49.15, `cpuapp`/`cpunet` "PC does not lay in memory" at 01:46:49.44),
 * i.e. at 1 ESB frame instead of the 0x26C the default build reaches.
 *
 * The reason is not the sizing -- it is what the sizing UNMASKS.  With the
 * 24-byte block, `rx[5]` (= `payload->data[0]`) read block filler, so
 * FUN_0102b50c never took its announce-response branch.  With correct storage
 * `data[0]` really is 0x11 and the branch runs FUN_0102b49c, which
 *     memcpy(packet + 5, &scratch, 0xfb);  packet[0] = 0xfb;
 * i.e. stages a FULL 251-byte ESB payload (a third independent confirmation of
 * CONFIG_ESB_MAX_PAYLOAD_LENGTH = 251) from a 251-byte STACK scratch buffer,
 * inside the ESB event IRQ, and then calls esb_write_payload + esb_start_tx in
 * a loop.  That path has never executed before in this project and it is where
 * the next defect lives.  Turning this on is step 1 of chasing it; it must not
 * be turned on while it costs 0x26B ESB frames, the BLE link and every sensor
 * volume.
 */
#ifdef G1_ESB_REAL_RX_PAYLOAD_OBJECT
/* net-core 0x21004da1 -- the ESB event handler's receive buffer
 * (FUN_0102b50c passes it to esb_read_rx_payload). */
uint8_t g_esb_rx_payload[G1_ESB_PAYLOAD_BYTES] G1_ESB_PAYLOAD_OBJECT;
#endif

/* net-core 0x21004ea1 -- the announce/sync response staging packet
 * (FUN_0102b49c passes it to esb_write_payload).  esb_write_payload only READS
 * this object, so the 24-byte block is a data defect but not an overrun; it is
 * given real storage only when G1_ESB_REAL_TX_PAYLOAD_OBJECT is defined, so the
 * two halves of the fix can be measured independently. */
#ifdef G1_ESB_REAL_TX_PAYLOAD_OBJECT
uint8_t g_esb_sync_response_packet[G1_ESB_PAYLOAD_BYTES] G1_ESB_PAYLOAD_OBJECT;
#endif
