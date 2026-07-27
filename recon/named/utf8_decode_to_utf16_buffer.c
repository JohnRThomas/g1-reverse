/* readable reconstruction; identity: FUN_00047844 @ 0x00047844
 * public-name: utf8_decode_to_utf16_buffer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   utf8_to_unicode                          <= FUN_000477a0 @ 0x000477a0
 *   utf8_decode_to_utf16_buffer              <= FUN_00047844 @ 0x00047844
 *   printf                                   <= FUN_000777f0 @ 0x000777f0
 * address symbols (name @ address):
 *   rodata_d74d7                             @ 0x000d74d7
 */
/* Reconstructed FUN_00047844 @ 0x47844  (parity: 300/300 trials, PROVEN) */

extern unsigned int utf8_to_unicode(unsigned char *, int);
extern int printf(const char *, ...);
int utf8_decode_to_utf16_buffer(int param_1, int param_2, int param_3, int param_4){
    int iVar2 = 0, iVar3 = 0;
    for(;;){
        if (param_2 <= iVar2){
            *(volatile short*)(param_3 + iVar3*2) = 0;
            return iVar3;
        }
        unsigned uVar1 = *(volatile unsigned char*)(param_1 + iVar2);
        if (uVar1 == 0){
            *(volatile short*)(param_3 + iVar3*2) = 0;
            return iVar3;
        }
        if (uVar1 == 0xd || uVar1 == 10 || (uVar1 - 0x20) < 0x60){
            iVar2 = iVar2 + 1;
            goto store;
        }
        if ((uVar1 & 0xf0) == 0xe0){
            uVar1 = (unsigned)utf8_to_unicode(param_1 + iVar2, 3);
            iVar2 = iVar2 + 3;
            goto store;
        }
        if ((uVar1 & 0xe0) == 0xc0){
            uVar1 = (unsigned)utf8_to_unicode(param_1 + iVar2, 2);
            iVar2 = iVar2 + 2;
            goto store;
        }
        iVar2 = iVar2 + 1;
        continue;
    store:
        *(volatile short*)(param_3 + iVar3*2) = (short)uVar1;
        if (param_4 - 1 == iVar3){
            printf(0x000d74d7, iVar3);
            *(volatile short*)(param_3 + iVar3*2) = 0;
            return iVar3;
        }
        iVar3 = iVar3 + 1;
    }
}
