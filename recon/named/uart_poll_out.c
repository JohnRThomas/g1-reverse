/* readable reconstruction; identity: FUN_00062f28 @ 0x00062f28
 * public-name: uart_poll_out
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   uart_poll_out                            <= FUN_00062f28 @ 0x00062f28
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   audio_dma_start_transfer                 <= FUN_0008496c @ 0x0008496c
 *   is_tx_ready                              <= FUN_00084abe @ 0x00084abe
 *   k_is_in_isr                              <= FUN_00086406 @ 0x00086406
 * address symbols (name @ address):
 *   g_tx_yield_allowed_flag                  @ 0x2001d564
 */
/* Reconstructed FUN_00062f28 @ 0x62f28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int k_sleep(int,int);
extern void audio_dma_start_transfer(int,int,int);
extern unsigned long long is_tx_ready(int,...);
extern int k_is_in_isr(void);
extern void thunk_FUN_00086384(int);

void uart_poll_out(int param_1, unsigned char param_2){
    int iVar6 = *(int*)(param_1+0x10);
    int *piVar7 = 0;
    int iVar3 = k_is_in_isr();
    if (iVar3 != 0 || *(char*)0x2001d564 == 0){
        while (1){
            piVar7 = *(int**)(param_1+4);
            unsigned long long uVar8 = is_tx_ready((int)(intptr_t)piVar7, 0);
            if ((int)uVar8 != 0) break;
        }
        iVar3 = *(int*)(iVar6+0xc);
        if (iVar3 != 0 && *(int*)(iVar3+0xc) != 0 && *(int*)(iVar3+0xbc) < 0){
            *(int*)(iVar3+0xbc) = *(int*)(*piVar7+0x54c);
        }
        goto LAB;
    }
    do {
        int cnt = 100;
        do {
            int iVar4 = (int)is_tx_ready(*(int*)(param_1+4));
            if (iVar4 != 0){
                unsigned long long uVar8 = is_tx_ready(*(int*)(param_1+4), 0);
                if ((int)uVar8 != 0) goto LAB;
                break;
            }
            thunk_FUN_00086384(1);
            cnt = cnt - 1;
        } while (cnt != 0);
        k_sleep(0x21, 0);
    } while (1);
  LAB:
    *(*(unsigned char**)(iVar6+0x14)) = param_2;
    audio_dma_start_transfer(param_1, *(int*)(iVar6+0x14), 1);
}
