#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000513e8 @ 0x000513e8
 * public-name: smp_process_request_packet
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mgmt_find_handler                        <= FUN_00051354 @ 0x00051354
 *   mgmt_find_error_translation_function     <= FUN_0005139c @ 0x0005139c
 *   smp_process_request_packet               <= FUN_000513e8 @ 0x000513e8
 *   net_buf_simple_pull_5f558                <= FUN_0005f558 @ 0x0005f558
 *   smp_make_rsp_hdr                         <= FUN_000807f6 @ 0x000807f6
 *   cbor_nb_writer_init                      <= FUN_00080830 @ 0x00080830
 *   smp_write_hdr                            <= FUN_00080864 @ 0x00080864
 *   smp_alloc_rsp                            <= FUN_00080ae6 @ 0x00080ae6
 *   smp_free_buf                             <= FUN_00080b0e @ 0x00080b0e
 *   cbor_encode_int32                        <= FUN_0008630c @ 0x0008630c
 *   cbor_encode_bstr                         <= FUN_0008633e @ 0x0008633e
 *   cbor_encode_map_indef_start              <= FUN_0008634c @ 0x0008634c
 *   thunk_FUN_00086354                       <= FUN_0008635c @ 0x0008635c
 * address symbols (name @ address):
 *   rodata_f2558                             @ 0x000f2558
 */
/* Reconstructed FUN_000513e8 @ 0x513e8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
typedef unsigned (*codef)(void *);
extern int mgmt_find_handler(uint a, unsigned char b);
extern uintptr_t mgmt_find_error_translation_function(short a);
extern void net_buf_simple_pull_5f558(int a, unsigned b);
extern void smp_make_rsp_hdr(void *a, void *b, int c);
extern void cbor_nb_writer_init(int a, int b);
extern void smp_write_hdr(int a);
extern void smp_free_buf(int a, int b);
extern int smp_alloc_rsp(int a, int b);
extern int cbor_encode_int32(int *a, uint b);
extern int cbor_encode_bstr(int *a, void *b);
extern int cbor_encode_map_indef_start(int *a, int b);
extern void FUN_000861aa(int *a, int b, unsigned c, unsigned short d, int e);
extern int thunk_FUN_00086354(int *a, int b);

uint smp_process_request_packet(int *param_1, int param_2)
{
    unsigned short pending;
    unsigned short uVar2;
    uint uVar3, uVar10, uVar11;
    int iVar4, iVar8, iVar9;
    unsigned uVar5;
    int *piVar6, *piVar13;
    unsigned *puVar7;
    codef pcVar12;
    unsigned local_38, local_34w;
    struct command_error_record {
        uint32_t message;
        uint32_t status;
    } error_record;

    do {
        uVar11 = (uint)*(volatile unsigned short *)(param_2 + 0x10);
        if (uVar11 == 0) {
LAB_000513fa:
            smp_free_buf(param_2, *param_1);
            iVar4 = 0;
            iVar9 = *param_1;
LAB_00051506:
            smp_free_buf(iVar4, iVar9);
            return uVar11;
        }
        if (uVar11 < 8) {
            uVar11 = 9;
            goto LAB_000513fa;
        }
        uVar5 = **(volatile unsigned **)(param_2 + 0xc);
        uVar11 = (*(volatile unsigned **)(param_2 + 0xc))[1];
        {
            unsigned short hi = (unsigned short)((uint)uVar5 >> 0x10);
            uVar2 = (unsigned short)(((hi & 0xff) << 8) | (hi >> 8));
            local_38 = (uVar2 << 0x10) | (uVar5 & 0xffff);
            uVar10 = (uVar11 & 0xff) << 8 | uVar11 >> 8 & 0xff;
            local_34w = ((uVar11 >> 0x10) << 0x10) | (uVar10 & 0xffff);
        }
        net_buf_simple_pull_5f558(param_2 + 0xc, 8);
        uVar3 = local_38;
        if (*(volatile unsigned short *)(param_2 + 0x10) < uVar2) {
            uVar11 = 9;
LAB_000515f8:
            iVar9 = 0;
            iVar4 = param_2;
LAB_000514b2:
            cbor_nb_writer_init(param_1[2], iVar4);
            piVar13 = (int *)param_1[2];
            piVar6 = piVar13 + 1;
            iVar8 = cbor_encode_map_indef_start(piVar6, 2);
            if (iVar8 == 0) {
LAB_000514f4:
                thunk_FUN_00086354(piVar6, 2);
            } else {
                error_record.message = ((unsigned long)&rodata_f2558) /*=0xf2558*/;
                error_record.status = 2;
                iVar8 = cbor_encode_bstr(piVar6, &error_record);
                if ((iVar8 == 0) || (iVar8 = cbor_encode_int32(piVar6, uVar11), iVar8 == 0)) goto LAB_000514f4;
                iVar8 = thunk_FUN_00086354(piVar6, 2);
                if (iVar8 != 0) {
                    smp_make_rsp_hdr(&local_38, &error_record,
                                 (piVar13[1] - *(volatile int *)(*piVar13 + 0xc)) + -8);
                    *(volatile short *)(*piVar13 + 0x10) = (short)piVar13[1] - (short)*(volatile int *)(*piVar13 + 0xc);
                    smp_write_hdr(param_1[2]);
                    pcVar12 = *(codef *)(uintptr_t)(*param_1 + 0x2c);
                    (*pcVar12)((void *)(uintptr_t)iVar4);
                    iVar4 = 0;
                }
            }
            smp_free_buf(iVar9, *param_1);
            iVar9 = *param_1;
            goto LAB_00051506;
        }
        uVar11 = local_38 & 5;
        if ((local_38 & 5) != 0) {
            uVar11 = 8;
            goto LAB_000515f8;
        }
        iVar4 = smp_alloc_rsp(param_2, *param_1);
        if (iVar4 == 0) {
            uVar11 = 2;
            goto LAB_000515f8;
        }
        piVar6 = (int *)param_1[1];
        *piVar6 = param_2;
        FUN_000861aa(piVar6 + 1, 4, *(volatile unsigned *)(param_2 + 0xc),
                     *(volatile unsigned short *)(param_2 + 0x10), 1);
        cbor_nb_writer_init(param_1[2], iVar4);
        piVar6 = (int *)param_1[2];
        piVar6[0xd] = uVar11;
        iVar9 = param_2;
        if (1 < (int)((local_38 << 0x1b) >> 0x1e)) {
            uVar11 = 0xd;
            goto LAB_000514b2;
        }
        puVar7 = (unsigned *)mgmt_find_handler(uVar10, (unsigned char)(local_34w >> 0x18));
        if (puVar7 == (unsigned *)0x0) {
LAB_000515aa:
            uVar11 = 8;
            goto LAB_000514b2;
        }
        if ((local_38 & 7) == 0) {
            pcVar12 = (codef)(uintptr_t)*puVar7;
        } else {
            if ((local_38 & 7) != 2) {
                uVar11 = 3;
                goto LAB_000514b2;
            }
            pcVar12 = (codef)(uintptr_t)puVar7[1];
        }
        if (pcVar12 == (codef)0x0) goto LAB_000515aa;
        iVar8 = cbor_encode_map_indef_start((int *)(param_1[2] + 4), 0xf);
        if (iVar8 == 0) {
            uVar11 = 7;
            goto LAB_000514b2;
        }
        uVar11 = (*pcVar12)(param_1);
        iVar8 = thunk_FUN_00086354((int *)(param_1[2] + 4), 0xf);
        if (iVar8 == 0) {
            if (uVar11 == 0) uVar11 = 7;
            goto LAB_000514b2;
        }
        if (uVar11 != 0) goto LAB_000514b2;
        pending = *(volatile unsigned short *)((int)piVar6 + 0x36);
        if ((pending != 0) && ((uVar3 & 0x18) == 0)) {
            pcVar12 = (codef)mgmt_find_error_translation_function((short)piVar6[0xd]);
            if (pcVar12 == (codef)0x0) {
                uVar11 = 1;
            } else {
                uVar11 = (*pcVar12)((void *)(uintptr_t)pending);
                if (uVar11 == 0) goto LAB_00051594;
                if (iVar4 == 0) goto LAB_000515f8;
            }
            goto LAB_000514b2;
        }
        smp_make_rsp_hdr(&local_38, &error_record,
                     (piVar6[1] - *(volatile int *)(*piVar6 + 0xc)) + -8);
        *(volatile short *)(*piVar6 + 0x10) = (short)piVar6[1] - (short)*(volatile int *)(*piVar6 + 0xc);
        smp_write_hdr(param_1[2]);
LAB_00051594:
        pcVar12 = *(codef *)(uintptr_t)(*param_1 + 0x2c);
        uVar11 = (*pcVar12)((void *)(uintptr_t)iVar4);
        if (uVar11 != 0) goto LAB_000515f8;
        net_buf_simple_pull_5f558(param_2 + 0xc, uVar2);
    } while (1);
}
