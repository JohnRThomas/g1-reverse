/*
 * ipc_sync.h  —  Even G1 app-core: shared IPC / L-R synchronisation messages.
 *
 * Two distinct transports live here; both are reconstructed from field-offset
 * usage in the proven bodies under recon/named/ and recon/verified/src/, cross-
 * checked against recon/modules/ipc_core/ and recon/modules/esb_sync/.
 *
 *   (A) app-core <-> net-core  : Zephyr ipc_service / RPMsg (ipc_core module).
 *   (B) master-lens <-> slave-lens : spin-polled shared-SRAM mailbox clocked
 *                                    out over Nordic ESB (esb_sync module).
 *
 * The *_sync_pkg family (master_sync_pkg + its panel_data_pkg) is the (B)
 * payload. master_sync_pkg is NOT a separate allocation: it is a named overlay
 * of the L-R sync staging region that lives inside the global device_info_t at
 * byte offset 0xC9 (the block returned by FUN_000167a8() / get_device_info()).
 * The on-wire frame (esb_sync_frame_t) is assembled from that region by
 * sync_to_slave() @0x26f74 and clocked out through the transceive callback
 * bound at device_info_t + 0x774.
 *
 * Field names are reconstructed from the accessing functions; offsets are the
 * load-bearing part. Unresolved bytes are called out inline and summarised at
 * the end of this file.
 */
#ifndef G1_IPC_SYNC_H
#define G1_IPC_SYNC_H

#include <stdint.h>

/* These records are byte-exact overlays of firmware memory / on-wire frames,
 * so every struct here is packed (no compiler-inserted alignment padding). */
#if defined(__GNUC__) || defined(__clang__)
#define G1_PACKED __attribute__((packed))
#else
#define G1_PACKED
#endif

/* ======================================================================== */
/* (B) L-R sync payloads — the *_sync_pkg family                             */
/* ======================================================================== */

/*
 * master_sync_pkg — L/R sync staging + packet-header region.
 *
 * Overlays struct device_info_t starting at offset 0xC9. Every field offset
 * below is (device_info_t offset - 0xC9). sync_to_slave() reads this region to
 * build an esb_sync_frame_t; local_esbs_ipc_service_recv() @0x15960 writes it
 * back from an inbound frame on the slave side.
 *
 * The command/flags byte hdr_flags: bits[5:0] = command/type, bits[7:6] =
 * up/down direction flags (0x80 = "up", 0x40 = "down").
 *
 * sizeof == 0x20 (0xC9..0xE8 inclusive of the param tail).
 */
struct G1_PACKED master_sync_pkg {
    uint8_t  hdr_flags;      /* dev+0xC9  cmd = &0x3f, dir = &0xc0 (0x80 up/0x40 down) */
    uint8_t  hdr_b1;         /* dev+0xCA  recv param_2[1]                              */
    uint8_t  hdr_b2;         /* dev+0xCB  recv param_2[2]                              */
    uint8_t  up_ack;         /* dev+0xCC  up-direction ack marker (cmp vs recv_up)     */
    uint8_t  down_ack;       /* dev+0xCD  down-direction ack marker (cmp vs recv_down) */
    uint8_t  up_pending;     /* dev+0xCE  "up recving" in-flight flag                  */
    uint8_t  down_pending;   /* dev+0xCF  "down recving" in-flight flag                */
    uint8_t  seq_committed;  /* dev+0xD0  sync sequence commit/rollback slot           */
    uint16_t field_d1;       /* dev+0xD1  packed into frame[12..13]                    */
    uint8_t  field_d3;       /* dev+0xD3  packed into frame[14]                         */
    uint8_t  packed_cmd;     /* dev+0xD4  per-frame packed cmd: (cmd&0x3f)|(updn<<6)   */
    uint8_t  app_id;         /* dev+0xD5  current running application id                */
    uint16_t sub_field_d6;   /* dev+0xD6  copied from device_info_t + 0x1072           */
    int16_t  sub_field_d8;   /* dev+0xD8  device_info_t+0xeb8 + device_info_t+0x1074   */
    uint8_t  seq;            /* dev+0xDA  per-frame sequence counter (incremented)      */
    uint8_t  payload_db[10]; /* dev+0xDB..0xE4  frame body payload (staged/echoed)      */
    uint8_t  param_e5;       /* dev+0xE5  sync_command_type  (param_3 tail, up to 4 B)  */
    uint8_t  param_e6;       /* dev+0xE6  sync_sub_command                              */
    uint8_t  param_e7;       /* dev+0xE7  sync_param1                                   */
    uint8_t  param_e8;       /* dev+0xE8  sync_param2                                   */
};

/* Direction / command bit helpers for master_sync_pkg.hdr_flags & packed_cmd */
#define SYNC_CMD_MASK   0x3Fu
#define SYNC_DIR_MASK   0xC0u
#define SYNC_DIR_UP     0x80u
#define SYNC_DIR_DOWN   0x40u

/*
 * esb_sync_frame_t — the 0x21-byte (33) shared-SRAM frame clocked out to the
 * slave lens. Built by sync_to_slave() into a stack buffer, then handed to
 * (*(fp774_t)(device_info_t + 0x774))(&frame, 0x21). Byte layout mirrors the
 * master_sync_pkg region: frame[1..] = &master_sync_pkg.hdr_flags.
 *
 *   [0]      opcode / frame tag (0 for sync_to_slave frames;
 *            FUN_00027448 large-frame path uses opcode 4 in the TX mailbox)
 *   [1..4]   device_info_t 0xC9..0xCC   (hdr_flags,hdr_b1,hdr_b2,up_ack)
 *   [5..7]   zero pad
 *   [8..11]  device_info_t 0xCD..0xD0   (down_ack,up_pending,down_pending,seq_committed)
 *   [12..13] device_info_t 0xD1..0xD2   (field_d1)
 *   [14]     device_info_t 0xD3         (field_d3)
 *   [15]     zero pad
 *   [16..32] device_info_t 0xD4..0xE4   (packed_cmd .. payload tail)
 */
struct G1_PACKED esb_sync_frame {
    uint8_t opcode;      /* +0                                          */
    uint8_t hdr[4];      /* +1  <- dev 0xC9..0xCC                       */
    uint8_t pad_5[3];    /* +5  zero                                    */
    uint8_t body0[4];    /* +8  <- dev 0xCD..0xD0                       */
    uint16_t field_d1;   /* +12 <- dev 0xD1                             */
    uint8_t field_d3;    /* +14 <- dev 0xD3                             */
    uint8_t pad_15;      /* +15 zero                                    */
    uint8_t body1[17];   /* +16 <- dev 0xD4..0xE4 (packed_cmd + tail)   */
};                        /* sizeof == 0x21                             */

/*
 * panel_data_pkg — display panel packet buffer.
 *
 * Reached indirectly: device_info_t holds a pointer to this buffer at offset
 * 0x100C. FUN_0007ce60() @0x7ce60 (re)initialises it: byte[0] = display state,
 * a small header, then zeroes the 399-byte (0x18F) body at (buffer + 8).
 * local_esbs_ipc_service_recv() drives byte[0] through the display state
 * machine (values 2 / 0xB, seq at buffer+7 written = 8, etc).
 *
 * sizeof == 8 + 0x18F == 0x197 (407).
 */
struct G1_PACKED panel_data_pkg {
    uint8_t  state;      /* +0   display/transfer state (2, 0xB, ...)   */
    uint8_t  hdr[6];     /* +1   packet header                          */
    uint8_t  seq;        /* +7   sequence byte (read as *(ptr0x1000)+7) */
    uint8_t  body[399];  /* +8   399-byte panel payload (cleared @ +8)  */
};                        /* sizeof == 0x197                            */

/* ---- subsystem push payloads (thin wrappers over master_sync_pkg) -------
 * These are the per-topic buffers handed to the *_sync_data / Send*ToSlave
 * helpers; each is copied into master_sync_pkg.payload_db before framing. The
 * helpers take (buf, len, sub_step); the buffers are opaque byte blobs whose
 * meaning is topic-specific, so they are modelled as sized byte arrays. */
struct G1_PACKED not_disturb_sync_data_pkg { uint8_t data[16]; }; /* DND settings   */
struct onboarding_sync_data_pkg  { uint8_t data[16]; }; /* onboarding step */

/* ======================================================================== */
/* (A) app-core <-> net-core IPC records (ipc_core module)                   */
/* ======================================================================== */

/*
 * ipc_response_msg — record posted to the app-core dashboard response msgq
 * (g_dashboard_response_msgq @0x2000392c) by send_response_data_to_msgqueue()
 * @0x47b1c. The queue element size is 0x18; payload is capped at 0x14 bytes.
 */
struct G1_PACKED ipc_response_msg {
    uint8_t  type;         /* +0   record type (1 for the BLE control record) */
    uint8_t  rsv;          /* +1                                              */
    uint16_t len;          /* +2   payload length (< 0x15)                    */
    uint8_t  payload[0x14];/* +4   copied response bytes                       */
};                          /* sizeof == 0x18                                 */

/*
 * runtime_info_ipc — 8-byte packet emitted by runtime_info_sync() @0x16268 via
 * global_ipc_service_send(&pkt, 8). Assembled from a uint16 + 3 trailing bytes:
 *   word0 = (info[0] << 16) | 0x0001 ; word1 = b[2] | b[3]<<8 | b[4]<<16
 */
struct G1_PACKED runtime_info_ipc {
    uint8_t  msg_id;   /* +0  == 0x01                          */
    uint8_t  rsv;      /* +1  == 0                              */
    uint16_t info;     /* +2  *param_1                          */
    uint8_t  b2;       /* +4                                    */
    uint8_t  b3;       /* +5                                    */
    uint8_t  b4;       /* +6                                    */
    uint8_t  pad;      /* +7  == 0                              */
};                      /* sizeof == 8                          */

/*
 * ipc_handler_desc — one entry of the first-byte demux table walked by
 * ipc0_ept_recv() @0x25a48. The endpoint context holds a count at +4 followed
 * by an array of pointers to these descriptors; a descriptor matches when its
 * msg_id equals the inbound buffer's first byte, and its recv thunk (at +8) is
 * called as recv(ctx - 0x714, buf + 1, len - 1).
 */
typedef void (*ipc_handler_fn)(int ctx, int payload, int len);
struct G1_PACKED ipc_handler_desc {
    uint8_t        msg_id;   /* +0  matched against inbound buf[0]     */
    uint8_t        pad[7];   /* +1                                     */
    ipc_handler_fn recv;     /* +8  dispatch thunk                     */
};

/*
 * ipc_ept_ctx — the IPC endpoint context installed by
 * register_ipc_service_context() @0x25d40 at g_ipc0_endpoint (0x20007a84).
 * Only the fields touched by the reconstructed bodies are modelled; the rest
 * of the ipc_service endpoint state is opaque platform data.
 *   +0x60 = TX thunk (0x00025b79)   +0x64 = alt thunk (0x00025ae9)
 *   +4    = handler-table count, immediately followed by the descriptor ptrs
 */
struct G1_PACKED ipc_ept_ctx {
    uint32_t              _reserved0;      /* +0                          */
    int32_t               handler_count;  /* +4                          */
    struct ipc_handler_desc *handlers[1]; /* +8  flexible: [handler_count]*/
    /* ... opaque ipc_service endpoint state up to +0x60 ...             */
    /* +0x60 tx_thunk ; +0x64 alt_thunk (set by register_ipc_service_context) */
};

#endif /* G1_IPC_SYNC_H */

/*
 * ---- Unresolved fields ---------------------------------------------------
 *  - master_sync_pkg.field_d1 / field_d3 / sub_field_d6 / sub_field_d8:
 *      copied verbatim into the frame; their semantic meaning (timestamp vs
 *      brightness vs raster tuning) is not pinned by the accessing functions.
 *  - master_sync_pkg.payload_db[10]: topic-specific staging bytes; exact
 *      sub-structure varies by command (0xa/0xb/0xc notification, DND, etc.).
 *  - esb_sync_frame.opcode: 0 for sync_to_slave frames but the shared-SRAM TX
 *      mailbox path (FUN_00027448) writes opcode 4 — the two share the wire
 *      byte0 but the enumeration of opcodes is not fully recovered.
 *  - panel_data_pkg.hdr[6]: header bytes between state and seq are written by
 *      the display pipeline (other module) and are not resolved here.
 *  - ipc_ept_ctx: bytes 0x08..0x60 are ipc_service-internal (Zephyr) and left
 *      opaque; only the count/handler array and the two thunk slots are known.
 */
