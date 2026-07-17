/* readable reconstruction; identity: FUN_0005f3d8 @ 0x0005f3d8
 * public-name: FUN_0005f3d8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f539a                             @ 0x000f539a
 *   rodata_f540e                             @ 0x000f540e
 *   rodata_f541c                             @ 0x000f541c
 *   rodata_f542d                             @ 0x000f542d
 */
/* Reconstructed FUN_0005f3d8 @ 0x5f3d8, exact extent 100 bytes. */
#include <stdint.h>

typedef struct list_node {
    uint32_t value;
    struct list_node *next;
} list_node_t;

extern void net_buf_unref(list_node_t *node);
extern void printk(uintptr_t format, ...);
extern void assert_post_action(uintptr_t file, uint32_t line);

list_node_t *FUN_0005f3d8(list_node_t *previous, list_node_t *node)
{
    if (node == 0) {
        printk(0x00099cbdu, 0x000f542du, 0x000f539au, 0x262u);
        assert_post_action(0x000f539au, 0x262u);
        return 0;
    }
    if (previous != 0) {
        if (previous->next == 0) {
            printk(0x00099cbdu, 0x000f540eu, 0x000f539au, 0x265u);
            assert_post_action(0x000f539au, 0x265u);
            return 0;
        }
        if (previous->next != node) {
            printk(0x00099cbdu, 0x000f541cu, 0x000f539au, 0x266u);
            assert_post_action(0x000f539au, 0x266u);
            return 0;
        }
        previous->next = node->next;
    }

    list_node_t *next = node->next;
    node->next = 0;
    net_buf_unref(node);
    return next;
}
