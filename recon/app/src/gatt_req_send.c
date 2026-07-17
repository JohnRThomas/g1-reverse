/* Reconstructed gatt_req_send @ 0x00082aee (FUN_00082aee; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: subsys/bluetooth/host/gatt.c. */
#include <stdint.h>
extern uintptr_t FUN_000596c0(uint32_t timeout, uint32_t unused);
extern void FUN_00059708(uintptr_t req);
extern uintptr_t FUN_00058eb0(uintptr_t conn, uint32_t op, uint32_t len);
extern void FUN_000825ac(uintptr_t buf, uintptr_t cb, uintptr_t user, uint32_t option);
extern int FUN_00059a90(uintptr_t conn, uintptr_t req);
typedef int (*encode_t)(uintptr_t buf, uint32_t len, uintptr_t params);
int gatt_req_send(uintptr_t conn, uintptr_t callback, uintptr_t params,
                  encode_t encode, uint32_t op, uint32_t len)
{
    uint32_t opcode = (uint8_t)op;
    uintptr_t req = FUN_000596c0(0x000f0000u, 0u);
    if (req == 0u) return -12;
    *(volatile uintptr_t *)(req + 4u) = callback;
    *(volatile uint8_t *)(req + 0x11u) = (uint8_t)opcode;
    *(volatile uint32_t *)(req + 0x14u) = len;
    *(volatile encode_t *)(req + 0x0cu) = encode;
    *(volatile uintptr_t *)(req + 0x18u) = params;
    uintptr_t buf = FUN_00058eb0(conn, opcode, len);
    if (buf == 0u) {
        FUN_00059708(req);
        return -12;
    }
    FUN_000825ac(buf, 0u, 0u, 1u);
    *(volatile uintptr_t *)(req + 8u) = buf;
    int err = encode(buf, len, params);
    if (err == 0) err = FUN_00059a90(conn, req);
    if (err != 0) FUN_00059708(req);
    return err;
}
