#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00082aee @ 0x00082aee
 * public-name: gatt_req_send
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_att_create_pdu                        <= FUN_00058eb0 @ 0x00058eb0
 *   bt_att_req_alloc                         <= FUN_000596c0 @ 0x000596c0
 *   bt_att_req_free                          <= FUN_00059708 @ 0x00059708
 *   bt_att_req_send                          <= FUN_00059a90 @ 0x00059a90
 *   bt_att_set_tx_meta_data                  <= FUN_000825ac @ 0x000825ac
 * address symbols (name @ address):
 *   rodata_f0000                             @ 0x000f0000
 */
/* Reconstructed gatt_req_send @ 0x00082aee (FUN_00082aee; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: subsys/bluetooth/host/gatt.c. */
#include <stdint.h>
extern uintptr_t bt_att_req_alloc(uint32_t timeout, uint32_t unused);
extern void bt_att_req_free(uintptr_t req);
extern int bt_att_create_pdu(int, int, int);
extern void bt_att_set_tx_meta_data(int, int, int, int);
extern unsigned bt_att_req_send(int, unsigned*);
typedef int (*encode_t)(uintptr_t buf, uint32_t len, uintptr_t params);
int gatt_req_send(uintptr_t conn, uintptr_t callback, uintptr_t params,
                  encode_t encode, uint32_t op, uint32_t len)
{
    uint32_t opcode = (uint8_t)op;
    uintptr_t req = bt_att_req_alloc(((unsigned long)&rodata_f0000) /*=0xf0000*/, 0u);
    if (req == 0u) return -12;
    *(volatile uintptr_t *)(req + 4u) = callback;
    *(volatile uint8_t *)(req + 0x11u) = (uint8_t)opcode;
    *(volatile uint32_t *)(req + 0x14u) = len;
    *(volatile encode_t *)(req + 0x0cu) = encode;
    *(volatile uintptr_t *)(req + 0x18u) = params;
    uintptr_t buf = bt_att_create_pdu(conn, opcode, len);
    if (buf == 0u) {
        bt_att_req_free(req);
        return -12;
    }
    bt_att_set_tx_meta_data(buf, 0u, 0u, 1u);
    *(volatile uintptr_t *)(req + 8u) = buf;
    int err = encode(buf, len, params);
    if (err == 0) err = bt_att_req_send(conn, req);
    if (err != 0) bt_att_req_free(req);
    return err;
}
