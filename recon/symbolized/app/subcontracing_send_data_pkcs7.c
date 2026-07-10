#include "g1_app_symbols.h"
/* named: subcontracing_send_data_pkcs7 */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed subcontracing_send_data_pkcs7 @ 0x21a40  (parity: 252/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern void debug_print_hex_dump(void);
extern void FUN_00086c1e(void);
extern void memset_bytes(void);

unsigned subcontracing_send_data_pkcs7(int param_1, int param_2, unsigned char param_3, void *param_4)
{
    volatile int *piVar1 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    volatile int *flag = (volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    volatile int local_3c[16];
    int uVar9 = param_2 / 0x11;
    int iVar8 = uVar9 + 1;
    int iVar10 = param_2 % 0x11;
    int iVar11, iVar13, iVar12;
    int iVar10b;

    memset_bytes();

    if (2 < *piVar1) {
        if (*flag == 0) DEBUG_PRINT();
        else debug_print();
    }
    iVar13 = 0;
    while (1) {
        iVar11 = *piVar1;
        iVar12 = iVar13 + 1;
        if (uVar9 <= iVar13) break;
        {
            volatile int *puVar6 = (volatile int*)(iVar13 * 0x11 + param_1);
            volatile int *puVar2 = &local_3c[1];
            volatile int *puVar7, *puVar3;
            do {
                puVar7 = puVar6 + 1;
                puVar3 = puVar2 + 1;
                *puVar2 = *puVar6;
                puVar2 = puVar3;
                puVar6 = puVar7;
            } while (puVar7 != (volatile int*)(iVar13 * 0x11 + param_1) + 4);
            *(volatile uint8_t*)puVar3 = *(volatile uint8_t*)puVar7;
        }
        if (2 < iVar11) {
            if (*flag == 0) DEBUG_PRINT();
            else debug_print();
        }
        debug_print_hex_dump();
        ((void(*)(void*))(intptr_t)param_4)((void*)local_3c);
        iVar13 = iVar12;
    }
    (void)iVar8; (void)iVar12;

    if (iVar10 == 0) {
        memset_bytes();
        if (iVar11 < 3) goto LAB_b5a;
        iVar10b = *flag;
    } else {
        memset_bytes();
        FUN_00086c1e();
        if (iVar11 < 3) goto LAB_b5a;
        iVar10b = *flag;
    }
    if (iVar10b == 0) DEBUG_PRINT();
    else debug_print();
LAB_b5a:
    debug_print_hex_dump();
    if (2 < *piVar1) {
        if (*flag == 0) DEBUG_PRINT();
        else debug_print();
    }
    ((void(*)(void*))(intptr_t)param_4)((void*)local_3c);
    return 0;
}

