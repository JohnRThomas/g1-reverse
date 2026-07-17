/* readable reconstruction; identity: FUN_01008940 @ 0x01008940
 * public-name: FUN_01008940
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01008940 @ 0x1008940  (parity 300 trials PROVEN) */

typedef unsigned int uint;
static inline int CARRY4(unsigned a,unsigned b){return (a+b)<a;}

unsigned long long FUN_01008940(uint param_1,uint param_2,uint param_3,uint param_4)
{
  uint unaff_r4=0, unaff_r5=0, unaff_r6=0, unaff_r7=0, unaff_r8=0, unaff_r9=0, unaff_r10=0, unaff_r11=0;
  uint uVar3,uVar4,uVar5,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13,uVar14,uVar15;
  int bVar16,bVar17,bVar1,bVar2;

  uVar7 = unaff_r8 + unaff_r4;
  bVar16 = CARRY4(unaff_r9,unaff_r5) || CARRY4(unaff_r9 + unaff_r5,(uint)CARRY4(unaff_r8,unaff_r4));
  uVar10 = unaff_r9 + unaff_r5 + CARRY4(unaff_r8,unaff_r4);
  bVar17 = CARRY4(unaff_r10,unaff_r6) || CARRY4(unaff_r10 + unaff_r6,(uint)bVar16);
  uVar12 = unaff_r10 + unaff_r6 + bVar16;
  uVar14 = unaff_r11 + unaff_r7 + bVar17;
  uVar3 = (uint)(CARRY4(unaff_r11,unaff_r7) || CARRY4(unaff_r11 + unaff_r7,(uint)bVar17));
  uVar8 = uVar7 + unaff_r5;
  bVar16 = CARRY4(uVar10,unaff_r6) || CARRY4(uVar10 + unaff_r6,(uint)CARRY4(uVar7,unaff_r5));
  uVar10 = uVar10 + unaff_r6 + CARRY4(uVar7,unaff_r5);
  bVar17 = CARRY4(uVar12,unaff_r7) || CARRY4(uVar12 + unaff_r7,(uint)bVar16);
  uVar12 = uVar12 + unaff_r7 + bVar16;
  bVar16 = CARRY4(uVar14,unaff_r7) || CARRY4(uVar14 + unaff_r7,(uint)bVar17);
  uVar14 = uVar14 + unaff_r7 + bVar17;
  bVar17 = CARRY4(param_1,uVar3) || CARRY4(param_1 + uVar3,(uint)bVar16);
  param_1 = param_1 + uVar3 + bVar16;
  bVar16 = CARRY4(param_2,(uint)bVar17);
  param_2 = param_2 + bVar17;
  bVar17 = CARRY4(param_3,(uint)bVar16);
  param_3 = param_3 + bVar16;
  uVar4 = param_4 + unaff_r4 + (uint)bVar17;
  uVar9 = uVar8 - unaff_r7;
  bVar16 = uVar10 < (unaff_r7 <= uVar8);
  uVar11 = uVar10 - (unaff_r7 > uVar8);
  bVar1 = uVar12 < (uVar10 != 0 || bVar16);
  uVar13 = uVar12 - (uVar10 == 0 && !bVar16);
  bVar16 = uVar14 - unaff_r4 < (uint)(uVar12 != 0 || bVar1);
  uVar15 = (uVar14 - unaff_r4) - (uint)(uVar12 == 0 && !bVar1);
  bVar1 = param_1 - unaff_r5 < (uint)(unaff_r4 < uVar14 || bVar16);
  uVar3 = (param_1 - unaff_r5) - (uint)(unaff_r4 >= uVar14 && !bVar16);
  bVar16 = param_2 - unaff_r6 < (uint)(unaff_r5 < param_1 || bVar1);
  uVar7 = (param_2 - unaff_r6) - (uint)(unaff_r5 >= param_1 && !bVar1);
  bVar1 = param_3 - unaff_r4 < (uint)(unaff_r6 < param_2 || bVar16);
  uVar12 = (param_3 - unaff_r4) - (uint)(unaff_r6 >= param_2 && !bVar16);
  uVar5 = (uVar4 - unaff_r6) - (uint)(unaff_r4 >= param_3 && !bVar1);
  bVar16 = uVar3 - unaff_r6 < (uint)(unaff_r5 <= uVar15);
  uVar8 = (uVar3 - unaff_r6) - (uint)(unaff_r5 > uVar15);
  bVar2 = uVar7 - unaff_r7 < (uint)(unaff_r6 < uVar3 || bVar16);
  uVar10 = (uVar7 - unaff_r7) - (uint)(unaff_r6 >= uVar3 && !bVar16);
  bVar16 = uVar12 - unaff_r5 < (uint)(unaff_r7 < uVar7 || bVar2);
  uVar14 = (uVar12 - unaff_r5) - (uint)(unaff_r7 >= uVar7 && !bVar2);
  uVar6 = (uVar5 - unaff_r7) - (uint)(unaff_r5 >= uVar12 && !bVar16);
  uVar4 = ((uint)(CARRY4(param_4,unaff_r4) || CARRY4(param_4 + unaff_r4,(uint)bVar17)) -
          (uint)(uVar4 <= unaff_r6 && (uint)(unaff_r4 < param_3 || bVar1) <= uVar4 - unaff_r6)) -
          (uint)(uVar5 <= unaff_r7 && (uint)(unaff_r5 < uVar12 || bVar16) <= uVar5 - unaff_r7);
  uVar12 = uVar4 | 1;
  uVar3 = (uint)((int)uVar4 >> 1);
  uVar7 = (uint)((int)(uVar4 ^ 2) >> 1);
  uVar7 = (uVar4 - uVar3) -
          (uint)(!CARRY4(uVar6,uVar3) &&
                !CARRY4(uVar6 + uVar3,
                        (uint)(uVar7 < uVar14 ||
                              uVar14 - uVar7 <
                              (uint)(uVar3 < uVar10 ||
                                    uVar10 - uVar3 <
                                    (uint)(uVar3 < uVar8 ||
                                          uVar8 - uVar3 <
                                          (uint)(uVar3 < uVar15 - unaff_r5 ||
                                                (uVar15 - unaff_r5) - uVar3 <
                                                (uint)(CARRY4(uVar13,uVar3) ||
                                                      CARRY4(uVar13 + uVar3,
                                                             (uint)(CARRY4(uVar11,uVar3) ||
                                                                   CARRY4(uVar11 + uVar3,
                                                                          (uint)CARRY4(uVar9,uVar12)
                                                                         ))))))))));
  unsigned long long lo = uVar9 + uVar12 + uVar7;
  unsigned int hi = uVar11 + uVar3 + CARRY4(uVar9,uVar12) + uVar7 + CARRY4(uVar9 + uVar12,uVar7);
  return ((unsigned long long)hi << 32) | (unsigned int)lo;
}
