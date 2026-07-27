/* readable reconstruction; identity: FUN_00033d58 @ 0x00033d58
 * public-name: clear_timeout_message
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   msg_content_recalc_unread                <= FUN_00033cf8 @ 0x00033cf8
 *   clear_timeout_message                    <= FUN_00033d58 @ 0x00033d58
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a7d87                             @ 0x000a7d87   [INLINED -- G6 literal batch]
 *   rodata_a8265                             @ 0x000a8265   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_message_pool                           @ 0x20007dac
 *   g_msg_queue_busy                         @ 0x20018d8e
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_00033d58 @ 0x33d58  (parity: 300/300 trials, PROVEN) */
extern int get_device_info(int,...);
extern int msg_content_recalc_unread(int,...);
extern unsigned get_timestamp(int,...);
extern void memcpy(int, int, int);
extern void memset_bytes(void*, int, int);

void clear_timeout_message(int param_1)
{
    int iVar2 = 0x20007dac;
    int iVar5, iVar7, iVar8, iVar9, iVar10, iVar11;
    unsigned uVar6;
    unsigned char uVar4;
    int local_2c;

    iVar10 = 0; iVar11 = 0; iVar9 = 0;
    *(volatile unsigned char *)0x20018d8eUL = 1;
LAB_00033d76:
    iVar5 = *(volatile int *)(iVar2 + iVar9 * 0x1b4);
    iVar7 = iVar2 + iVar9 * 0x1b4;
    iVar8 = *(volatile int *)(iVar7 + 4);
    if (iVar5 == 0) {
        if (iVar10 == 0) goto LAB_00033dc2;
        if (iVar11 == 0) {
            iVar11 = iVar10;
            if (iVar8 == 0) {
                iVar7 = iVar9 + 1;
                goto joined_00033edc;
            }
            if (*(volatile char *)(iVar7 + 0xf) == 0) goto LAB_00033daa;
LAB_00033de4:
            if (param_1 != 0) goto LAB_00033e20;
LAB_00033de8:
            uVar6 = get_timestamp(0);
            iVar5 = iVar2 + iVar9 * 0x1b4;
            if (uVar6 <= (unsigned)(*(volatile int *)(iVar5 + 4) + 10)) goto LAB_00033daa;
        } else {
            if (*(volatile char *)(iVar7 + 0xf) == 0) {
LAB_00033d92:
                iVar7 = iVar9 + iVar11;
joined_00033edc:
                if (iVar7 < 10) goto LAB_00033e98;
                goto LAB_00033e3e;
            }
            if (param_1 == 0) {
                if (iVar8 == 0) goto LAB_00033d92;
                goto LAB_00033de8;
            }
            if (iVar8 == 0) goto LAB_00033d92;
LAB_00033e20:
            iVar5 = iVar2 + iVar9 * 0x1b4;
        }
        local_2c = iVar9 * 0x1b4;
        iVar11 = iVar11 + 1;
        iVar7 = iVar11 + iVar9;
        memset_bytes(iVar5, 0, 0x1b4);
        if (9 < iVar7) goto LAB_00033e3e;
        if (*(volatile int *)(iVar2 + local_2c) != 0) {
            iVar9 = iVar9 + 1;
            goto LAB_00033d76;
        }
    } else {
        iVar10 = 1;
LAB_00033dc2:
        if (iVar8 == 0) {
            if (iVar11 != 0) {
                iVar7 = iVar9 + iVar11;
                if (9 < iVar7) goto LAB_00033e3e;
                if (iVar5 == 0) goto LAB_00033e98;
LAB_00033e8a:
                iVar9 = iVar9 + 1;
                goto LAB_00033d76;
            }
            goto LAB_00033dc8;
        }
        iVar8 = iVar2 + iVar9 * 0x1b4;
        if (*(volatile char *)(iVar8 + 0xf) != 0) goto LAB_00033de4;
        if ((iVar5 != 0) && (uVar6 = get_timestamp(0), (unsigned)(*(volatile int *)(iVar8 + 4) + 5) < uVar6)) {
            iVar11 = iVar11 + 1;
            iVar7 = iVar11 + iVar9;
            memset_bytes(iVar8, 0, 0x1b4);
            if (iVar7 < 10) {
                if (*(volatile int *)(iVar2 + iVar9 * 0x1b4) != 0) goto LAB_00033e8a;
                goto LAB_00033e98;
            }
            goto LAB_00033e3e;
        }
LAB_00033daa:
        iVar7 = iVar11 + iVar9;
        if (9 < iVar7) goto LAB_00033e3e;
        if ((*(volatile int *)(iVar2 + iVar9 * 0x1b4) != 0) || (iVar11 == 0)) goto LAB_00033dc8;
    }
LAB_00033e98:
    iVar5 = iVar7 * 0x1b4 + iVar2;
    if (*(volatile char *)(iVar5 + 0x10) == 0) {
        iVar11 = iVar11 + 1;
        goto LAB_00033d76;
    }
    memcpy(iVar2 + iVar9 * 0x1b4, iVar5, 0x1b4);
    memset_bytes(iVar5, 0, 0x1b4);
    if (0 < *(volatile int *)0x2000230cUL) {
        if (*(volatile int *)0x20007554UL == 0) {
            log_message(((unsigned long)"%s(): ######clear_timeout_message copy data from %d to  i %d\n"), ((unsigned long)"clear_timeout_message"), iVar7, iVar9);
        } else {
            debug_print(((unsigned long)"%s(): ######clear_timeout_message copy data from %d to  i %d\n"), ((unsigned long)"clear_timeout_message"), iVar7, iVar9);
        }
    }
LAB_00033dc8:
    iVar9 = iVar9 + 1;
    if (iVar9 == 10) {
LAB_00033e3e:
        iVar11 = get_device_info(0);
        uVar4 = (unsigned char)msg_content_recalc_unread(0);
        *(volatile unsigned char *)(iVar11 + 0xdd) = uVar4;
        *(volatile unsigned char *)0x20018d8eUL = 0;
        return;
    }
    goto LAB_00033d76;
}
