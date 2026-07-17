/* readable reconstruction; identity: FUN_00080d9a @ 0x00080d9a
 * public-name: bt_uuid_create
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_uuid_create                           <= FUN_00080d9a @ 0x00080d9a
 */
/* Reconstructed FUN_00080d9a @ 0x80d9a  (parity: 300/300 trials, PROVEN) */

int bt_uuid_create(unsigned char *param_1, unsigned int *param_2, int param_3)
{
    if (param_3 == 4) {
        param_1[0] = 1;
        *(unsigned int*)(param_1+4) = *param_2;
    } else if (param_3 == 0x10) {
        unsigned int *puVar1, *puVar2, *puVar3;
        param_1[0] = 2;
        puVar1 = (unsigned int*)(param_1+1);
        puVar2 = param_2;
        do {
            puVar3 = puVar2+1;
            *puVar1 = *puVar2;
            puVar1++; puVar2 = puVar3;
        } while (puVar2 != param_2+4);
    } else {
        if (param_3 != 2) return 0;
        param_1[0]=0;
        *(unsigned short*)(param_1+2) = *(unsigned short*)param_2;
    }
    return 1;
}
