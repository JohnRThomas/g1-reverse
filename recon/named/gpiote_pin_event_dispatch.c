/* readable reconstruction; identity: FUN_000654c4 @ 0x000654c4
 * public-name: gpiote_pin_event_dispatch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_pin_idx                              <= FUN_00065434 @ 0x00065434
 *   gpiote_pin_event_dispatch                <= FUN_000654c4 @ 0x000654c4
 * address symbols (name @ address):
 *   g_gpiote_cb                              @ 0x20002bc0
 */
/* Reconstructed FUN_000654c4 @ 0x654c4  (parity: 300/300 trials, PROVEN) */

extern unsigned long long get_pin_idx(unsigned long);

void gpiote_pin_event_dispatch(unsigned int param_1)
{
    int iVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    void (*UNRECOVERED_JUMPTABLE)(unsigned int, unsigned int, unsigned int);
    unsigned long long uVar4;

    uVar4 = get_pin_idx(param_1);
    iVar1 = 0x20002bc0;
    uVar2 = (unsigned int)(uVar4 >> 0x20);
    uVar3 = (unsigned int)*(volatile unsigned short *)(0x20002bc0UL + ((int)uVar4 + 8) * 2);
    if ((int)(uVar3 << 0x17) < 0) {
        uVar3 = (uVar3 << 0x13) >> 0x1c;
        (*(void (**)(unsigned int, unsigned int, unsigned int))(0x20002bc0UL + uVar3 * 8))
            (param_1, uVar2, *(volatile unsigned int *)(0x20002bc0UL + uVar3 * 8 + 4));
    }
    UNRECOVERED_JUMPTABLE = *(void (**)(unsigned int, unsigned int, unsigned int))(iVar1 + 8);
    if (UNRECOVERED_JUMPTABLE != 0) {
        (*UNRECOVERED_JUMPTABLE)(param_1, uVar2, *(volatile unsigned int *)(iVar1 + 0xc));
        return;
    }
    return;
}
