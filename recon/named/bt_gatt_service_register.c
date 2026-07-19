/* readable reconstruction; identity: FUN_0005ad38 @ 0x0005ad38
 * public-name: bt_gatt_service_register
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_service_init                     <= FUN_00059cb4 @ 0x00059cb4
 *   sc_indicate                              <= FUN_0005a570 @ 0x0005a570
 *   gatt_reset_cf_and_change_aware           <= FUN_0005a6b0 @ 0x0005a6b0
 *   bt_gatt_service_register                 <= FUN_0005ad38 @ 0x0005ad38
 *   k_sched_unlock                           <= FUN_00073b1c @ 0x00073b1c
 *   k_sched_lock                             <= FUN_00073bf4 @ 0x00073bf4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 *   read_struct_first_word                   <= FUN_0008270c @ 0x0008270c
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   bt_gatt_foreach_attr_0                   <= FUN_00082c9c @ 0x00082c9c
 * address symbols (name @ address):
 *   rodata_825bb                             @ 0x000825bb
 *   rodata_88128                             @ 0x00088128
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f4a06                             @ 0x000f4a06
 *   rodata_f4a0a                             @ 0x000f4a0a
 *   rodata_f4a20                             @ 0x000f4a20
 *   rodata_f4a2b                             @ 0x000f4a2b
 *   rodata_f4a3b                             @ 0x000f4a3b
 *   rodata_f4a7d                             @ 0x000f4a7d
 *   g_bt_gatt_flags                          @ 0x20006448
 *   gatt_service_init_guard                  @ 0x2000af04
 *   g_bt_gatt_dynamic_db                     @ 0x2000af08
 *   g_2000af0c                               @ 0x2000af0c
 *   last_static_handle                       @ 0x2000ff3c
 */
/* Reconstructed FUN_0005ad38 @ 0x0005ad38 (bt_gatt_service_register).
 * Raw/address backmap: FUN_0005ad38 @ 0x0005ad38, extent 0x0000021c.
 */
#include <stdint.h>
extern void printk(const char *, ...); /* printk */
extern void assert_post_action(const char *, uint32_t); /* assert_post_action */
extern uint32_t read_struct_first_word(volatile uint32_t *); /* atomic_get */
extern void bt_gatt_service_init(void); /* bt_gatt_service_init */
extern int bt_uuid_cmp(const void *, const void *); /* bt_uuid_cmp */
extern void k_sched_unlock(void); /* k_sched_lock */
extern void k_sched_lock(void); /* k_sched_unlock */
extern void bt_gatt_foreach_attr_0(uint16_t, uint16_t, void *, void *); /* foreach attr */
extern void log_msg_create_3arg(uint32_t, uint32_t, const void *); /* logger */
extern void sc_indicate(uint16_t, uint16_t); /* sc_indicate */
extern void gatt_reset_cf_and_change_aware(void); /* db_changed */

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

int bt_gatt_service_register(struct gatt_service_recovered *service)
{
    if (service == 0) {
        printk((const char *)0x00099cbdU, (const char *)0x000f4a06U,
                     (const char *)0x000f46b8U, 0x670U);
        printk((const char *)0x000f4a0aU);
        assert_post_action((const char *)0x000f46b8U, 0x670U);
    }
    if (service->attrs == 0) {
        printk((const char *)0x00099cbdU, (const char *)0x000f4a20U,
                     (const char *)0x000f46b8U, 0x671U);
        printk((const char *)0x000f4a0aU);
        assert_post_action((const char *)0x000f46b8U, 0x671U);
    }
    if (service->attr_count == 0) {
        printk((const char *)0x00099cbdU, (const char *)0x000f4a2bU,
                     (const char *)0x000f46b8U, 0x672U);
        printk((const char *)0x000f4a0aU);
        assert_post_action((const char *)0x000f46b8U, 0x672U);
    }

    volatile uint32_t *const flags = (volatile uint32_t *)0x2000af04U;
    if ((read_struct_first_word(flags) & 1U) != 0U &&
        (read_struct_first_word((volatile uint32_t *)0x20006448U) & 4U) == 0U) {
        const uint32_t package[2] = { 2U, 0x000f4a3bU };
        log_msg_create_3arg(0x00088128U, 0x1040U, package);
        return -22;
    }

    bt_gatt_service_init();
    struct uuid16_recovered gap = { 0U, 0U, 0x1800U };
    struct uuid16_recovered gatt = { 0U, 0U, 0x1801U };
    if (bt_uuid_cmp(service->attrs[0].uuid, &gap) == 0 ||
        bt_uuid_cmp(service->attrs[0].uuid, &gatt) == 0)
        return -120;

    k_sched_unlock();
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
            bt_gatt_foreach_attr_0(attr->handle, attr->handle,
                         (void *)0x000825bbU, &found);
            if (found != 0) {
                const uint32_t package[3] = {
                    3U, 0x000f4a7dU, attr->handle,
                };
                log_msg_create_3arg(0x00088128U, 0x1840U, package);
                k_sched_lock();
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

    if ((read_struct_first_word(flags) & 1U) == 0U) {
        k_sched_lock();
        return 0;
    }
    sc_indicate(service->attrs[0].handle,
                 service->attrs[service->attr_count - 1U].handle);
    gatt_reset_cf_and_change_aware();
    k_sched_lock();
    return 0;
}
