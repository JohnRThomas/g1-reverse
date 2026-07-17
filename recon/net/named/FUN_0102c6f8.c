/* readable reconstruction; identity: FUN_0102c6f8 @ 0x0102c6f8
 * public-name: FUN_0102c6f8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_102d22d                           @ 0x0102d22d
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d394                           @ 0x0103d394
 */
/* net-core FUN_0102c6f8 @ 0x102c6f8  (parity 258 trials PROVEN) */
extern unsigned long long FUN_01039ade(int*);
extern int  FUN_01036128(int);
extern int  FUN_0103610c(int);
extern void FUN_01036144(int);
extern void FUN_01039b36(int*, void*, unsigned, void*);
extern void FUN_01039bb0(int, unsigned);
extern void FUN_01039bbe(int, int, unsigned);

typedef void (*cb_t)(int*, void*, unsigned, void*);
typedef void (*pc_t)(int*, unsigned);

void FUN_0102c6f8(int *p, int param_2, int param_3, unsigned param_4)
{
  volatile unsigned short *FLp  = (volatile unsigned short*)((char*)p + 0x1c);
  volatile short          *CNTp = (volatile short*)((char*)p + 0x1e);
  volatile unsigned       *W    = (volatile unsigned*)p;   /* p[0], p[1] */
  int piv = (int)((char*)p + 0x14);
  unsigned uVar5 = 0, uVar7 = 0, k = 0, kind = 0;
  unsigned *puVar11, *puVar12 = 0, *puVar13, *puVar14 = 0;
  void *pcVar9 = 0;
  int sl = 0;
  unsigned long long uVar16;
  unsigned uVar8 = (unsigned)*FLp;

  if (uVar8 & 8) {
      unsigned uv7 = (param_2 == 1) ? 0x10u : 0x20u;
      *FLp = (unsigned short)(uVar8 | uv7);
      goto L_73c;
  }
  uVar5 = uVar8 & 7;
  if (param_2 != 2) goto L_7d6;
  goto L_710;

L_73c:
  if (FUN_01036128(piv) != 0) return;
  goto ASSERTL;

L_710:
  uVar16 = FUN_01039ade(p);
  uVar5 = (unsigned)(uVar16 >> 32);
  if ((int)uVar16 == 0) goto L_73c;
  {
    unsigned iv = (unsigned)((int)uVar16 - 1);
    if (iv == 0) goto L_7d6;
    else if (iv == 2) goto L_820;
    else if (iv == 3) goto L_8ac;
    else if (iv == 4) goto L_906;
    else goto ASSERTL;
  }

L_7d6:
  puVar14 = (unsigned*)((unsigned*)p)[6];
  uVar7 = (unsigned)*FLp;
  if ((int)(unsigned)puVar14 < 0) {
      puVar12 = (unsigned*)W[0];
      W[0] = 0; W[1] = 0;
      uVar7 = (uVar7 & 0xfff8) | 1;
      *FLp = (unsigned short)uVar7;
      goto L_7f4;
  }
  k = uVar7 & 7;
  if ((unsigned)(k - 5) <= 1) {                 /* k == 5 or 6 */
      puVar12 = (unsigned*)W[0];
      W[0] = 0; W[1] = 0;
      if (k == 6) {
          puVar13 = puVar12;
          while (puVar13 != 0) {
              *CNTp = (short)(*CNTp + 1);
              puVar13 = (unsigned*)*puVar13;
          }
          uVar7 = (uVar7 & 0xfff8) | 2;
      } else {
          uVar7 = (uVar7 & 0xfff8);
      }
      *FLp = (unsigned short)uVar7;
      uVar16 = FUN_01039ade(p);
      uVar5 = (unsigned)(uVar16 >> 32);
      if ((int)uVar16 != 0) *FLp = (unsigned short)(uVar7 | 0x20);
      goto L_7f4;
  }
  if (k != 4) goto ASSERTL;
  /* k == 4 */
  uVar7 = (uVar7 & 0xfff8);
  *FLp = (unsigned short)uVar7;
  uVar16 = FUN_01039ade(p);
  uVar5 = (unsigned)(uVar16 >> 32);
  if ((int)uVar16 != 0) *FLp = (unsigned short)(uVar7 | 0x20);
  /* L_7b8 */
  uVar7 = (unsigned)*FLp;
  k = uVar7 & 7;
  if (k != uVar5) { puVar12 = 0; pcVar9 = 0; goto L_878; }
  goto L_7c4;

L_7f4:
  uVar7 = (unsigned)*FLp;
  k = uVar7 & 7;
  if (k != uVar5) { pcVar9 = 0; goto L_878; }
  if (puVar12 != 0) { pcVar9 = 0; sl = 0; goto L_888; }
  goto L_7c4;

L_878:
  if (((unsigned*)p)[2] != 0) { sl = 1; goto L_888; }
  if (puVar12 != 0) { sl = 0; goto L_888; }
  if (pcVar9 == 0) goto L_7c4;
  sl = 0;
L_888:
  uVar7 = uVar7 | 8;
  *FLp = (unsigned short)uVar7;
  if (FUN_01036128(piv) == 0) goto ASSERTL;
  if (sl != 0) {
      puVar13 = (unsigned*)((unsigned*)p)[2];
      if (puVar13 != 0) {
          puVar11 = (unsigned*)*puVar13;
          while (puVar13 != 0) {
              ((cb_t)(((void**)puVar13)[1]))(p, puVar13, kind, puVar14);
              puVar13 = puVar11;
              if (puVar11 != 0) puVar11 = (unsigned*)*puVar11;
          }
      }
  }
  while (puVar12 != 0) {
      unsigned *nx = (unsigned*)*puVar12;
      FUN_01039b36(p, puVar12, kind, puVar14);
      puVar12 = nx;
  }
  if (pcVar9 != 0) {
      ((pc_t)pcVar9)(p, 0x0102d22du);
  }
  if (FUN_0103610c(piv) == 0) goto ASSERTL;
  FUN_01036144(piv);
  *FLp = (unsigned short)((unsigned)*FLp & 0xfff7);
  goto L_7c4;

L_7c4:
  uVar5 = (unsigned)*FLp;
  if (uVar5 & 0x10) {
      *FLp = (unsigned short)(uVar5 & ~0x10u);
      uVar5 = uVar5 & 7;
      goto L_7d6;
  }
  if (uVar5 & 0x20) {
      *FLp = (unsigned short)(uVar5 & ~0x20u);
      goto L_710;
  }
  goto L_73c;

L_820:  /* case 3 */
  if (uVar5 == 0) {
      if ((unsigned)W[0] == 0) goto ASSERTL;
      pcVar9 = *(void**)(unsigned)((unsigned*)p)[4];
      if (pcVar9 == 0) goto ASSERTL;
      puVar12 = 0; puVar14 = 0; kind = 6;
      uVar7 = ((unsigned)*FLp & 0xfff8) | 6;
      *FLp = (unsigned short)uVar7;
      goto L_878;
  }
  goto ASSERTL;

L_8ac:  /* case 4 */
  if (uVar5 == 2) {
      if (*CNTp != 0) goto ASSERTL;
      pcVar9 = *(void**)((unsigned)((unsigned*)p)[4] + 4);
      if (pcVar9 == 0) goto ASSERTL;
      puVar12 = 0; puVar14 = 0; kind = 4;
      uVar7 = ((unsigned)*FLp & 0xfff8) | 4;
      *FLp = (unsigned short)uVar7;
      goto L_878;
  }
  goto ASSERTL;

L_906:  /* case 5 */
  if (uVar5 == 1) {
      if ((unsigned)W[0] == 0) goto ASSERTL;
      pcVar9 = *(void**)((unsigned)((unsigned*)p)[4] + 8);
      if (pcVar9 == 0) goto ASSERTL;
      puVar12 = 0; puVar14 = 0; kind = 5;
      uVar7 = ((unsigned)*FLp & 0xfff8) | 5;
      *FLp = (unsigned short)uVar7;
      goto L_878;
  }
  goto ASSERTL;

ASSERTL:
  for (;;) {
      FUN_01039bbe(0x0103d2a7, 0x0103d394, 0x156);
      FUN_01039bb0(0x0103d394, 0x156);
  }
}
