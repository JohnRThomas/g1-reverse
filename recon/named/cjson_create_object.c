/* readable reconstruction; identity: FUN_00064ca4 @ 0x00064ca4
 * public-name: cjson_create_object
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_create_object                      <= FUN_00064ca4 @ 0x00064ca4
 *   alloc_zeroed_node                        <= FUN_00084fd4 @ 0x00084fd4
 * address symbols (name @ address):
 *   g_cjson_hooks                            @ 0x20002bac
 */
/* Reconstructed FUN_00064ca4 @ 0x64ca4  (parity: 300/300 trials, PROVEN) */

extern unsigned int alloc_zeroed_node(unsigned int a);

void cjson_create_object(void)
{
    unsigned int v = *(volatile unsigned int*)0x20002bacUL;
    unsigned int r = alloc_zeroed_node(v);
    if (r != 0) {
        *(volatile unsigned int*)(r + 0xc) = 0x40;
    }
}
