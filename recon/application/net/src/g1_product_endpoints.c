/* Recovered product IPC endpoint ownership.
 *
 * Original initialized-data back-maps:
 *   g1_ipc0_endpoint_config @ 0x21000584
 *   g1_hci_endpoint_config  @ 0x2100059c
 * Callback words remain documented at their shipped runtime Thumb values;
 * this cohesive build expresses them as relocations to the CFG-proven bodies.
 */
#include <stddef.h>
#include <stdint.h>
#include <zephyr/ipc/ipc_service.h>

extern void FUN_0102ac00(void *priv); /*=0x0102b401*/
extern void FUN_0102ab14(const uint8_t *data, size_t size, void *priv); /*=0x0102b315*/
extern void FUN_0102ace8(void *priv); /*=0x0102b4e9*/
extern void FUN_0102adf0(uint8_t *data, uint32_t size); /*=0x0102b5f1*/

struct ipc_ept_cfg g1_ipc0_endpoint_config = {
    .name = "ipc0",
    .prio = 0,
    .cb = {
        .bound = FUN_0102ac00,
        .received = (void (*)(const void *, size_t, void *))FUN_0102ab14,
        .error = NULL,
    },
    .priv = NULL,
};

struct ipc_ept_cfg g1_hci_endpoint_config = {
    .name = "nrf_bt_hci",
    .prio = 0,
    .cb = {
        .bound = FUN_0102ace8,
        .received = (void (*)(const void *, size_t, void *))FUN_0102adf0,
        .error = NULL,
    },
    .priv = NULL,
};
