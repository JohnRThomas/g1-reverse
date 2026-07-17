/* readable reconstruction; identity: FUN_00069238 @ 0x00069238
 * public-name: lc3_encode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_attdet_run                           <= FUN_000682f0 @ 0x000682f0
 *   lc3_setup_bits                           <= FUN_000684a8 @ 0x000684a8
 *   lc3_flush_bits                           <= FUN_000685f4 @ 0x000685f4
 *   lc3_put_bits_generic                     <= FUN_00068908 @ 0x00068908
 *   lc3_bwdet_run                            <= FUN_00068a10 @ 0x00068a10
 *   lc3_bwdet_put_bw                         <= FUN_00068b2c @ 0x00068b2c
 *   lc3_energy_compute                       <= FUN_00068b68 @ 0x00068b68
 *   lc3_encode                               <= FUN_00069238 @ 0x00069238
 *   lc3_ltpf_analyse                         <= FUN_0006ab80 @ 0x0006ab80
 *   lc3_ltpf_disable                         <= FUN_0006b364 @ 0x0006b364
 *   lc3_ltpf_put_data                        <= FUN_0006b378 @ 0x0006b378
 *   lc3_mdct_forward                         <= FUN_0006b9b8 @ 0x0006b9b8
 *   lc3_sns_analyze                          <= FUN_0006c778 @ 0x0006c778
 *   lc3_sns_put_data                         <= FUN_0006efdc @ 0x0006efdc
 *   lc3_spec_analyze                         <= FUN_0006f4a0 @ 0x0006f4a0
 *   lc3_spec_put_side                        <= FUN_0006f91c @ 0x0006f91c
 *   lc3_spec_encode                          <= FUN_0006f9c0 @ 0x0006f9c0
 *   lc3_tns_analyze                          <= FUN_0006ffd8 @ 0x0006ffd8
 *   lc3_tns_put_data                         <= FUN_00070b38 @ 0x00070b38
 * address symbols (name @ address):
 *   rodata_8bc88                             @ 0x0008bc88
 */
/* Reconstructed FUN_00069238 @ 0x69238  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
typedef unsigned char byte;
extern void lc3_attdet_run(uint a, uint b, int c, void *d);
extern void lc3_setup_bits(void *a, int b, unsigned c, int d);
extern void lc3_flush_bits(void *a);
extern int lc3_put_bits_generic(void *a, uint b, int c);
extern int lc3_bwdet_run(uint a, uint b, void *c);
extern void lc3_bwdet_put_bw(void *a, uint b, unsigned c);
extern int lc3_energy_compute(uint a, uint b, int c, void *d);
extern void lc3_ltpf_analyse(uint a, uint b, void *c, int d);
extern void lc3_ltpf_disable(void *a);
extern void lc3_ltpf_put_data(void *a, void *b);
extern void lc3_mdct_forward(uint a, uint b, uint c, int d);
extern void lc3_sns_analyze(uint a, uint b, void *c, unsigned d);
extern void lc3_sns_put_data(void *a, void *b);
extern void lc3_spec_analyze(uint a, uint b, int c, uint d);
extern void lc3_spec_put_side(void *a, uint b, uint c, void *d);
extern void lc3_spec_encode(void *a, uint b, uint c, unsigned d);
extern void lc3_tns_analyze(uint a, unsigned b, int c, int d);
extern void lc3_tns_put_data(void *a, void *b);
extern void FUN_00086c44(int a, int b, int c);

undefined4 lc3_encode(byte *param_1, int param_2, undefined4 param_3, undefined4 param_4, int param_5, undefined4 param_6)
{
    uint uVar8, uVar9, local_1b4, local_108, local_10c;
    unsigned char local_1ab;
    int iVar10, iVar11;
    unsigned uVar5;
    unsigned char auStack_128[28];
    unsigned char auStack_1a8[8], auStack_1a0[28], auStack_184[80], auStack_134[12];

    if (param_1 != (byte *)0x0) {
        if (param_5 - 0x14U < 0x17d) {
            (**(void (***)(byte *, undefined4, undefined4))(0x8bc88 + param_2 * 4))(param_1, param_3, param_4);
            uVar9 = (uint)param_1[1];
            iVar11 = *(volatile int *)(param_1 + 0x4a0);
            uVar8 = (uint)*param_1;
            local_1b4 = (uint)param_1[2];
            lc3_attdet_run(uVar8, local_1b4, param_5, param_1 + 4);
            lc3_ltpf_analyse(uVar8, local_1b4, param_1 + 0x10, iVar11);
            FUN_00086c44(iVar11, iVar11, 0);
            iVar10 = *(volatile int *)(param_1 + 0x4a4);
            lc3_mdct_forward(uVar8, local_1b4, uVar9, iVar10);
            iVar11 = lc3_energy_compute(uVar8, uVar9, iVar10, auStack_128);
            if (iVar11 != 0) {
                lc3_ltpf_disable(auStack_1a8);
            }
            local_1ab = lc3_bwdet_run(uVar8, uVar9, auStack_128);
            lc3_sns_analyze(uVar8, uVar9, auStack_128, uVar5 = 0);
            lc3_tns_analyze(uVar8, local_1ab, iVar11, param_5);
            lc3_spec_analyze(uVar8, uVar9, param_5, (uint)local_1ab);
            lc3_setup_bits(auStack_128, 1, param_6, param_5);
            lc3_bwdet_put_bw(auStack_128, (uint)param_1[1], local_1ab);
            lc3_spec_put_side(auStack_128, (uint)*param_1, (uint)param_1[1], auStack_134);
            lc3_tns_put_data(auStack_128, auStack_184);
            if ((int)(local_108 + 1) < 0x21) {
                local_10c = local_10c | (uint)local_1ab << (local_108 & 0xff);
                local_108 = local_108 + 1;
            } else {
                lc3_put_bits_generic(auStack_128, (uint)local_1ab, 1);
            }
            lc3_sns_put_data(auStack_128, auStack_1a0);
            if (local_1ab != 0) {
                lc3_ltpf_put_data(auStack_128, auStack_1a8);
            }
            lc3_spec_encode(auStack_128, (uint)*param_1, (uint)param_1[1], local_1ab);
            lc3_flush_bits(auStack_128);
            return 0;
        }
        return 0xffffffff;
    }
    return 0xffffffff;
}
