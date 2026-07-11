/* Reconstructed FUN_00085030 @ 0x85030. */

struct list_owner;
struct list_node;
extern struct list_node *FUN_00084f06(struct list_owner *owner, int index);

struct list_node *FUN_00085030(struct list_owner *owner, int index)
{
    if (index < 0)
        return 0;
    return FUN_00084f06(owner, index);
}
