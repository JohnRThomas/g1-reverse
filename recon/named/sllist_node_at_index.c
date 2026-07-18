/* readable reconstruction; identity: FUN_00085030 @ 0x00085030
 * public-name: sllist_node_at_index
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   linked_node_at_index                     <= FUN_00084f06 @ 0x00084f06
 *   sllist_node_at_index                     <= FUN_00085030 @ 0x00085030
 */
/* Reconstructed FUN_00085030 @ 0x85030. */

struct list_owner;
struct list_node;
extern struct list_node *linked_node_at_index(struct list_owner *owner, int index);

struct list_node *sllist_node_at_index(struct list_owner *owner, int index)
{
    if (index < 0)
        return 0;
    return linked_node_at_index(owner, index);
}
