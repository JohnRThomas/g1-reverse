#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00024ad8 @ 0x00024ad8
 * public-name: wlcstai_record_next_fragment
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   wlcstai_record_next_fragment             <= FUN_00024ad8 @ 0x00024ad8
 * address symbols (name @ address):
 *   g_wlcstai_fragment_cursor                @ 0x20007a08
 */
/* Reconstructed FUN_00024ad8 @ 0x24ad8  (exact extent 186 bytes; the halfword
 * at 0x24b92 is alignment and 0x24b94 is its literal pool)
 *
 * P4 iteration 40.  Catalog-missing sibling of FUN_00024a40: the +8 iterator
 * op of the type-8 (WLCSTAI) NDEF record, installed as the literal 0x00024ad9
 * by fill_record_type8 (0x250c4).  Same invoker and same three arguments
 * (record, two-word out view, rewind flag); its cursor is a DIFFERENT cell,
 * 0x20007a08.
 *
 * The difference from the WLCCAP iterator is that WLCSTAI's payload is
 * OPTIONAL-FIELD driven: record[0x10] is a presence bitmap and only the bytes
 * whose bit is set are emitted.  The shipped code expresses that as a nine-way
 * tbb whose arms FALL THROUGH into each other, so entering at cursor k tests
 * bits k-1, k, k+1 ... until one is set:
 *     00024af4  cmp  r2, #8 ; bhi #0x24b82
 *     00024af8  tbb  [pc, r2]            ; table 05 0a 11 18 1f 26 2d 34 3b
 *                                        ; -> 0x24b06 0x24b10 0x24b1e 0x24b2c
 *                                        ;    0x24b3a 0x24b48 0x24b56 0x24b64
 *                                        ;    0x24b72
 *     00024b06  adds r0, #0x10 ; str r0, [r1]     ; cursor 0: the control byte
 *     00024b0a  str  r3, [r4]                     ; cursor <- the NEXT index
 *     00024b0c  ldr  r0, [r1]
 *     00024b0e  pop  {r4, r5, pc}
 *     00024b10  ldrb r3, [r0, #0x10] ; lsls r3, r3, #0x1f ; bpl #0x24b1e
 *     00024b16  adds r0, #0x11 ; movs r3, #2 ; str r0, [r1] ; b #0x24b0a
 *     ... (bit 1 -> +0x12/3, bit 2 -> +0x13/4, bit 3 -> +0x14/5,
 *          bit 4 -> +0x15/6, bit 5 -> +0x16/7, bit 6 -> +0x17/8)
 *     00024b72  ldrsb.w r3, [r0, #0x10] ; cmp r3, #0 ; bge #0x24b82
 *     00024b7a  adds r0, #0x18 ; movs r3, #9 ; str r0, [r1] ; b #0x24b0a
 *     00024b82  movs r3, #0 ; strd r3, r3, [r1] ; b #0x24b0c
 *
 * Note the exhausted arm at 0x24b82 branches to 0x24b0c, NOT 0x24b0a: it zeroes
 * the out view and does NOT touch the cursor.  That asymmetry against the
 * WLCCAP iterator (whose default arm still advances) is deliberate and is
 * reproduced here.
 */

unsigned int wlcstai_record_next_fragment(unsigned char *param_1, unsigned int *param_2,
                          int param_3)
{
  unsigned int uVar1;
  unsigned int uVar2;
  unsigned int uVar3;

  if (param_1 == 0) {
    return 0;
  }
  if (*param_1 != 8) {
    return 0;
  }
  if (param_2 == 0) {
    return 0;
  }
  if (param_3 != 0) {
    *(volatile unsigned int *)((unsigned long)&g_wlcstai_fragment_cursor) /*=0x20007a08*/ = 0;
  }
  uVar1 = *(volatile unsigned int *)((unsigned long)&g_wlcstai_fragment_cursor) /*=0x20007a08*/;
  param_2[1] = 1;
  if (uVar1 > 8) {
    param_2[0] = 0;
    param_2[1] = 0;
    return param_2[0];
  }
  if (uVar1 == 0) {
    param_2[0] = (unsigned int)(param_1 + 0x10);
    *(volatile unsigned int *)((unsigned long)&g_wlcstai_fragment_cursor) /*=0x20007a08*/ = 1;
    return param_2[0];
  }
  uVar3 = param_1[0x10];
  for (uVar2 = uVar1; uVar2 < 9; uVar2++) {
    if ((uVar3 >> (uVar2 - 1)) & 1) {
      param_2[0] = (unsigned int)(param_1 + 0x10 + uVar2);
      *(volatile unsigned int *)((unsigned long)&g_wlcstai_fragment_cursor) /*=0x20007a08*/ = uVar2 + 1;
      return param_2[0];
    }
  }
  param_2[0] = 0;
  param_2[1] = 0;
  return param_2[0];
}
