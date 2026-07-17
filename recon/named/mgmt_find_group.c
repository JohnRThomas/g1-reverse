/* readable reconstruction; identity: FUN_0005139c @ 0x0005139c
 * public-name: mgmt_find_group
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mgmt_find_group                          <= FUN_0005139c @ 0x0005139c
 * address symbols (name @ address):
 *   g_mgmt_group_list_head                   @ 0x2000a94c
 */
/* Reconstructed FUN_0005139c @ 0x5139c  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint;
uint mgmt_find_group(uint param_1)
{
    unsigned int *puVar2 = *(volatile unsigned int**)0x2000a94cUL;
    unsigned int *puVar1 = puVar2;
    if (puVar2 != 0) puVar1 = (unsigned int*)*puVar2;
    while (1) {
        if (puVar2 == 0) return 0;
        if (*(volatile unsigned short*)((char*)puVar2 + 10) == param_1) break;
        puVar2 = puVar1;
        if (puVar1 != 0) puVar1 = (unsigned int*)*puVar1;
    }
    return puVar2[3];
}
