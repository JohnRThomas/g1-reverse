/* readable reconstruction; identity: FUN_00024a40 @ 0x00024a40
 * public-name: wlccap_record_next_fragment
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   wlccap_record_next_fragment              <= FUN_00024a40 @ 0x00024a40
 */
/* Reconstructed FUN_00024a40 @ 0x24a40  (exact extent 142 bytes; the halfword
 * at 0x24ace is alignment and 0x24ad0/0x24ad4 are its literal pool)
 *
 * P4 iteration 40.  Catalog-missing.  Installed as the literal 0x00024a41 at
 * offset +8 of the type-7 (WLCCAP) NDEF record by event_record_init
 * (0x25090).  Its only invoker is serialization_read_or_copy (0x7c670):
 *     0007c67c  strd r5, r5, [r1]     ; zero the 2-word out view
 *     0007c680  ldr  r5, [r0, #0x14]  ; the record
 *     0007c684  ldr  r6, [r5, #8]
 *     0007c688  mov  r0, r5
 *     0007c68a  blx  r6               ; r0 = record, r1 = out view, r2 = flag
 * so all THREE registers are live arguments: the record, a two-word
 * {pointer,length} out view, and a "restart the walk" flag.
 *
 * The function is the WLCCAP payload ITERATOR.  A file-scope cursor at
 * 0x20007a0c selects which of the six payload fragments to hand back; the
 * caller loops until the accumulated length reaches the value_len op's answer
 * (6, FUN_0007c38a).  Every fragment is one byte, so out[1] is set to 1 up
 * front and only the degenerate arm clears it.
 *
 * Shipped bytes (the tbb table at 0x24a64 is `03 06 1d 27 29 2b`, i.e. the six
 * case targets 0x24a6a / 0x24a70 / 0x24a9e / 0x24ab2 / 0x24ab6 / 0x24aba):
 *     00024a40  push {r4, r5, r6, lr}
 *     00024a42  cbz  r0, #0x24a9c            ; NULL   -> return 0
 *     00024a44  ldrb r3, [r0] ; cmp r3, #7
 *     00024a48  bne  #0x24ac6                ; type   -> return 0
 *     00024a4a  cmp  r1, #0 ; beq #0x24aca   ; no out -> return 0
 *     00024a4e  ldr  r4, [pc, #0x80]         ; @0x24ad0 = 0x20007a0c
 *     00024a50  cbz  r2, #0x24a56
 *     00024a52  movs r3, #0 ; str r3, [r4]   ; flag != 0 rewinds the cursor
 *     00024a56  movs r3, #1
 *     00024a58  ldr  r2, [r4]
 *     00024a5a  str  r3, [r1, #4]            ; out[1] = 1  (before the switch)
 *     00024a5c  cmp  r2, #5 ; bhi #0x24abe
 *     00024a60  tbb  [pc, r2]
 *     ...
 *     00024a96  adds r2, #1
 *     00024a98  ldr  r0, [r1]
 *     00024a9a  str  r2, [r4]                ; cursor advances on every arm
 *     00024a9c  pop  {r4, r5, r6, pc}
 *
 * Cases 0, 3, 4 and 5 hand back interior bytes of the record (+0x10, +0x17,
 * +0x18, +0x19).  Cases 1 and 2 REPACK bit fields into the shared one-byte
 * staging cell at 0x20018c67 and hand back a pointer to that cell:
 *     case 1: (rec[0x14] & 1) | (rec[0x11] << 6) | ((rec[0x12] << 2) & 0x3c)
 *                             | ((rec[0x13] << 1) & 2)
 *     case 2: (rec[0x16] & 0x1f) | (rec[0x15] << 5)
 * both truncated to 8 bits by the `strb`.  The out-of-range arm writes the
 * whole out view to zero (a single `strd`) and still advances the cursor.
 */

unsigned int wlccap_record_next_fragment(unsigned char *param_1, unsigned int *param_2,
                          int param_3)
{
  unsigned int uVar1;
  unsigned int uVar2;

  if (param_1 == 0) {
    return 0;
  }
  if (*param_1 != 7) {
    return 0;
  }
  if (param_2 == 0) {
    return 0;
  }
  if (param_3 != 0) {
    *(volatile unsigned int *)0x20007a0c = 0;
  }
  uVar1 = *(volatile unsigned int *)0x20007a0c;
  param_2[1] = 1;
  switch (uVar1) {
  case 0:
    param_2[0] = (unsigned int)(param_1 + 0x10);
    break;
  case 1:
    uVar2 = (param_1[0x14] & 1) | ((unsigned int)param_1[0x11] << 6) |
            (((unsigned int)param_1[0x12] << 2) & 0x3c) |
            (((unsigned int)param_1[0x13] << 1) & 2);
    *(volatile unsigned char *)0x20018c67 = (unsigned char)uVar2;
    param_2[0] = 0x20018c67;
    break;
  case 2:
    uVar2 = (param_1[0x16] & 0x1f) | ((unsigned int)param_1[0x15] << 5);
    *(volatile unsigned char *)0x20018c67 = (unsigned char)uVar2;
    param_2[0] = 0x20018c67;
    break;
  case 3:
    param_2[0] = (unsigned int)(param_1 + 0x17);
    break;
  case 4:
    param_2[0] = (unsigned int)(param_1 + 0x18);
    break;
  case 5:
    param_2[0] = (unsigned int)(param_1 + 0x19);
    break;
  default:
    param_2[0] = 0;
    param_2[1] = 0;
    break;
  }
  *(volatile unsigned int *)0x20007a0c = uVar1 + 1;
  return param_2[0];
}
