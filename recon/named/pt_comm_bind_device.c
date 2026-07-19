/* readable reconstruction; identity: FUN_000330a8 @ 0x000330a8
 * public-name: pt_comm_bind_device
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   pt_comm_bind_device                      <= FUN_000330a8 @ 0x000330a8
 * address symbols (name @ address):
 *   g_fuel_gauge_dev                         @ 0x20002424
 *   g_pt_comm_state                          @ 0x2000242c
 */
/* Reconstructed FUN_000330a8 @ 0x330a8  (parity: 300/300 trials, PROVEN) */

unsigned int pt_comm_bind_device(unsigned int param_1)
{
    if (param_1 == 0) {
        return 0xffffffff;
    }
    if (*(volatile unsigned int*)0x20002424UL != param_1) {
        *(volatile unsigned int*)0x20002424UL = param_1;
    }
    *(volatile unsigned char*)0x2000242cUL = 0;
    return 0;
}
