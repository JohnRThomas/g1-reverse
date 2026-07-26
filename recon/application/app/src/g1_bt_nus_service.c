/* ---------------------------------------------------------------------------
 * BRING-UP WIRING TU (P4 iteration 31) — the application's own GATT service,
 * the third entry of the shipped `bt_gatt_service_static` iterable section.
 *
 * MEASURED MOTIVATION.  With `g1-i23a-app` + `g1-i30e-net` the virtual phone
 * connects over the modeled radio and sweeps an ATT write of the real G1 frame
 * `0a 06 00 00 00 00` across handles 0x0F..0x15, exactly as the oracle run
 * does — and a Renode block hook at OUR `ble_process_req_dispatch`
 * (0x0001ee80) fires **0 times** over the whole 20 s capture, while
 * `now_has_persist_task` (0x00028d48) runs 398 times and returns 0 every time.
 * `process_for_new_task` therefore never leaves its `CASE0` poll, never issues
 * `trigger_screen_state_change(reason, ctx, 1)`, `device_info[0xfe8]` stays 0
 * and no pixel is ever blitted.
 *
 * ROOT CAUSE.  The shipped `bt_gatt_service_static` section holds THREE
 * services (app_update.bin, read through tools/extract.py):
 *
 *     0x88058  { attrs = 0x0008b3b4, count = 8 }   Zephyr GATT service
 *     0x88060  { attrs = 0x0008b454, count = 7 }   Zephyr GAP service
 *     0x88068  { attrs = 0x0008ad18, count = 6 }   <-- THIS ONE
 *
 * Our link's `bt_gatt_service_static_area` is 0x10 bytes — only the two Zephyr
 * services (`attr__1_gatt_svc`, `attr__2_gap_svc`).  The 128-bit NUS UUID
 * body `9e ca dc 24 0e e5 a9 e0 93 f3 a3 b5` occurs 5 times in
 * app_update.bin and 0 times in our zephyr.bin, so the application's transport
 * service is simply absent and the phone has nothing to write to.
 *
 * WHAT THE SHIPPED SERVICE IS.  The six attributes at 0x8ad18 (stride 20 =
 * sizeof(struct bt_gatt_attr)) decode as:
 *
 *   #  VA        uuid        read        write       user_data   handle|perm
 *   0  0x8ad18   0x2000357b  0x00082989  --          0x2000357b  0x0000|0x0001
 *                (6E400001-B5A3-F393-E0A9-E50E24DCCA9E, bt_gatt_attr_read_service)
 *   1  0x8ad2c   0x20002f70  0x00082c49  --          0x20002830  |0x0001
 *                (0x2803 characteristic declaration, bt_gatt_attr_read_chrc)
 *   2  0x8ad40   0x20003559  --          --          --          |0x0001
 *                (6E400003.. TX value, BT_GATT_PERM_READ)
 *   3  0x8ad54   0x20002f6c  0x0008295b  0x0005a465  0x20002818  |0x0003
 *                (0x2902 CCC, read/write_ccc, READ|WRITE)
 *   4  0x8ad68   0x20002f68  0x00082c49  --          0x20002810  |0x0001
 *   5  0x8ad7c   0x20003537  --          0x0004f4d9  --          |0x0003
 *                (6E400002.. RX value, on_receive, READ|WRITE)
 *
 * That is byte-for-byte the expansion of stock NCS
 * `nrf/subsys/bluetooth/services/nus.c`'s `BT_GATT_SERVICE_DEFINE(nus_svc, …)`
 * with `CONFIG_BT_NUS_AUTHEN` UNSET (the TX value permission is 0x0001 =
 * BT_GATT_PERM_READ, not BT_GATT_PERM_READ_AUTHEN = 0x0010).  The corroborating
 * detail is placement: the `bt_uuid_128`, `bt_gatt_chrc` and `_bt_gatt_ccc`
 * objects the attributes point at live in `.data` (0x20002810, 0x20002818,
 * 0x20002830 and the seven packed `bt_uuid_128` at 0x20003537..0x200035ad),
 * which is exactly where GCC puts the NON-const compound literals inside the
 * `BT_GATT_CHARACTERISTIC` / `BT_GATT_CCC` / `BT_UUID_DECLARE_128` macros while
 * the attribute array itself is `const` in rodata.  A hand-rolled table would
 * not split that way.
 *
 * WHY THIS FILE AND NOT `CONFIG_BT_NUS=y`.  nus.c owns a file-static
 * `struct bt_nus_cb nus_cb` singleton.  The recovered corpus already owns that
 * singleton at the shipped address 0x2000a2b8 (pinned `g_2000a2b8 =
 * g1_ram_arena + 0x82b8`): `FUN_0004f500` (`bt_nus_init`, retained, parity
 * PROVEN) copies the three callbacks into it, and `FUN_000181f0`
 * (`ancs_notify_sync_init`, called from `ancs_main` line 173) is its only
 * caller, passing the shipped `.data` object at 0x20002310 whose restored
 * initialiser is { received = FUN_00017f70, sent = NULL,
 * send_enabled = FUN_00017e3c }.  Compiling stock nus.c as well would create a
 * SECOND, always-NULL `nus_cb` and the write would be delivered to it — the
 * duplicate-singleton / displacement-fallout class this project has now hit
 * five times (iterations 26, 28, 29, 30 §30.3).  So the service definition is
 * emitted here and its three callbacks read the ONE recovered singleton.
 *
 * The two pins the recovered `bt_nus_send` (`FUN_0004f518` /
 * `gatt_notify_config_change`) spells — `rodata_8ad40` (&attrs[2], the TX value
 * attribute handed to `bt_gatt_notify_cb`) and `rodata_4f4f1` (`on_sent`) —
 * were still ABSOLUTE original-image addresses in
 * recon/symbols/g1_app_globals.ld.  They are bound onto this service here, the
 * same way g1_bt_adv_objects.c binds rodata_8839c / g_20002350 / g_20002358.
 *
 * Integration-only: no canonical parity body changes.
 * ---------------------------------------------------------------------------
 */
#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <bluetooth/services/nus.h>

/* The recovered `nus_cb` singleton: shipped 0x2000a2b8, pinned in
 * recon/symbols/g1_app_globals.ld onto the recovered RAM arena.  Only
 * FUN_0004f500 writes it; only these three callbacks read it. */
extern volatile unsigned int g_2000a2b8;
#define G1_NUS_CB ((const volatile struct bt_nus_cb *)(const void *)&g_2000a2b8)

/* The shipped attribute stride is 20 bytes (0x8ad18, 0x8ad2c, 0x8ad40,
 * 0x8ad54, 0x8ad68, 0x8ad7c).  The rodata_8ad40 rebind below adds 2 * 20, so
 * fail the build loudly rather than silently if the SDK struct ever changes. */
BUILD_ASSERT(sizeof(struct bt_gatt_attr) == 20,
	     "bt_gatt_attr stride must match the shipped 20-byte attributes");

static void g1_nus_ccc_cfg_changed(const struct bt_gatt_attr *attr,
				   uint16_t value)
{
	void (*send_enabled)(enum bt_nus_send_status status) =
		G1_NUS_CB->send_enabled;

	ARG_UNUSED(attr);

	if (send_enabled != NULL) {
		send_enabled(value == BT_GATT_CCC_NOTIFY ?
				     BT_NUS_SEND_STATUS_ENABLED :
				     BT_NUS_SEND_STATUS_DISABLED);
	}
}

static ssize_t g1_nus_on_receive(struct bt_conn *conn,
				 const struct bt_gatt_attr *attr,
				 const void *buf, uint16_t len,
				 uint16_t offset, uint8_t flags)
{
	void (*received)(struct bt_conn *conn, const uint8_t *const data,
			 uint16_t len) = G1_NUS_CB->received;

	ARG_UNUSED(attr);
	ARG_UNUSED(offset);
	ARG_UNUSED(flags);

	if (received != NULL) {
		received(conn, (const uint8_t *)buf, len);
	}

	return len;
}

/* Shipped 0x0004f4f0 (`rodata_4f4f1` is its Thumb pointer): the
 * `bt_gatt_notify_params.func` the recovered bt_nus_send installs. */
__attribute__((used, retain))
void g1_nus_on_sent(struct bt_conn *conn, void *user_data)
{
	void (*sent)(struct bt_conn *conn) = G1_NUS_CB->sent;

	ARG_UNUSED(user_data);

	if (sent != NULL) {
		sent(conn);
	}
}

/* Shipped 0x8ad18..0x8ad90, 6 attributes.  `BT_GATT_SERVICE_DEFINE` emits the
 * global `attr_g1_nus_svc[]` array plus the `bt_gatt_service_static` iterable
 * entry; the section is SORT_BY_NAME, so `g1_nus_svc` lands after Zephyr's
 * `_1_gatt_svc` (8 attrs) and `_2_gap_svc` (7 attrs) — the same order, and
 * therefore the same ATT handles 0x10..0x15, as the shipped image. */
BT_GATT_SERVICE_DEFINE(g1_nus_svc,
	BT_GATT_PRIMARY_SERVICE(BT_UUID_NUS_SERVICE),
	BT_GATT_CHARACTERISTIC(BT_UUID_NUS_TX,
			       BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ,
			       NULL, NULL, NULL),
	BT_GATT_CCC(g1_nus_ccc_cfg_changed,
		    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
	BT_GATT_CHARACTERISTIC(BT_UUID_NUS_RX,
			       BT_GATT_CHRC_WRITE |
			       BT_GATT_CHRC_WRITE_WITHOUT_RESP,
			       BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
			       NULL, g1_nus_on_receive, NULL),
);
