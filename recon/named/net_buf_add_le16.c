/* readable reconstruction; identity: FUN_000836f8 @ 0x000836f8
 * public-name: net_buf_add_le16
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_push                      <= FUN_0005f518 @ 0x0005f518
 *   net_buf_add_le16                         <= FUN_000836f8 @ 0x000836f8
 */
/* Reconstructed FUN_000836f8 @ 0x836f8  (parity: 300/300 trials, PROVEN) */

extern unsigned char *net_buf_simple_push(unsigned int a, unsigned int b);

void net_buf_add_le16(unsigned int param_1, unsigned int param_2)
{
    unsigned char *puVar1 = net_buf_simple_push(param_1, 2);
    puVar1[0] = (unsigned char)param_2;
    puVar1[1] = (unsigned char)(param_2 >> 8);
}
