/* Reconstructed FUN_0005ad38 @ 0x0005ad38 (bt_gatt_service_register).
 * Raw/address backmap: FUN_0005ad38 @ 0x0005ad38, extent 0x0000021c.
 */
#include <stdint.h>
extern void FUN_0007e2fa(const char *, ...); /* printk */
extern void FUN_0007e2ec(const char *, uint32_t); /* assert_post_action */
extern uint32_t FUN_0008270c(volatile uint32_t *); /* atomic_get */
extern void FUN_00059cb4(void); /* bt_gatt_service_init */
extern int FUN_00080d3e(const void *, const void *); /* bt_uuid_cmp */
extern void FUN_00073b1c(void); /* k_sched_lock */
extern void FUN_00073bf4(void); /* k_sched_unlock */
extern void FUN_00082c9c(uint16_t, uint16_t, void *, void *); /* foreach attr */
extern void FUN_00082a42(uint32_t, uint32_t, const void *); /* logger */
extern void FUN_0005a570(uint16_t, uint16_t); /* sc_indicate */
extern void FUN_0005a6b0(void); /* db_changed */

struct gatt_attr_recovered {
    const void *uuid;
    void *read;
    void *write;
    void *user_data;
    uint16_t handle;
    uint8_t perm;
    uint8_t reserved;
};
struct gatt_service_recovered {
    struct gatt_attr_recovered *attrs;
    uint16_t attr_count;
    uint16_t reserved;
    struct gatt_service_recovered *next;
};
struct uuid16_recovered { uint8_t type; uint8_t pad; uint16_t value; };

int FUN_0005ad38(struct gatt_service_recovered *service)
{
    if (service == 0) {
        FUN_0007e2fa((const char *)0x00099cbdU, (const char *)0x000f4a06U,
                     (const char *)0x000f46b8U, 0x670U);
        FUN_0007e2fa((const char *)0x000f4a0aU);
        FUN_0007e2ec((const char *)0x000f46b8U, 0x670U);
    }
    if (service->attrs == 0) {
        FUN_0007e2fa((const char *)0x00099cbdU, (const char *)0x000f4a20U,
                     (const char *)0x000f46b8U, 0x671U);
        FUN_0007e2fa((const char *)0x000f4a0aU);
        FUN_0007e2ec((const char *)0x000f46b8U, 0x671U);
    }
    if (service->attr_count == 0) {
        FUN_0007e2fa((const char *)0x00099cbdU, (const char *)0x000f4a2bU,
                     (const char *)0x000f46b8U, 0x672U);
        FUN_0007e2fa((const char *)0x000f4a0aU);
        FUN_0007e2ec((const char *)0x000f46b8U, 0x672U);
    }

    volatile uint32_t *const flags = (volatile uint32_t *)0x2000af04U;
    if ((FUN_0008270c(flags) & 1U) != 0U &&
        (FUN_0008270c((volatile uint32_t *)0x20006448U) & 4U) == 0U) {
        const uint32_t package[2] = { 2U, 0x000f4a3bU };
        FUN_00082a42(0x00088128U, 0x1040U, package);
        return -22;
    }

    FUN_00059cb4();
    struct uuid16_recovered gap = { 0U, 0U, 0x1800U };
    struct uuid16_recovered gatt = { 0U, 0U, 0x1801U };
    if (FUN_00080d3e(service->attrs[0].uuid, &gap) == 0 ||
        FUN_00080d3e(service->attrs[0].uuid, &gatt) == 0)
        return -120;

    FUN_00073b1c();
    volatile uintptr_t *const db_head = (volatile uintptr_t *)0x2000af08U;
    volatile uintptr_t *const db_tail = (volatile uintptr_t *)0x2000af0cU;
    uint16_t handle;
    uint16_t last_handle;
    if (*db_head == 0) {
        handle = *(volatile uint16_t *)0x2000ff3cU;
        last_handle = 0;
    } else {
        struct gatt_service_recovered *last =
            (struct gatt_service_recovered *)(*db_tail - 8U);
        handle = last->attrs[last->attr_count - 1U].handle;
        last_handle = handle;
    }

    for (uint16_t i = 0; i < service->attr_count; ++i) {
        struct gatt_attr_recovered *attr = &service->attrs[i];
        if (attr->handle == 0U) {
            attr->handle = ++handle;
        } else if (attr->handle > handle) {
            handle = attr->handle;
        } else {
            const struct gatt_attr_recovered *found = 0;
            FUN_00082c9c(attr->handle, attr->handle,
                         (void *)0x000825bbU, &found);
            if (found != 0) {
                const uint32_t package[3] = {
                    3U, 0x000f4a7dU, attr->handle,
                };
                FUN_00082a42(0x00088128U, 0x1840U, package);
                FUN_00073bf4();
                return -22;
            }
        }
    }

    const uintptr_t service_node = (uintptr_t)service + 8U;
    service->next = 0;
    if (last_handle == 0U || service->attrs[0].handle > last_handle) {
        if (*db_tail == 0) {
            *db_head = service_node;
            *db_tail = service_node;
        } else {
            *(volatile uintptr_t *)*db_tail = service_node;
            *db_tail = service_node;
        }
    } else {
        struct gatt_service_recovered *previous = 0;
        struct gatt_service_recovered *current =
            (struct gatt_service_recovered *)(*db_head - 8U);
        while (current != 0 &&
               current->attrs[0].handle <= service->attrs[0].handle) {
            previous = current;
            current = current->next == 0 ? 0 :
                (struct gatt_service_recovered *)((uintptr_t)current->next - 8U);
        }
        service->next = current == 0 ? 0 :
            (struct gatt_service_recovered *)((uintptr_t)current + 8U);
        if (previous != 0)
            previous->next = (struct gatt_service_recovered *)service_node;
        else
            *db_head = service_node;
        if (current == 0)
            *db_tail = service_node;
    }

    if ((FUN_0008270c(flags) & 1U) == 0U) {
        FUN_00073bf4();
        return 0;
    }
    FUN_0005a570(service->attrs[0].handle,
                 service->attrs[service->attr_count - 1U].handle);
    FUN_0005a6b0();
    FUN_00073bf4();
    return 0;
}
