/*
 * teleprompt: scrolling teleprompter script display driven by the phone.
 *
 * The phone streams a script to the glasses over BLE service SVC_TELEPROMPTER
 * (0x0620); the glasses show it as scrolling text and report progress/"arrived"
 * status back (SVC_TELEPROMPTER_ACK 0x0600, SVC_TELEPROMPTER_PROG 0x0601). The
 * flow is packet-driven: init packet, text-upgrade (append/replace) packets, an
 * arrived-status packet, suspend, and exit; oversized prompt words are dropped
 * and packet-length is validated. A per-frame countdown timer paces the scroll.
 * The script buffer hangs off device_info_t.teleprompter_data_ptr. None of the
 * teleprompter functions are reconstructed into recon/named/ yet; the entry
 * point is ui_teleprompter_task (known from firmware strings), living in the
 * ble_proto/system dispatch groups. See even_protocol.h for the service IDs.
 */
#ifndef G1_TELEPROMPT_H
#define G1_TELEPROMPT_H

/* ---- known-but-not-yet-reconstructed firmware symbols (from debug strings) --
 *   void ui_teleprompter_task(...);  // packet state machine + scroll screen thread
 *
 * BLE services (even_protocol.h):
 *   SVC_TELEPROMPTER      0x0620   phone -> glasses script/control
 *   SVC_TELEPROMPTER_ACK  0x0600   glasses -> phone ack
 *   SVC_TELEPROMPTER_PROG 0x0601   glasses -> phone progress / arrived status
 *
 * Display states (from strings):
 *   TELEPROMPTER_DISPLAY_IDLE / TELEPROMPTER_TEXT_DISPLAY /
 *   TELEPROMPTER_DISPLAY_ABNORMAL_EXIT
 * This header documents the subsystem surface; there are no reconstructed
 * prototypes to declare in this agent's set.                                  */

#endif /* G1_TELEPROMPT_H */
