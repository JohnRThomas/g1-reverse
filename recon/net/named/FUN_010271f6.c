/* readable reconstruction; identity: FUN_010271f6 @ 0x010271f6
 * public-name: FUN_010271f6
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010271f6 @ 0x010271f6, exact Thumb extent 0x36 bytes. */
#include <stdint.h>

struct controller_storage_node {
    struct controller_storage_node *next;
    uint16_t capacity;
};

struct controller_storage_list {
    struct controller_storage_node *head;
    struct controller_storage_node embedded;
};

extern void FUN_01027196(struct controller_storage_node *node,
                         uint16_t capacity);
extern void FUN_010271b8(struct controller_storage_node *node,
                         struct controller_storage_node **head);

#define controller_storage_node_init FUN_01027196
#define controller_storage_list_prepend FUN_010271b8

/* Initialize the embedded node and make it the sole list member. */
void FUN_010271f6(struct controller_storage_list *storage, uint16_t capacity)
{
    volatile uint16_t narrowed_capacity = capacity;
    storage->head = 0;
    controller_storage_node_init(&storage->embedded, narrowed_capacity);
    controller_storage_list_prepend(&storage->embedded, &storage->head);
}
