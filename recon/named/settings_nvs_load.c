/* readable reconstruction; identity: FUN_0004e780 @ 0x0004e780
 * public-name: settings_nvs_load
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nvs_write                                <= FUN_0004c8f8 @ 0x0004c8f8
 *   settings_call_set_handler                <= FUN_0004e604 @ 0x0004e604
 *   settings_nvs_load                        <= FUN_0004e780 @ 0x0004e780
 *   settings_nvs_delete_id                   <= FUN_0007e9d4 @ 0x0007e9d4
 *   settings_nvs_read_latest                 <= FUN_0007e9dc @ 0x0007e9dc
 * address symbols (name @ address):
 *   ADDR_settings_nvs_read_fn_THUMB          @ 0x0007f211
 */
/* Reconstructed FUN_0004e780 @ 0x4e780  (parity: 100/100 trials, PROVEN) */
#include <stdint.h>
extern int settings_nvs_read_latest(int,int,void*,int);
extern void settings_nvs_delete_id(int,int);
extern void nvs_write(int,int,void*,int);
extern int settings_call_set_handler(void*,int,unsigned,void*,unsigned);

int settings_nvs_load(int param_1, unsigned param_2){
    int iVar7 = param_1 + 8;
    struct {
        unsigned char reserved[11];
        unsigned char marker;
        int owner;
        short key;
        unsigned char alignment[2];
        unsigned char data[76];
    } frame;
    unsigned short r4v = (unsigned short)(*(unsigned short*)(param_1+0x38) + 1);
    int iVar2, iVar3;
    unsigned short sVar4, sVar6, sVar5;
  LOOP:
    sVar4 = r4v;
    sVar6 = (unsigned short)(sVar4 - 1);
    if (sVar6 == 0x8000) return 0;
    iVar2 = settings_nvs_read_latest(iVar7, sVar6, frame.data, 0x4a);
    sVar5 = (unsigned short)(sVar4 + 0x3fff);
    iVar3 = settings_nvs_read_latest(iVar7, sVar5, &frame.marker, 1);
    if (iVar2 > 0){
        if (iVar3 > 0) goto L806;
        goto L7d8;
    }
    if (iVar3 > 0) goto L7d8;
    r4v = sVar6;
    goto LOOP;
  L7d8:
    if (*(unsigned short*)(param_1+0x38) == sVar6){
        *(unsigned short*)(param_1+0x38) = (unsigned short)(sVar4 - 2);
        nvs_write(iVar7, 0x8000, (void*)(param_1+0x38), 2);
    }
    settings_nvs_delete_id(iVar7, sVar6);
    settings_nvs_delete_id(iVar7, sVar5);
    r4v = sVar6;
    goto LOOP;
  L806:
    frame.data[iVar2] = 0;
    frame.owner = iVar7;
    frame.key = (short)sVar5;
    iVar2 = settings_call_set_handler(frame.data, iVar3, 0x0007f211,
                         &frame.owner, param_2);
    if (iVar2 != 0) return iVar2;
    r4v = sVar6;
    goto LOOP;
}
