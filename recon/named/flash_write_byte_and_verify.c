/* named: flash_write_byte_and_verify */
/* Reconstructed flash_write_byte_and_verify @ 0x84db2  (parity: 300/300 trials, PROVEN) */

extern int flash_area_read(int a, int b, char *c, int d, int e);
extern int flash_region_is_erased(int a, char *b, int c);

unsigned int flash_write_byte_and_verify(int param_1, char *param_2, int param_3, int param_4)
{
    int iVar1;
    unsigned int uVar2;
    char cVar3;

    iVar1 = flash_area_read(param_1, param_3, param_2, 1, param_4);
    if (iVar1 < 0) {
        uVar2 = 1;
    } else {
        iVar1 = flash_region_is_erased(param_1, param_2, 1);
        if (iVar1 == 0) {
            if (*param_2 == 1) {
                cVar3 = 1;
            } else {
                cVar3 = 2;
            }
        } else {
            cVar3 = 3;
        }
        uVar2 = 0;
        *param_2 = cVar3;
    }
    return uVar2;
}

