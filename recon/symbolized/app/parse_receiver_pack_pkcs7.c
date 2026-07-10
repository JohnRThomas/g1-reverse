#include "g1_app_symbols.h"
/* named: parse_receiver_pack_pkcs7 */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed parse_receiver_pack_pkcs7 @ 0x19cd0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void debug_print(uint32_t, ...);
extern void memcpy(int, ...);

unsigned int parse_receiver_pack_pkcs7(int param_1, unsigned char *param_2, unsigned int param_3)
{
    unsigned char bVar1, bVar2;
    unsigned short uVar3;
    unsigned char *pbVar4 = (unsigned char*)((uintptr_t)&g_pkcs7_pack_cmd_id) /*=0x20010320*/;
    unsigned short *puVar5 = (unsigned short*)((uintptr_t)&g_pkcs7_pack_offset) /*=0x2000d6f4*/;
    unsigned int uVar6;
    unsigned int uVar7;
    int iVar8;
    unsigned int uVar9;

    if (param_2 == (unsigned char*)0) {
        uVar7 = 0xb0;
        iVar8 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar6 = "[%s-%d]error, req is NULL ! \n" /*=0x9b371*/;
    } else {
        if (param_1 != 0) {
            if (param_3 < 3) {
                if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
                    debug_print("[%s-%d]error, req_len is %d, too short ! \n" /*=0x9b3b5*/, "parse_receiver_pack_pkcs7" /*=0x9e0d0*/, 0xbbUL, param_3);
                    return 0xca;
                }
                DEBUG_PRINT("[%s-%d]error, req_len is %d, too short ! \n" /*=0x9b3b5*/, "parse_receiver_pack_pkcs7" /*=0x9e0d0*/, 0xbbUL, param_3);
                return 0xca;
            }
            bVar1 = param_2[2];
            uVar9 = (unsigned int)*param_2;
            bVar2 = param_2[1];
            if (bVar1 == 0) {
                *pbVar4 = *param_2;
                *puVar5 = (unsigned short)bVar1;
            }
            if (*pbVar4 != uVar9) {
                if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
                    debug_print("[%s-%d]error, curCmd is %d, but parseCmd is %d ! \n" /*=0x9b3e0*/, "parse_receiver_pack_pkcs7" /*=0x9e0d0*/);
                    return 0xca;
                }
                DEBUG_PRINT("[%s-%d]error, curCmd is %d, but parseCmd is %d ! \n" /*=0x9b3e0*/, "parse_receiver_pack_pkcs7" /*=0x9e0d0*/, 0xd0UL, uVar9, (unsigned int)*pbVar4);
                return 0xca;
            }
            uVar3 = *puVar5;
            memcpy(param_1 + (unsigned int)uVar3, param_2 + 3, param_3 - 3, uVar9, param_1, param_2);
            if ((unsigned int)bVar1 == (unsigned int)(bVar2 - 1)) {
                uVar6 = 0xc9;
            } else {
                uVar6 = 0xcb;
            }
            *puVar5 = (unsigned short)((int)param_3 + (uVar3 - 3));
            return uVar6;
        }
        uVar7 = 0xb5;
        iVar8 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        uVar6 = "[%s-%d]error, origin_data is NULL ! \n" /*=0x9b38f*/;
    }
    if (iVar8 == 0) {
        DEBUG_PRINT(uVar6, "parse_receiver_pack_pkcs7" /*=0x9e0d0*/, uVar7);
    } else {
        debug_print(uVar6, "parse_receiver_pack_pkcs7" /*=0x9e0d0*/, uVar7);
    }
    return 0xca;
}

