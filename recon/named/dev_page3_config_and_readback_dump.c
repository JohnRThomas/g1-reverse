/* readable reconstruction; identity: FUN_00016110 @ 0x00016110
 * public-name: dev_page3_config_and_readback_dump
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_page3_config_and_readback_dump       <= FUN_00016110 @ 0x00016110
 *   dev_ctrl_read1                           <= FUN_00083dba @ 0x00083dba
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 * address symbols (name @ address):
 *   rodata_9951c                             @ 0x0009951c   [INLINED -- G6 literal batch]
 *   rodata_99528                             @ 0x00099528   [INLINED -- G6 literal batch]
 *   rodata_99534                             @ 0x00099534   [INLINED -- G6 literal batch]
 *   rodata_99540                             @ 0x00099540   [INLINED -- G6 literal batch]
 *   rodata_9954c                             @ 0x0009954c   [INLINED -- G6 literal batch]
 *   rodata_99558                             @ 0x00099558   [INLINED -- G6 literal batch]
 *   rodata_99564                             @ 0x00099564   [INLINED -- G6 literal batch]
 *   rodata_99570                             @ 0x00099570   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_00016110 @ 0x16110  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
extern int dev_ctrl_read1(int,int,int,int);
extern int dev_write_reg3(int, ...);

int dev_page3_config_and_readback_dump(int param_1, unsigned int param_2, int param_3)
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
    log_message(((unsigned long)"0x10 is %x\n"), uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x11, (int)&uStack_14 + 3);
    log_message(((unsigned long)"0x11 is %x\n"), uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x12, (int)&uStack_14 + 3);
    log_message(((unsigned long)"0x12 is %x\n"), uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x13, (int)&uStack_14 + 3);
    log_message(((unsigned long)"0x13 is %x\n"), uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x14, (int)&uStack_14 + 3);
    log_message(((unsigned long)"0x14 is %x\n"), uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x15, (int)&uStack_14 + 3);
    log_message(((unsigned long)"0x15 is %x\n"), uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x16, (int)&uStack_14 + 3);
    log_message(((unsigned long)"0x16 is %x\n"), uStack_14 >> 0x18);
    dev_ctrl_read1(*(int *)(iVar1 + 0x1c), 3, 0x17, (int)&uStack_14 + 3);
    log_message(((unsigned long)"0x17 is %x\n"), uStack_14 >> 0x18);
    return 0;
}
