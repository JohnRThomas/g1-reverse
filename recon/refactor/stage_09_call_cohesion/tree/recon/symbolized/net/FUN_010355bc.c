#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010355bc @ 0x010355bc
 * public-name: FUN_010355bc
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   virtqueue_add_consumed_buffer            <= FUN_010353ec @ 0x010353ec
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 *   metal_io_block_write                     <= FUN_0103ab0e @ 0x0103ab0e
 *   thunk_FUN_01036824                       <= FUN_0103aec2 @ 0x0103aec2
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e889                           @ 0x0103e889
 */
/* net-core FUN_010355bc @ 0x10355bc  (parity 300 trials PROVEN) */

extern int virtqueue_add_consumed_buffer(unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int);
extern int metal_io_block_write(void *, unsigned int, void *, unsigned int);
extern unsigned int FUN_0103ac46(unsigned int, unsigned int);
extern void FUN_0103acca(unsigned int);
extern void FUN_0103aec6(void *);
extern void thunk_FUN_01036824(void *);

unsigned int FUN_010355bc(int param_1, unsigned int param_2, unsigned int param_3, int param_4, unsigned int param_5)
{
    unsigned int uVar5 = *(volatile unsigned int *)(param_4 - 8);
    volatile int *piVar1 = *(volatile int **)(param_1 + 0xac);
    struct {
        unsigned int first;
        unsigned int second;
        unsigned int reserved;
        unsigned short result;
        unsigned short padding;
    } local_buf;
    unsigned int uVar4;
    unsigned int panic_code;
    int iVar2b;

    unsigned int uVar3 = (unsigned int)(param_4 - 0x10) - piVar1[0];
    if ((unsigned int)piVar1[2] <= uVar3) {
        uVar3 = 0xffffffff;
    }

    local_buf.first = param_2;
    local_buf.second = param_3;
    local_buf.reserved = 0;
    local_buf.result = (unsigned short)param_5;
    local_buf.padding = 0;
    int iVar2 = metal_io_block_write((void *)piVar1, uVar3, &local_buf, 0x10);
    uVar5 = uVar5 & 0xffff;

    if (iVar2 == 0x10) goto L_612;

    assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103e889) /*=0x103e889*/, 0x1af);
    panic_code = 0x1af;
    goto L_term;

L_term:
    assert_post_action(((unsigned long)&rodata_103e889) /*=0x103e889*/, panic_code);
    /* falls through to success-path code physically */

L_612:
    FUN_0103aec6((void *)(param_1 + 0x58));
    uVar4 = FUN_0103ac46(*(volatile unsigned int *)(param_1 + 0xa8), uVar5);
    if (*(volatile int *)(*(volatile int *)(param_1 + 0xa0) + 0x18) != 1) {
        goto L_success;
    }
    iVar2b = virtqueue_add_consumed_buffer(*(volatile unsigned int *)(param_1 + 0xa8), uVar5, uVar4);
    if (iVar2b == 0) goto L_success;

    assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103e889) /*=0x103e889*/, 0x1bc);
    panic_code = 0x1bc;
    goto L_term;

L_success:
    FUN_0103acca(*(volatile unsigned int *)(param_1 + 0xa8));
    thunk_FUN_01036824((void *)(param_1 + 0x58));
    return param_5;
}
