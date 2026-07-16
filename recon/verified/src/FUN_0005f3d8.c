/* Reconstructed FUN_0005f3d8 @ 0x5f3d8, exact extent 100 bytes. */
#include <stdint.h>

typedef struct list_node {
    uint32_t value;
    struct list_node *next;
} list_node_t;

extern void FUN_0005f24c(list_node_t *node);
extern void FUN_0007e2fa(uintptr_t format, ...);
extern void FUN_0007e2ec(uintptr_t file, uint32_t line);

list_node_t *FUN_0005f3d8(list_node_t *previous, list_node_t *node)
{
    if (node == 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000f542du, 0x000f539au, 0x262u);
        FUN_0007e2ec(0x000f539au, 0x262u);
        return 0;
    }
    if (previous != 0) {
        if (previous->next == 0) {
            FUN_0007e2fa(0x00099cbdu, 0x000f540eu, 0x000f539au, 0x265u);
            FUN_0007e2ec(0x000f539au, 0x265u);
            return 0;
        }
        if (previous->next != node) {
            FUN_0007e2fa(0x00099cbdu, 0x000f541cu, 0x000f539au, 0x266u);
            FUN_0007e2ec(0x000f539au, 0x266u);
            return 0;
        }
        previous->next = node->next;
    }

    list_node_t *next = node->next;
    node->next = 0;
    FUN_0005f24c(node);
    return next;
}
