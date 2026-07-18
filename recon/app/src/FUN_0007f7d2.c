/* Reconstructed FUN_0007f7d2 @ 0x0007f7d2 (bt_ancs_app_attr_request).
 * Exact configured NCS ANCS app-attribute request owner; extent 0xc2.
 */
#include <stdint.h>
extern void FUN_000836ec(void *, void *, uint32_t); /* net_buf_simple_init_with_data */
extern uint32_t FUN_00083730(void *);               /* net_buf_simple_tailroom */
extern void FUN_00083758(void *, uint8_t);          /* net_buf_simple_add_u8 */
extern void FUN_00083740(void *, const void *, uint32_t); /* net_buf_simple_add_mem */
extern int FUN_0004f198(void *, uint16_t, void *);  /* bt_ancs_cp_write */

struct simple_buffer_recovered {
    uint8_t *data;
    uint16_t length;
    uint16_t size;
    uint8_t *storage;
};

int FUN_0007f7d2(uint8_t *client, const uint8_t *app_id,
                 uint32_t app_id_length, void *callback)
{
    if (app_id_length == 0U)
        return -22;
    client[0x908] = 0;
    if ((__atomic_fetch_or((uint32_t *)(client + 4), 4U,
                           __ATOMIC_SEQ_CST) & 4U) != 0U)
        return -16;
    struct simple_buffer_recovered buffer;
    FUN_000836ec(&buffer, client + 0x28, 0x800U);
    buffer.data = buffer.storage;
    buffer.length = 0;
    if (FUN_00083730(&buffer) < 1U)
        return -12;
    FUN_00083758(&buffer, 1U);
    if (FUN_00083730(&buffer) < app_id_length + 1U)
        return -12;
    FUN_00083740(&buffer, app_id, app_id_length);
    FUN_00083758(&buffer, 0U);
    *(uint32_t *)(client + 0x8f8) = 0;
    if (client[0x8e8] != 0U) {
        if (FUN_00083730(&buffer) < 1U)
            return -12;
        FUN_00083758(&buffer, 0U);
        *(uint32_t *)(client + 0x8f8) = 1;
    }
    int error = FUN_0004f198(client, buffer.length, callback);
    *(uint32_t *)(client + 0x904) = *(uint32_t *)(client + 0x8f8);
    return error;
}
