/* readable reconstruction; identity: FUN_0003483c @ 0x0003483c
 * public-name: notification_icon_type_from_package
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   notification_icon_type_from_package      <= FUN_0003483c @ 0x0003483c
 *   strncmp                                  <= FUN_00087036 @ 0x00087036
 * address symbols (name @ address):
 *   rodata_9adaa                             @ 0x0009adaa
 *   rodata_a819e                             @ 0x000a819e
 *   rodata_a81b7                             @ 0x000a81b7
 *   rodata_a81d0                             @ 0x000a81d0
 *   rodata_a81e6                             @ 0x000a81e6
 *   rodata_a81fa                             @ 0x000a81fa
 *   g_notif_app_pkg_table_buf                @ 0x20007dbc
 */
/* Reconstructed FUN_0003483c @ 0x3483c (strict CFG parity). */
#include <stdint.h>

extern uint8_t strlen(const char *text);
extern uintptr_t get_device_info(void);
extern int strncmp(const void *left, const void *right, uint32_t length);

static uint32_t bounded_length(const char *text)
{
    uint32_t length = strlen(text);
    return length < 31U ? length : 31U;
}

int notification_icon_type_from_package(int slot, uint32_t unused_2, uint32_t unused_3,
                 uint32_t unused_4)
{
    uint8_t *record = (uint8_t *)(0x20007dbcU + (uint32_t)slot * 0x1b4U);
    const char *row;

    (void)unused_2;
    (void)unused_3;
    (void)unused_4;

    if (strncmp((const void *)0x000a819eU, record, 0x18U) == 0 ||
        strncmp((const void *)0x0009adaaU, record, 0x1cU) == 0) {
        return 1;
    }
    if (strncmp((const void *)0x000a81b7U, record, 0x18U) == 0 ||
        strncmp((const void *)0x000a81d0U, record, 0x15U) == 0) {
        return 2;
    }
    if (strncmp((const void *)0x000a81e6U, record, 0x13U) == 0 ||
        strncmp((const void *)0x000a81faU, record, 0x14U) == 0) {
        return 0;
    }

    row = *(volatile uint8_t *)(get_device_info() + 0x1068U) != 0
        ? (const char *)0x20003292U : (const char *)0x20003152U;
    while (*(volatile const uint8_t *)row != 0) {
        if (strncmp(row, record, bounded_length(row)) == 0) {
            return 3;
        }
        row += 0x20;
    }

    row = *(volatile uint8_t *)(get_device_info() + 0x1068U) != 0
        ? (const char *)0x200030d2U : (const char *)0x20003032U;
    while (*(volatile const uint8_t *)row != 0) {
        if (strncmp(row, record, bounded_length(row)) == 0) {
            return 4;
        }
        row += 0x20;
    }
    return 5;
}
