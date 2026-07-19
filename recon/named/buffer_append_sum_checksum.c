/* readable reconstruction; identity: FUN_0007d16a @ 0x0007d16a
 * public-name: buffer_append_sum_checksum
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   buffer_append_sum_checksum               <= FUN_0007d16a @ 0x0007d16a
 */
/* Reconstructed FUN_0007d16a @ 0x7d16a  (parity: 300/300 trials, PROVEN) */

int buffer_append_sum_checksum(int *param_1, unsigned char *param_2)
{
    if (param_1 == 0 || param_2 == 0) {
        return -1;
    }
    char cVar2 = 0;
    unsigned char bVar1 = *param_2;
    int iVar4;
    for (iVar4 = 0; iVar4 < (int)(unsigned int)bVar1; iVar4++) {
        cVar2 = cVar2 + *(char*)(*param_1 + iVar4);
    }
    *(char*)(*param_1 + (unsigned int)bVar1) = cVar2;
    *param_2 = bVar1 + 1;
    return 0;
}
