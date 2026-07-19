### FUN_00049acc  @ 0x00049acc  (size=1452)

callers (1): FUN_0007d8f4
callees (1): bytes_to_u32le_array

```c
/* readable reconstruction; identity: FUN_00049acc @ 0x00049acc
 * public-name: FUN_00049acc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bytes_to_u32le_array                     <= FUN_0007d8c4 @ 0x0007d8c4
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 */
/* Reconstructed FUN_00049acc @ 0x49acc  (parity: 300/300 trials, PROVEN) */
typedef unsigned int uint;
extern void bytes_to_u32le_array(unsigned char*, void*, int);

void FUN_00049acc(volatile uint *param_1, void *param_2)
{
  int *piVar1;
  int iVar2,iVar3,iVar4,iVar5,iVar6,iVar9,iVar14,iVar15,iVar16,iVar17,iVar18,iVar19,iVar20,iVar23,iVar24,iVar25,iVar26;
  uint uVar7,uVar8,uVar10,uVar11,uVar12,uVar13,uVar21,uVar22;
  unsigned char auStack_128[260];

  iVar6 = *param_1;
  uVar7 = param_1[1];
  uVar22 = param_1[2];
  uVar8 = param_1[3];
  bytes_to_u32le_array(auStack_128,param_2,0x40);
  piVar1 = (int *)auStack_128;
  iVar9 = *piVar1;
  iVar24 = piVar1[7];
  uVar10 = ((uVar22 ^ uVar8) & uVar7 ^ uVar8) + 0xd76aa478 + iVar9 + iVar6;
  uVar11 = uVar7 + (uVar10 >> 0x19 | uVar10 * 0x80);
  iVar3 = piVar1[1];
  uVar10 = ((uVar7 ^ uVar22) & uVar11 ^ uVar22) + 0xe8c7b756 + iVar3 + uVar8;
  iVar4 = piVar1[2];
  uVar10 = uVar11 + (uVar10 >> 0x14 | uVar10 * 0x1000);
  uVar12 = ((uVar7 ^ uVar11) & uVar10 ^ uVar7) + 0x242070db + iVar4 + uVar22;
  iVar5 = piVar1[3];
  uVar13 = uVar10 + (uVar12 >> 0xf | uVar12 * 0x20000);
  uVar12 = ((uVar11 ^ uVar10) & uVar13 ^ uVar11) + 0xc1bdceee + iVar5 + uVar7;
  iVar14 = piVar1[4];
  uVar12 = uVar13 + (uVar12 >> 10 | uVar12 * 0x400000);
  uVar11 = ((uVar10 ^ uVar13) & uVar12 ^ uVar10) + 0xf57c0faf + iVar14 + uVar11;
  iVar15 = piVar1[5];
  uVar11 = uVar12 + (uVar11 >> 0x19 | uVar11 * 0x80);
  uVar10 = ((uVar13 ^ uVar12) & uVar11 ^ uVar13) + 0x4787c62a + iVar15 + uVar10;
  iVar16 = piVar1[6];
  uVar10 = uVar11 + (uVar10 >> 0x14 | uVar10 * 0x1000);
  uVar13 = ((uVar12 ^ uVar11) & uVar10 ^ uVar12) + 0xa8304613 + iVar16 + uVar13;
  uVar13 = uVar10 + (uVar13 >> 0xf | uVar13 * 0x20000);
  uVar12 = ((uVar11 ^ uVar10) & uVar13 ^ uVar11) + 0xfd469501 + iVar24 + uVar12;
  iVar17 = piVar1[8];
  uVar12 = uVar13 + (uVar12 >> 10 | uVar12 * 0x400000);
  iVar25 = piVar1[10];
  uVar11 = ((uVar10 ^ uVar13) & uVar12 ^ uVar10) + 0x698098d8 + iVar17 + uVar11;
  iVar18 = piVar1[9];
  uVar11 = uVar12 + (uVar11 >> 0x19 | uVar11 * 0x80);
  iVar26 = piVar1[0xd];
  uVar10 = ((uVar13 ^ uVar12) & uVar11 ^ uVar13) + 0x8b44f7af + iVar18 + uVar10;
  uVar10 = uVar11 + (uVar10 >> 0x14 | uVar10 * 0x1000);
  uVar13 = ((uVar12 ^ uVar11) & uVar10 ^ uVar12) + iVar25 + -0xa44f + uVar13;
  iVar19 = piVar1[0xb];
  uVar13 = uVar10 + (uVar13 >> 0xf | uVar13 * 0x20000);
  iVar23 = piVar1[0xe];
  uVar12 = ((uVar11 ^ uVar10) & uVar13 ^ uVar11) + 0x895cd7be + iVar19 + uVar12;
  iVar20 = piVar1[0xc];
  uVar12 = uVar13 + (uVar12 >> 10 | uVar12 * 0x400000);
  iVar2 = piVar1[0xf];
  uVar11 = ((uVar10 ^ uVar13) & uVar12 ^ uVar10) + 0x6b901122 + iVar20 + uVar11;
  uVar11 = uVar12 + (uVar11 >> 0x19 | uVar11 * 0x80);
  uVar10 = ((uVar13 ^ uVar12) & uVar11 ^ uVar13) + 0xfd987193 + iVar26 + uVar10;
  uVar10 = uVar11 + (uVar10 >> 0x14 | uVar10 * 0x1000);
  uVar13 = ((uVar12 ^ uVar11) & uVar10 ^ uVar12) + 0xa679438e + iVar23 + uVar13;
  uVar13 = uVar10 + (uVar13 >> 0xf | uVar13 * 0x20000);
  uVar12 = ((uVar11 ^ uVar10) & uVar13 ^ uVar11) + 0x49b40821 + iVar2 + uVar12;
  uVar12 = uVar13 + (uVar12 >> 10 | uVar12 * 0x400000);
  uVar11 = ((uVar13 ^ uVar12) & uVar10 ^ uVar13) + 0xf61e2562 + iVar3 + uVar11;
  uVar11 = uVar12 + (uVar11 >> 0x1b | uVar11 * 0x20);
  uVar10 = ((uVar12 ^ uVar11) & uVar13 ^ uVar12) + 0xc040b340 + iVar16 + uVar10;
  uVar10 = uVar11 + (uVar10 >> 0x17 | uVar10 * 0x200);
  uVar13 = ((uVar11 ^ uVar10) & uVar12 ^ uVar11) + 0x265e5a51 + iVar19 + uVar13;
  uVar13 = uVar10 + (uVar13 >> 0x12 | uVar13 * 0x4000);
  uVar12 = ((uVar10 ^ uVar13) & uVar11 ^ uVar10) + 0xe9b6c7aa + iVar9 + uVar12;
  uVar12 = uVar13 + (uVar12 >> 0xc | uVar12 * 0x100000);
  uVar11 = ((uVar13 ^ uVar12) & uVar10 ^ uVar13) + 0xd62f105d + iVar15 + uVar11;
  uVar11 = uVar12 + (uVar11 >> 0x1b | uVar11 * 0x20);
  uVar10 = ((uVar12 ^ uVar11) & uVar13 ^ uVar12) + 0x02441453 + iVar25 + uVar10;
  uVar10 = uVar11 + (uVar10 >> 0x17 | uVar10 * 0x200);
  uVar13 = ((uVar11 ^ uVar10) & uVar12 ^ uVar11) + 0xd8a1e681 + iVar2 + uVar13;
  uVar13 = uVar10 + (uVar13 >> 0x12 | uVar13 * 0x4000);
  uVar12 = ((uVar10 ^ uVar13) & uVar11 ^ uVar10) + 0xe7d3fbc8 + iVar14 + uVar12;
  uVar12 = uVar13 + (uVar12 >> 0xc | uVar12 * 0x100000);
  uVar11 = ((uVar13 ^ uVar12) & uVar10 ^ uVar13) + 0x21e1cde6 + iVar18 + uVar11;
  uVar11 = uVar12 + (uVar11 >> 0x1b | uVar11 * 0x20);
  uVar10 = ((uVar12 ^ uVar11) & uVar13 ^ uVar12) + 0xc33707d6 + iVar23 + uVar10;
  uVar10 = uVar11 + (uVar10 >> 0x17 | uVar10 * 0x200);
  uVar13 = ((uVar11 ^ uVar10) & uVar12 ^ uVar11) + 0xf4d50d87 + iVar5 + uVar13;
  uVar13 = uVar10 + (uVar13 >> 0x12 | uVar13 * 0x4000);
  uVar12 = ((uVar10 ^ uVar13) & uVar11 ^ uVar10) + 0x455a14ed + iVar17 + uVar12;
  uVar12 = uVar13 + (uVar12 >> 0xc | uVar12 * 0x100000);
  uVar11 = ((uVar13 ^ uVar12) & uVar10 ^ uVar13) + 0xa9e3e905 + iVar26 + uVar11;
  uVar11 = uVar12 + (uVar11 >> 0x1b | uVar11 * 0x20);
  uVar10 = ((uVar12 ^ uVar11) & uVar13 ^ uVar12) + 0xfcefa3f8 + iVar4 + uVar10;
  uVar10 = uVar11 + (uVar10 >> 0x17 | uVar10 * 0x200);
  uVar13 = ((uVar11 ^ uVar10) & uVar12 ^ uVar11) + uVar13 + 0x676f02d9 + iVar24;
  uVar21 = uVar10 + (uVar13 >> 0x12 | uVar13 * 0x4000);
  uVar12 = (uVar11 & (uVar10 ^ uVar21) ^ uVar10) + 0x8d2a4c8a + iVar20 + uVar12;
  uVar12 = uVar21 + (uVar12 >> 0xc | uVar12 * 0x100000);
  uVar11 = (uVar10 ^ uVar21 ^ uVar12) + iVar15 + -0x5c6be + uVar11;
  uVar13 = uVar12 + (uVar11 >> 0x1c | uVar11 * 0x10);
  uVar10 = (uVar21 ^ uVar12 ^ uVar13) + 0x8771f681 + iVar17 + uVar10;
  uVar10 = uVar13 + (uVar10 >> 0x15 | uVar10 * 0x800);
  uVar11 = (uVar12 ^ uVar13 ^ uVar10) + 0x6d9d6122 + iVar19 + uVar21;
  uVar21 = uVar10 + (uVar11 >> 0x10 | uVar11 * 0x10000);
  uVar12 = (uVar13 ^ uVar10 ^ uVar21) + uVar12 + 0xfde5380c + iVar23;
  uVar11 = uVar21 + (uVar12 >> 9 | uVar12 * 0x800000);
  uVar12 = (uVar10 ^ uVar21 ^ uVar11) + 0xa4beea44 + iVar3 + uVar13;
  uVar13 = uVar11 + (uVar12 >> 0x1c | uVar12 * 0x10);
  uVar10 = (uVar21 ^ uVar11 ^ uVar13) + 0x4bdecfa9 + iVar14 + uVar10;
  uVar10 = uVar13 + (uVar10 >> 0x15 | uVar10 * 0x800);
  uVar12 = (uVar11 ^ uVar13 ^ uVar10) + uVar21 + 0xf6bb4b60 + iVar24;
  uVar12 = uVar10 + (uVar12 >> 0x10 | uVar12 * 0x10000);
  uVar11 = (uVar13 ^ uVar10 ^ uVar12) + uVar11 + 0xbebfbc70 + iVar25;
  uVar21 = uVar12 + (uVar11 >> 9 | uVar11 * 0x800000);
  uVar11 = (uVar10 ^ uVar12 ^ uVar21) + 0x289b7ec6 + iVar26 + uVar13;
  uVar13 = uVar21 + (uVar11 >> 0x1c | uVar11 * 0x10);
  uVar10 = (uVar12 ^ uVar21 ^ uVar13) + uVar10 + 0xeaa127fa + iVar9;
  uVar11 = uVar13 + (uVar10 >> 0x15 | uVar10 * 0x800);
  uVar10 = (uVar21 ^ uVar13 ^ uVar11) + uVar12 + 0xd4ef3085 + iVar5;
  uVar10 = uVar11 + (uVar10 >> 0x10 | uVar10 * 0x10000);
  uVar12 = (uVar13 ^ uVar11 ^ uVar10) + 0x04881d05 + iVar16 + uVar21;
  uVar21 = uVar10 + (uVar12 >> 9 | uVar12 * 0x800000);
  uVar12 = (uVar11 ^ uVar10 ^ uVar21) + uVar13 + 0xd9d4d039 + iVar18;
  uVar12 = uVar21 + (uVar12 >> 0x1c | uVar12 * 0x10);
  uVar11 = (uVar10 ^ uVar21 ^ uVar12) + uVar11 + 0xe6db99e5 + iVar20;
  uVar13 = uVar12 + (uVar11 >> 0x15 | uVar11 * 0x800);
  uVar10 = (uVar21 ^ uVar12 ^ uVar13) + 0x1fa27cf8 + iVar2 + uVar10;
  uVar10 = uVar13 + (uVar10 >> 0x10 | uVar10 * 0x10000);
  uVar11 = (uVar12 ^ uVar13 ^ uVar10) + uVar21 + 0xc4ac5665 + iVar4;
  uVar11 = uVar10 + (uVar11 >> 9 | uVar11 * 0x800000);
  uVar12 = ((uVar11 | ~uVar13) ^ uVar10) + 0xf4292244 + iVar9 + uVar12;
  uVar12 = uVar11 + (uVar12 >> 0x1a | uVar12 * 0x40);
  uVar13 = ((uVar12 | ~uVar10) ^ uVar11) + 0x432aff97 + iVar24 + uVar13;
  uVar21 = uVar12 + (uVar13 >> 0x16 | uVar13 * 0x400);
  uVar10 = ((uVar21 | ~uVar11) ^ uVar12) + 0xab9423a7 + iVar23 + uVar10;
  uVar10 = uVar21 + (uVar10 >> 0x11 | uVar10 * 0x8000);
  uVar11 = ((uVar10 | ~uVar12) ^ uVar21) + 0xfc93a039 + iVar15 + uVar11;
  uVar13 = uVar10 + (uVar11 >> 0xb | uVar11 * 0x200000);
  uVar12 = ((uVar13 | ~uVar21) ^ uVar10) + 0x655b59c3 + iVar20 + uVar12;
  uVar11 = uVar13 + (uVar12 >> 0x1a | uVar12 * 0x40);
  uVar12 = ((uVar11 | ~uVar10) ^ uVar13) + 0x8f0ccc92 + iVar5 + uVar21;
  uVar21 = uVar11 + (uVar12 >> 0x16 | uVar12 * 0x400);
  uVar10 = ((uVar21 | ~uVar13) ^ uVar11) + iVar25 + -0x100b83 + uVar10;
  uVar12 = uVar21 + (uVar10 >> 0x11 | uVar10 * 0x8000);
  uVar10 = ((uVar12 | ~uVar11) ^ uVar21) + 0x85845dd1 + iVar3 + uVar13;
  uVar13 = uVar12 + (uVar10 >> 0xb | uVar10 * 0x200000);
  uVar10 = ((uVar13 | ~uVar21) ^ uVar12) + 0x6fa87e4f + iVar17 + uVar11;
  uVar11 = uVar13 + (uVar10 >> 0x1a | uVar10 * 0x40);
  uVar10 = ((uVar11 | ~uVar12) ^ uVar13) + 0xfe2ce6e0 + iVar2 + uVar21;
  uVar10 = uVar11 + (uVar10 >> 0x16 | uVar10 * 0x400);
  uVar12 = ((uVar10 | ~uVar13) ^ uVar11) + 0xa3014314 + iVar16 + uVar12;
  uVar12 = uVar10 + (uVar12 >> 0x11 | uVar12 * 0x8000);
  uVar13 = ((uVar12 | ~uVar11) ^ uVar10) + uVar13 + 0x4e0811a1 + iVar26;
  uVar21 = uVar12 + (uVar13 >> 0xb | uVar13 * 0x200000);
  uVar11 = ((uVar21 | ~uVar10) ^ uVar12) + uVar11 + 0xf7537e82 + iVar14;
  uVar13 = uVar21 + (uVar11 >> 0x1a | uVar11 * 0x40);
  uVar10 = ((uVar13 | ~uVar12) ^ uVar21) + uVar10 + 0xbd3af235 + iVar19;
  uVar11 = uVar13 + (uVar10 >> 0x16 | uVar10 * 0x400);
  uVar10 = ((uVar11 | ~uVar21) ^ uVar13) + 0x2ad7d2bb + iVar4 + uVar12;
  uVar12 = uVar11 + (uVar10 >> 0x11 | uVar10 * 0x8000);
  uVar10 = ((uVar12 | ~uVar13) ^ uVar11) + uVar21 + 0xeb86d391 + iVar18;
  *param_1 = uVar13 + iVar6;
  param_1[1] = uVar7 + uVar12 + (uVar10 >> 0xb | uVar10 * 0x200000);
  param_1[2] = uVar12 + uVar22;
  param_1[3] = uVar11 + uVar8;
  return;
}
```