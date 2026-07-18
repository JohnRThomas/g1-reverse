/* readable reconstruction; identity: FUN_0102d938 @ 0x0102d938
 * public-name: FUN_0102d938
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   g1_ipc_rpmsg_register_ept                <= FUN_0102da84 @ 0x0102da84
 *   get_ept_slot_with_name                   <= FUN_01039f4c @ 0x01039f4c
 *   strncpy                                  <= FUN_0103b5a4 @ 0x0103b5a4
 * address symbols (name @ address):
 *   rodata_103cf0a                           @ 0x0103cf0a
 */
/* net-core FUN_0102d938 @ 0x102d938; true CFG extent 0x102da14 (220 bytes) */
#include <stdint.h>
extern void FUN_01036410(void *, int32_t, int32_t);
extern void FUN_01039fb2(void *);
extern int FUN_0102d6e0(void *, void **, const void *);
extern void *get_ept_slot_with_name(void *, uint32_t);
extern void strncpy(void *, const void *, uint32_t);
extern void FUN_0102d69c(void *, void *, const void *, uint32_t);
extern int g1_ipc_rpmsg_register_ept(void *, uint32_t, void *);

struct request_2d938 {
    const void *data;
    uint8_t reserved[4];
    uint8_t callback_record[12];
    void *callback_argument;
};

int FUN_0102d938(uint8_t *owner, void **output, struct request_2d938 *request)
{
    uint8_t *state = *(uint8_t **)(owner + 0x10);
    if (*(volatile uint32_t *)(state + 0x37c) != 2) return -16;
    if (request->data == 0 || *(const uint8_t *)request->data == 0) return -22;

    void *record;
    if (*(void **)(state + 0x378) == 0) {
        void *guard = state + 0x1b0;
        FUN_01036410(guard, -1, -1);
        int reused = FUN_0102d6e0(state, &record, request->data);
        if (record == 0) {
            FUN_01039fb2(guard);
            return -22;
        }
        *(void **)((uint8_t *)record + 0x68) = request->callback_record;
        *(void **)((uint8_t *)record + 0x6c) = request->callback_argument;
        *((uint8_t *)record + 0x64) = 0;
        *(void **)((uint8_t *)record + 0x3c) = record;
        if (reused) {
            FUN_01039fb2(guard);
            FUN_0102d69c(state, record, request->data,
                          *(uint32_t *)((uint8_t *)record + 0x60));
        } else {
            strncpy((uint8_t *)record + 0x40, request->data, 0x20);
            FUN_01039fb2(guard);
        }
    } else {
        record = get_ept_slot_with_name(state, 0x0103cf0a);
        if (record == 0) return -22;
        *(void **)((uint8_t *)record + 0x68) = request->callback_record;
        *(void **)((uint8_t *)record + 0x6c) = request->callback_argument;
        *(void **)((uint8_t *)record + 0x3c) = record;
        *((uint8_t *)record + 0x64) = 0;
        strncpy((uint8_t *)record + 0x40, request->data, 0x20);
        if (g1_ipc_rpmsg_register_ept(state, 1, record) != 0) return -22;
    }
    *output = record;
    return 0;
}
