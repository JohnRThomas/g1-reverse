/* ---------------------------------------------------------------------------
 * BRING-UP WIRING TU (P4 iteration 23) — the application's own
 * `struct bt_conn_cb` entry in the `bt_conn_cb` ITERABLE SECTION.
 *
 * SYMPTOM (iteration 22 §22.7 / §22.11 item 2, measured, not guessed):
 * the virtual central connects (`vcentral Connected` True, 1 CONNECT_IND, 530
 * data events answered) yet the app keeps printing
 *
 *     low_speed_peripheral_dispatch_thread(): Global Working Mode: 10
 *         get_glasses_ble_status 0 ble_is_connected 0
 *
 * ROOT CAUSE (byte evidence below).  The `ble_is_connected` field of that line
 * is `low_speed_peripheral_dispatch_thread`'s local `side`, which can only
 * become 1 when `get_ancs_conn_handle() != 0`
 * (recon/symbolized/app/low_speed_peripheral_dispatch_thread.c:119,144,160).
 * `get_ancs_conn_handle` (FUN_00019b2c) is a one-liner:
 *
 *     return *(volatile unsigned int *)0x20007518;      // g_ancs_conn
 *
 * and `g_ancs_conn` has exactly ONE writer in the whole image —
 * `ancs_connected` (FUN_0001861c @ 0x1861c), its last statement.  So
 * `ble_is_connected 0` says precisely: **`ancs_connected` never ran**.
 *
 * `ancs_connected` is a `struct bt_conn_cb::connected` callback.  In the
 * SHIPPED image it is reached through the `bt_conn_cb` ITERABLE SECTION, whose
 * bounds are the two rodata pins the recovered Zephyr notifiers still carry:
 *
 *     rodata_87fec  = _bt_conn_cb_list_start   (0x00087fec)
 *     rodata_88058  = _bt_conn_cb_list_end     (0x00088058)
 *
 * The stride is proven by the recovered notifier itself —
 * recon/symbolized/app/ble_notify_remote_info_available.c (identity
 * FUN_00056da8, Zephyr's `bt_conn_security_changed`) walks the section with
 * `uVar4 = uVar4 + 0x24`, and follows the registered-list `_next` at `+0x20`.
 * So sizeof(struct bt_conn_cb) = 0x24 = 36 B in the shipped build and the
 * section holds exactly (0x88058 - 0x87fec) / 0x24 = 3 entries.
 *
 * Shipped section contents (read with tools/extract.py's VA mapping; every
 * word below is a literal read of app_update.bin):
 *
 *   0x87fec  0001861d 00018add 00000000 00000000 00000000 000184f1
 *            00000000 00000000 00000000
 *            -> { .connected       = 0x1861c ancs_connected,
 *                 .disconnected    = 0x18adc ancs_disconnected,
 *                 .security_changed= 0x184f0 ancs_security_changed }
 *   0x88010  000220cd 00022079 0 0 0 0 0 0 0
 *   0x88034  00052989 00052a0d 0 0 0 0 0 0 0
 *
 * The member INDEX of each recovered notifier confirms the layout is stock
 * zephyr/include/zephyr/bluetooth/conn.h order (offset -> index -> member):
 *   +0x08 -> 2 -> le_param_req        (ble_notify_disconnected.c, misnamed)
 *   +0x0c -> 3 -> le_param_updated    (ble_notify_le_param_updated.c)
 *   +0x10 -> 4 -> identity_resolved   (ble_notify_identity_resolved.c)
 *   +0x14 -> 5 -> security_changed    (ble_notify_remote_info_available.c,
 *                                      misnamed; it calls the slot with
 *                                      (conn, conn[9] = sec_level, err))
 * i.e. connected[0], disconnected[1], le_param_req[2], le_param_updated[3],
 * identity_resolved[4], security_changed[5], then two more slots and _next[8].
 *
 * IN OUR BUILD the section is real but holds ONE entry, the SDK's own:
 *     000847f4 R _bt_conn_cb_list_start
 *     000847f4 r bt_conn_cb_mcumgr_bt_callbacks
 *     00084810 R _bt_conn_cb_list_end            (0x1c = 28 B = 7 pointers)
 * — CONFIG_BT_SMP=y only, so our `struct bt_conn_cb` is connected,
 * disconnected, le_param_req, le_param_updated, identity_resolved,
 * security_changed, _next.  connected/disconnected/security_changed keep
 * indices 0/1/5 in BOTH layouts (the two shipped extras, CONFIG_BT_REMOTE_INFO
 * and CONFIG_BT_USER_PHY_UPDATE, sit at indices 6/7, AFTER security_changed),
 * so the app entry maps across without ambiguity.
 *
 * The app entry was never emitted: `rodata_87fec` / `rodata_88058` are plain
 * `PROVIDE(... = 0x000879ec/0x00088058)` identity pins into the ORIGINAL
 * image, which our relocated build does not reproduce, and nothing else
 * referenced `ancs_connected`, so --gc-sections dropped all three callbacks
 * (nm on /private/tmp/g1-i22b-app/zephyr/zephyr.elf: no `ancs_connected`,
 * `ancs_disconnected` or `ancs_security_changed` symbol at all).
 *
 * FIX, the documented way (same mechanism as g1_bt_adv_objects.c §22.6): a
 * linker rebind cannot express an object whose CONTENTS are pointers, so the
 * object is EMITTED — here into the genuine iterable section via the stock
 * BT_CONN_CB_DEFINE macro, which is exactly what the shipped firmware used.
 * No canonical parity body is touched; the three callbacks are the recovered,
 * parity-proven bodies.
 * ------------------------------------------------------------------------- */

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>

/* The recovered bodies.  Their reconstructed C prototypes use plain integer
 * words (recon/symbolized/app/ancs_connected.c:38,
 * ancs_disconnected.c:32, recon/named/ancs_security_changed.c:44); the AAPCS
 * argument registers are identical to the bt_conn_cb prototypes, so the
 * addresses are placed through a cast rather than by editing a proven body. */
extern void ancs_connected(int conn, int err);
extern void ancs_disconnected(uint32_t conn, uint32_t reason);
extern void ancs_security_changed(uint32_t conn, uint32_t level, int32_t err);

BT_CONN_CB_DEFINE(g1_ancs_conn_callbacks) = {
	.connected        = (void (*)(struct bt_conn *, uint8_t))ancs_connected,
	.disconnected     = (void (*)(struct bt_conn *, uint8_t))ancs_disconnected,
	.security_changed = (void (*)(struct bt_conn *, bt_security_t,
				      enum bt_security_err))ancs_security_changed,
};
