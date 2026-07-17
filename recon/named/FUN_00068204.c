/* readable reconstruction; identity: FUN_00068204 @ 0x00068204
 * public-name: FUN_00068204
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_module_registry_node                   @ 0x20002c3c
 *   g_metal_generic_bus                      @ 0x2000b424
 */
/* Reconstructed FUN_00068204 @ 0x68204  (parity: 300/300 trials, PROVEN) */

typedef unsigned int u32;
#define G6823C 0x2000b424UL

int FUN_00068204(u32 *param_1)
{
    char *p0 = *(char**)param_1;
    if (p0 == (char*)0 || *p0 == 0 || (unsigned int)param_1[2] > 1) {
        return (int)0xffffffea;
    }
    param_1[1] = 0x20002c3cUL;
    u32 node_addr = (u32)((char*)param_1 + 0x44);
    u32 old_next = *(volatile u32*)(G6823C + 0x1c);
    param_1[0x12] = old_next;
    param_1[0x11] = (u32)(G6823C + 0x18);
    *(volatile u32*)(G6823C + 0x1c) = node_addr;
    *(volatile u32*)old_next = node_addr;
    return 0;
}
