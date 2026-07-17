/* readable reconstruction; identity: FUN_0007c4b6 @ 0x0007c4b6
 * public-name: opt_record_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   opt_field1_set                           <= FUN_0007c430 @ 0x0007c430
 *   opt_field2_set                           <= FUN_0007c456 @ 0x0007c456
 *   opt_field3_set                           <= FUN_0007c48a @ 0x0007c48a
 *   opt_record_init                          <= FUN_0007c4b6 @ 0x0007c4b6
 */
/* Reconstructed FUN_0007c4b6 @ 0x7c4b6  (parity: 300/300 trials, PROVEN) */
extern void opt_field1_set(unsigned char *a0, unsigned int a1, void *a2);
extern void opt_field3_set(unsigned char *a0, void *a1);
extern void opt_field2_set(unsigned char *a0, void *a1);

unsigned int opt_record_init(unsigned char *param_1)
{
    unsigned int uVar1;
    struct {
        unsigned int value;
        unsigned char flag;
    } header = {0};
    unsigned int state[2] = {0, 0};
    if (param_1 == 0) {
        uVar1 = 7;
    } else {
        *param_1 = 0xc0;
        opt_field1_set(param_1, 0, &header);
        opt_field3_set(param_1, &header);
        opt_field2_set(param_1, state);
        uVar1 = 0;
        *(unsigned int*)(param_1 + 0x14) = 0;
        *(unsigned int*)(param_1 + 0x18) = 0;
    }
    return uVar1;
}
