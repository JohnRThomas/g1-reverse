/* readable reconstruction; identity: FUN_00084c7e @ 0x00084c7e
 * public-name: wdt_feed
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 *   wdt_feed                                 <= FUN_00084c7e @ 0x00084c7e
 */
/* Reconstructed FUN_00084c7e @ 0x84c7e  (parity: 300/300 trials, PROVEN) */

extern int dev_write_reg3(unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int wdt_feed(void *param_1, int param_2)
{
    unsigned int *p = *(volatile unsigned int**)((char*)param_1 + 4);
    if (param_2 == 0) {
        return dev_write_reg3(*(volatile unsigned int*)p, 7, 4, 1);
    }
    return 0xffffffea;
}
