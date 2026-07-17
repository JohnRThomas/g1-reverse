#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00016110 @ 0x00016110
 * public-name: FUN_00016110
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_ctrl_read1                           <= FUN_00083dba @ 0x00083dba
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 * address symbols (name @ address):
 *   rodata_9951c                             @ 0x0009951c
 *   rodata_99528                             @ 0x00099528
 *   rodata_99534                             @ 0x00099534
 *   rodata_99540                             @ 0x00099540
 *   rodata_9954c                             @ 0x0009954c
 *   rodata_99558                             @ 0x00099558
 *   rodata_99564                             @ 0x00099564
 *   rodata_99570                             @ 0x00099570
 */
/* Reconstructed FUN_00016110 @ 0x16110  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int, ...);
extern int dev_ctrl_read1(int,int,int,int);
extern int dev_write_reg3(int, ...);

int FUN_00016110(int param_1, unsigned int param_2, int param_3)
{
    int iVar1;
    unsigned int uStack_14;
    unsigned int uStack_10;

    iVar1 = *(volatile int *)(0x00087ce0 + 4);
    uStack_14 = param_2;
    uStack_10 = param_3;
    *((unsigned char *)&uStack_14 + 3) = 0;
    (void)uStack_10;
    dev_write_reg3(*(int *)(iVar1 + 0x1c), 3, 0x10, 0xeb, param_1);
    dev_write_reg3(*(int *)(iVar1 + 0x1c), 3, 0x11, 1);
    dev_write_reg3(*(int *)(iVar1 + 0x1c), 3, 0x12, 0xad);
    dev_write_reg3(*(int *)(iVar1 + 0x1c), 3, 0x13, 1);
    dev_write_reg3(*(int *)(iVar1 + 0x1c), 3, 0x14, 0x3f);
    dev_write_reg3(*(int *)(iVar1 + 0x1c), 3, 0x15, 3);
    dev_write_reg3(*(int *)(iVar1 + 0x1c), 3, 0x16, 0x2e);
    dev_write_reg3(*(int *)(iVar1 + 0x1c), 3, 0x17, 2);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x10, (int)&uStack_14 + 3);
    DEBUG_PRINT(((unsigned long)&rodata_9951c) /*=0x9951c*/, uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x11, (int)&uStack_14 + 3);
    DEBUG_PRINT(((unsigned long)&rodata_99528) /*=0x99528*/, uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x12, (int)&uStack_14 + 3);
    DEBUG_PRINT(((unsigned long)&rodata_99534) /*=0x99534*/, uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x13, (int)&uStack_14 + 3);
    DEBUG_PRINT(((unsigned long)&rodata_99540) /*=0x99540*/, uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x14, (int)&uStack_14 + 3);
    DEBUG_PRINT(((unsigned long)&rodata_9954c) /*=0x9954c*/, uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x15, (int)&uStack_14 + 3);
    DEBUG_PRINT(((unsigned long)&rodata_99558) /*=0x99558*/, uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x16, (int)&uStack_14 + 3);
    DEBUG_PRINT(((unsigned long)&rodata_99564) /*=0x99564*/, uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x17, (int)&uStack_14 + 3);
    DEBUG_PRINT(((unsigned long)&rodata_99570) /*=0x99570*/, uStack_14 >> 0x18);
    return 0;
}
