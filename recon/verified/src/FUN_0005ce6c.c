/* Reconstructed Zephyr smp_public_key_periph @ 0x0005ce6c.
 * Raw/address back-map: FUN_0005ce6c / 0x0005ce6c.
 * Pinned upstream identity: subsys/bluetooth/host/smp.c.
 */
#include <stddef.h>
#include <stdint.h>

typedef void (*passkey_display_cb_t)(void *connection, uint32_t passkey);
typedef void (*passkey_entry_cb_t)(void *connection);

struct bt_conn_auth_cb_raw {
    passkey_display_cb_t passkey_display;
    passkey_entry_cb_t passkey_entry;
};

struct log_record_two_raw {
    uint32_t count;
    uint32_t format;
};

struct log_record_three_raw {
    uint32_t count;
    uint32_t format;
    uint32_t value;
};

extern struct bt_conn_auth_cb_raw *FUN_0005cac0(void *smp);
extern int FUN_00082ff6(void *bits, uint32_t bit);
extern int FUN_00086be4(const void *left, const void *right, size_t size);
extern void FUN_00083074(uintptr_t source, uint32_t level,
                         const void *record);
extern void *FUN_000830b0(void *smp, uint32_t command);
extern void *FUN_0005f5d0(void *buffer_data, size_t size);
extern void FUN_0005cb38(void *smp, void *buffer, void *user_data);
extern void FUN_00083090(void *bits, uint32_t bit);
extern unsigned int FUN_0005cdc4(int);
extern int FUN_00055cb4(void *, int);
extern void *FUN_0005caa4(uint32_t flag);
extern int FUN_0005cc68(int);

#define latch_auth_cb                 FUN_0005cac0 /* 0x0005cac0 */
#define atomic_test_bit_raw           FUN_00082ff6 /* 0x00082ff6 */
#define memory_compare                FUN_00086be4 /* 0x00086be4 */
#define log_process_record            FUN_00083074 /* 0x00083074 */
#define smp_create_pdu_raw            FUN_000830b0 /* 0x000830b0 */
#define net_buf_add_raw               FUN_0005f5d0 /* 0x0005f5d0 */
#define smp_send_raw                  FUN_0005cb38 /* 0x0005cb38 */
#define atomic_set_bit_raw            FUN_00083090 /* 0x00083090 */
#define smp_send_pairing_confirm_raw  FUN_0005cdc4 /* 0x0005cdc4 */
#define random_bytes                  FUN_00055cb4 /* 0x00055cb4 */
#define smp_find_raw                  FUN_0005caa4 /* 0x0005caa4 */
#define smp_dhkey_generate_raw        FUN_0005cc68 /* 0x0005cc68 */

#define SC_PUBLIC_KEY_SLOT ((uint8_t *volatile *)UINT32_C(0x2000af48))

enum pairing_method_raw {
    JUST_WORKS_RAW = 0,
    PASSKEY_INPUT_RAW = 1,
    PASSKEY_DISPLAY_RAW = 2,
    PASSKEY_CONFIRM_RAW = 3,
    PASSKEY_ROLE_RAW = 4,
    LE_SC_OOB_RAW = 5,
};

static inline uint32_t load_u32_raw(const uint8_t *base, size_t offset)
{
    return *(const uint32_t *)(const void *)(base + offset);
}

static inline void store_u32_raw(uint8_t *base, size_t offset, uint32_t value)
{
    *(uint32_t *)(void *)(base + offset) = value;
}

uint8_t smp_public_key_periph(void *context)
{
    uint8_t *smp = (uint8_t *)context;
    struct bt_conn_auth_cb_raw *auth = latch_auth_cb(smp);
    uint8_t *public_key = *SC_PUBLIC_KEY_SLOT;

    /* SMP_FLAG_SC_DEBUG_KEY is bit 14; pkey begins at +0x57. */
    if (!atomic_test_bit_raw(smp + 4, 14) &&
        memory_compare(smp + 0x57, public_key, 32) == 0) {
        const struct log_record_two_raw rejected = { 2, 0x000f4e96 };
        log_process_record(0x00088180, 0x1080, &rejected);
        return 8;
    }

    /* sc_send_public_key(), inlined by the shipped -Os build. */
    void *buffer = smp_create_pdu_raw(smp, 12);
    if (buffer == NULL) {
        return 8;
    }

    uint8_t *request = net_buf_add_raw((uint8_t *)buffer + 12, 64);
    for (size_t word = 0; word != 16; ++word) {
        ((uint32_t *)(void *)request)[word] =
            ((const uint32_t *)(const void *)public_key)[word];
    }
    smp_send_raw(smp, buffer, NULL);

    switch (smp[8]) {
    case JUST_WORKS_RAW:
    case PASSKEY_CONFIRM_RAW: {
        atomic_set_bit_raw(smp, 4); /* BT_SMP_CMD_PAIRING_RANDOM */
        int error = smp_send_pairing_confirm_raw(smp);
        if (error != 0) {
            return (uint8_t)error;
        }
        break;
    }

    case PASSKEY_INPUT_RAW:
        atomic_set_bit_raw(smp, 3);  /* BT_SMP_CMD_PAIRING_CONFIRM */
        atomic_set_bit_raw(smp, 14); /* BT_SMP_KEYPRESS_NOTIFICATION */
        atomic_set_bit_raw(smp + 4, 10); /* SMP_FLAG_USER */
        auth->passkey_entry((void *)(uintptr_t)load_u32_raw(smp, 0xf0));
        break;

    case PASSKEY_DISPLAY_RAW: {
        /* display_passkey() latches the callback independently. */
        auth = latch_auth_cb(smp);
        if (random_bytes(smp + 0xd8, 4) != 0) {
            return 8;
        }
        uint32_t passkey = load_u32_raw(smp, 0xd8) % UINT32_C(1000000);
        store_u32_raw(smp, 0xd8, passkey);
        smp[0xdc] = 0;
        if (auth != NULL && auth->passkey_display != NULL) {
            atomic_set_bit_raw(smp + 4, 11); /* SMP_FLAG_DISPLAY */
            auth->passkey_display(
                (void *)(uintptr_t)load_u32_raw(smp, 0xf0), passkey);
        }
        atomic_set_bit_raw(smp, 3);
        atomic_set_bit_raw(smp, 14);
        break;
    }

    case LE_SC_OOB_RAW:
        atomic_set_bit_raw(smp, 4);
        break;

    case PASSKEY_ROLE_RAW:
    default: {
        const struct log_record_three_raw unknown = {
            3, 0x000f4e7a, smp[8]
        };
        log_process_record(0x00088180, 0x1840, &unknown);
        return 8;
    }
    }

    /* generate_dhkey(), inlined by the shipped build. */
    atomic_set_bit_raw(smp + 4, 7); /* SMP_FLAG_DHKEY_PENDING */
    if (smp_find_raw(8) != NULL) {  /* SMP_FLAG_DHKEY_GEN */
        return 0;
    }
    return (uint8_t)smp_dhkey_generate_raw(smp);
}
