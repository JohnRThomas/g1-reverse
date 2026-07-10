/*
 * esb_sync.h  -  Even G1 (nRF5340 app core, NCS 2.5.1)
 *
 * Left/Right (master/slave) inter-lens synchronisation.
 *
 * G1 is two independent nRF5340 lenses; the master lens mirrors its state to
 * the slave so both displays and settings stay consistent. The transport is
 * NOT a Zephyr message queue: the app core stages a frame into a shared-SRAM
 * mailbox (0x20018c6f TX buffer, 0x2000302b inbound status) and hands it to the
 * radio/ESB path through a bound transceive callback stored at ctx+0x774
 * (spi_master_trans_data_tx_rx), then spin-polls a completion byte (ctx+0x105a)
 * with 1-tick busy-waits. Delivery is sequence-numbered (ctx+0xda); the slave RX
 * entry local_esbs_ipc_service_recv() detects "same package", "loss package",
 * "suspend/resume package" and "up/down recving" against that counter.
 *
 * sync_to_slave() is the generic single-frame push (payload,len,seq,flags);
 * FUN_00027448() is the segmented/large-frame push (0xda-byte chunks, opcodes
 * 0xb/0xc, with an ack-echo mailbox at 0x20018d6b). Higher-level helpers push
 * specific state: runtime_info_sync, not_disturb_sync_data, onboarding_sync_data,
 * SendPowerInfoToSlave, SendSystemLanguageInfoToSlave, and the signalling
 * wrapper sync_message_signal_to_slave. FUN_000286f8() is the master sync
 * pump/dispatcher that drives all of the above each tick. Role/channel/addressing
 * come from the global sync context returned by FUN_000167a8() (device_info_t:
 * device_type, esb_channel_number, mac_addresses); the bring-up log line
 * "--role:%d --mode:%d, esb_channel %d ... esb_master_addr .. esb_slave_addr"
 * is emitted here.
 *
 * Function bodies are NOT here; each prototype maps to a reconstructed source
 * file recon/named/<name>.c (or recon/verified/src/<name>.c). Addresses are the
 * app-core flash offsets (link base 0xC200).
 *
 * PUBLIC vs INTERNAL is taken from the authoritative reference graph: the public
 * set below is exactly the module's cross-module `api` set; everything under
 * "internal" is only reachable from within esb_sync (or from its own owning
 * unit) and must not be treated as a stable entry point.
 */
#ifndef G1_ESB_SYNC_H
#define G1_ESB_SYNC_H

#include <stdint.h>
#include "device_info.h"      /* struct device_info_t global state */

/* Ghidra-decompiler type aliases (signatures are as-reconstructed) */
typedef uint8_t  byte; typedef uint8_t  u8; typedef uint8_t  undefined1;
typedef uint16_t u16;  typedef uint16_t undefined2;
typedef uint32_t u32;  typedef uint32_t uint; typedef uint32_t undefined4; typedef uint32_t undefined;
typedef uint64_t u64;  typedef uint64_t undefined8;

/* ======================================================================== */
/* PUBLIC API  (== reference-graph `api` set: called from other modules)     */
/* ======================================================================== */

/* Slave-side RX entry for the ESB IPC service; demuxes an inbound sync frame
 * against the sequence counter and applies it locally.                      @0x15960 */
undefined4 local_esbs_ipc_service_recv(int param_1, byte *param_2);

/* Low-level SPI full-duplex transfer used by the master transport;
 * init path logs "[spi_master init]". Bound at ctx+0x774 and invoked by the
 * *push* routines to actually clock a staged mailbox frame out.             @0x262ac */
unsigned int spi_master_trans_data_tx_rx(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4, unsigned int param_5);

/* Generic single-frame push to the slave lens (payload, len, seq, flags);
 * the retry path logs "retry sync_to_slave failed !".                       @0x26f74 */
uint32_t sync_to_slave(char *param_1, uint32_t param_2, uint32_t *param_3, uint32_t param_4);

/* Segmented / large-frame push: builds a packet into the shared-SRAM TX
 * mailbox (0x20018c6f, opcode 4) for cmd 0xb/0xc bulk 0xda-byte chunks, with
 * an ack-echo compare against 0x20018d6b for cmd 1; spin-waits on ctx+0x105a. @0x27448 */
uint32_t FUN_00027448(char *param_1, uint32_t param_2, uint32_t *param_3, uint32_t param_4);

/* Master sync pump / top-level dispatcher: each tick pushes all queued state
 * (calls sync_to_slave, FUN_00027448, FUN_000275fc, sync_message_signal_to_slave,
 * FUN_0002efa8, FUN_0007ce60, update_persist_task_status).                   @0x286f8 */
void FUN_000286f8(unsigned param_1);

/* Signalling / event wrapper over sync_to_slave (control messages rather
 * than bulk state); also resets transfer state via FUN_0007ce40.            @0x2c224 */
unsigned int sync_message_signal_to_slave(unsigned int param_1, unsigned int param_2, unsigned int param_3);

/* Do-Not-Disturb settings push; logs "slave sync not_disturb sub_step %d".  @0x3ce04 */
uint32_t not_disturb_sync_data(uint8_t *param_1, uint32_t param_2, uint32_t param_3);

/* Onboarding step push; logs "SYNC onboarding action_cmd %d and sub_step %d
 * to slave".                                                                @0x42c8c */
uint32_t onboarding_sync_data(uint8_t *param_1, uint32_t param_2, uint32_t param_3);

/* Battery / power-state push.                                               @0x488bc */
unsigned int SendPowerInfoToSlave(int param_1);

/* System-language-selection push.                                          @0x48998 */
u32 SendSystemLanguageInfoToSlave(int param_1);

/* Reset the active transfer / display-sync context: zeroes ctx recv/ack
 * bytes (0xe9,0xea,0xcc..0xcf) and the 399-byte panel buffer at *(ctx+0x100c);
 * param_1 selects clear-vs-init of the display packet header.               @0x7ce60 */
void FUN_0007ce60(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4);

/* Set/restore the sync sequence field ctx+0xd0 = param_1 (used by the push
 * routines to roll the seq back on failure or commit it on success).        @0x7d230 */
unsigned int FUN_0007d230(unsigned int param_1);

/* ======================================================================== */
/* INTERNAL  (reachable only within esb_sync's owning unit; NOT public api)  */
/* ======================================================================== */

/* Runtime/status snapshot push. Cross-topic callers exist (FUN_00016eb8,
 * FUN_0002a8d8) but the module partition keeps it internal.                 @0x16268 */
unsigned int runtime_info_sync(unsigned short *param_1);

/* Notification/message delivery pump step: dequeues a pending ring entry
 * (FUN_00033b88), branches on role, issues sync_to_slave/FUN_00027448 with
 * opcode 0xa/0xb/0xc, advances retry counter 0x20018d82, sets entry state.  @0x275fc */
void FUN_000275fc(void);

/* Read inbound slave status byte from net-core mailbox 0x2000302f when role
 * == master (else 0).                                                       @0x2efa8 */
unsigned char FUN_0002efa8(void);

/* Dequeue next pending notification/message record from the ring at
 * 0x20008dac (gated v118!=0 && v116==0 && v115<4); copies the 0x1b4-byte
 * entry to staging 0x20007bf4 and returns its address (or 0).               @0x33b88 */
unsigned int FUN_00033b88(void);

/* Set the delivery-state byte (offset +0xd) of ring entry index param_1
 * (stride 0x1b4, base 0x20007dac).                                          @0x33bf0 */
void FUN_00033bf0(int param_1, uint8_t param_2);

/* Find a ring-entry slot by id: scans indices 10..19 (stride 0x1b4) of the
 * table at *0x33c48 for a ready, non-busy entry whose id == param_1;
 * returns the entry address or 0.                                           @0x33c18 */
int FUN_00033c18(int param_1);

#endif /* G1_ESB_SYNC_H */
