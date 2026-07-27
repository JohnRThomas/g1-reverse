/* readable reconstruction; identity: FUN_00084e72 @ 0x00084e72
 * public-name: flash_area_write_and_close
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_area_open                          <= FUN_0004e048 @ 0x0004e048
 *   flash_read_boot_swap_ate                 <= FUN_0006403c @ 0x0006403c
 *   nullsub_3                                <= FUN_0007ef7e @ 0x0007ef7e
 *   flash_area_write_and_close               <= FUN_00084e72 @ 0x00084e72
 */
/* Reconstructed FUN_00084e72 @ 0x84e72  (parity: 300/300 trials, PROVEN) */

extern int flash_area_open(unsigned int a, void *b, unsigned int c, unsigned int d, unsigned int e);
extern unsigned int flash_read_boot_swap_ate(int, unsigned char *);
extern void nullsub_3(unsigned int a);

unsigned int flash_area_write_and_close(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    unsigned int uVar2;
    unsigned int local_c;
    local_c = param_2;
    iVar1 = flash_area_open(param_1 & 0xff, &local_c, param_3, param_4, param_1);
    if (iVar1 == 0) {
        uVar2 = flash_read_boot_swap_ate(local_c, param_2);
        nullsub_3(local_c);
    } else {
        uVar2 = 1;
    }
    return uVar2;
}
