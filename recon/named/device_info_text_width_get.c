/* readable reconstruction; identity: FUN_0007d3ee @ 0x0007d3ee
 * public-name: device_info_text_width_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 */
/* Reconstructed FUN_0007d3ee @ 0x7d3ee  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
int device_info_text_width_get(void){
    int iVar2;
    unsigned short uVar1;
    iVar2 = get_device_info();
    if (*(unsigned short*)(iVar2 + 0x1072) == 0) goto L_426;
L_3fe:
    iVar2 = get_device_info();
    if (*(unsigned short*)(iVar2 + 0x1072) > 0x40) goto L_436;
    goto L_40e;
L_426:
    iVar2 = get_device_info();
    if (*(unsigned short*)(iVar2 + 0x1074) != 0) goto L_3fe;
L_436:
    iVar2 = get_device_info();
    *(unsigned short*)(iVar2 + 0x1072) = 0x20;
L_40e:
    iVar2 = get_device_info();
    uVar1 = *(unsigned short*)(iVar2 + 0x1072);
    iVar2 = get_device_info();
    return *(int*)(iVar2 + 0xec4) + (unsigned int)uVar1;
}
