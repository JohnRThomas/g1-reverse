/* readable reconstruction; identity: FUN_01034be4 @ 0x01034be4
 * public-name: FUN_01034be4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103e6f2                           @ 0x0103e6f2
 *   g_sdc_res_pool_slot_tbl                  @ 0x210006a8
 */
#include "../../headers/g1_nrf_regs.h"
/* net-core FUN_01034be4 @ 0x1034be4  (parity 300 trials PROVEN) */
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned short ushort;

static inline unsigned ctz32(unsigned x){
  return (unsigned)__builtin_ctz(x);
}

extern int FUN_0103467c(uint);
extern int FUN_010344a8(uint);
extern void FUN_01034538(uint, uint);
extern int FUN_010345f4(uint *);
extern void FUN_0103a9be(uint, uint);

void FUN_01034be4(void)
{
  volatile uint *p304 = (volatile uint *)(G1_NRF_GPIOTE_NS_BASE + 0x304);
  uint r0 = *p304 & 0xffu;
  r0 |= 0x80000000u;
  int uVar6 = FUN_0103467c(r0);

  volatile uint *sl20 = (volatile uint *)(G1_NRF_P0_NS_BASE + 0x20);
  volatile uint *sb20 = (volatile uint *)(G1_NRF_P1_NS_BASE + 0x20);
  const byte *tbl_d84 = (const byte *)0x0103e6f2;
  const volatile ushort *tbl_d88 = (const volatile ushort *)0x210006a8;

  uint local_30[2];

  if (uVar6 < 0) {
    uint t;
    t = *sl20; local_30[0] = t; *sl20 = t;
    t = *sb20; local_30[1] = t; *sb20 = t;

LAB_c1c:
    for (int fp = 0; ; fp++) {
      const byte *tp = tbl_d84 + fp;
      for (;;) {
        uint val = local_30[fp];
        if (val == 0) break;
        uint bitpos = ctz32(val);
        byte tb = *tp;
        uint uVar12 = bitpos | ((uint)tb << 5);
        int retA = FUN_010344a8(uVar12);
        ushort uVar1 = tbl_d88[retA + 8];

        uint byteIdx = bitpos >> 3;
        byte *bp = (byte *)&local_30[fp];
        bp[byteIdx] = bp[byteIdx] & (byte)~(1u << (bitpos & 7));

        uint local_34 = uVar12;
        int iVar8 = FUN_010345f4(&local_34);
        uint uVar13 = ((uint)uVar1 << 0x1b) >> 0x1d;
        uint uVar7 = (uint)(*(volatile int *)(iVar8 + (local_34 + 0x80) * 4) << 0xe) >> 0x1e;

        if ((int)(((uint)(uVar1 >> 2)) << 0x1d) < 0) {
          FUN_01034538(uVar12, uVar13);
          local_34 = uVar12;
          iVar8 = FUN_010345f4(&local_34);
          if (uVar7 == (uint)(*(volatile int *)(iVar8 + (local_34 + 0x80) * 4) << 0xe) >> 0x1e) {
            FUN_0103a9be(uVar12, 0);
            FUN_0103a9be(uVar12, uVar7);
          }
        } else {
          int bVar16 = 0;
          int doCf2 = 0;
          if (uVar7 == 2) {
            FUN_0103a9be(uVar12, 3);
            bVar16 = (uVar13 & 5) == 1;
            doCf2 = 1;
          } else {
            FUN_0103a9be(uVar12, 2);
            if (uVar13 != 3) {
              if (uVar7 != 3) goto LAB_cb8;
              bVar16 = (uVar13 == 2);
              doCf2 = 1;
            }
          }
          if (doCf2) {
            if (!bVar16) goto LAB_cb8;
          }
          FUN_01034538(uVar12, uVar13);
        }
LAB_cb8:;
        local_34 = uVar12;
        iVar8 = FUN_010345f4(&local_34);
        *(volatile uint *)(iVar8 + 0x20) = 1u << (local_34 & 0xff);
      }
      if (fp != 0) goto LAB_d16;
    }

LAB_d16:
    (void)FUN_0103467c(0x80000000u);
    uint a, b;
    a = *sl20; local_30[0] = a; *sl20 = a;
    b = *sb20;
    uint orv = a | b;
    local_30[1] = b; *sb20 = b;
    if (orv != 0) goto LAB_c1c;
    uVar6 = uVar6 & 0x7fffffff;
  }

  uint r5 = (uint)uVar6;
  if (r5 != 0) {
    do {
      uint pos = ctz32(r5);
      uint r2 = 1u << pos;
      uint addr = 0x4100a510u + pos * 4u;
      volatile uint *ap = (volatile uint *)addr;
      uint v0 = *ap;
      uint v1 = *ap;
      uint a0 = (v0 >> 8) & 0x3f;
      uint a1 = (v1 >> 16) & 3;
      r5 = r5 & ~r2;
      FUN_01034538(a0, a1);
    } while (r5 != 0);
  }
}
