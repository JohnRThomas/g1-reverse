/* Reconstructed FUN_0007c39c @ 0x7c39c  (exact extent 38 bytes)
 *
 * P4 iteration 40.  Catalog-missing sibling of FUN_0007c38a: the `value_len`
 * op of the type-8 (WLCSTAI) NDEF record, installed as the literal 0x0007c39d
 * at offset +4 by fill_record_type8 (0x250c4).  Same call site
 * (opt_node_value_len, 0x7c408, `bx r2` with r0 = the record).
 *
 * Shipped bytes:
 *     0007c39c  cbz    r0, #0x7c3c0        ; NULL -> r0 is already 0
 *     0007c39e  ldrb   r3, [r0]
 *     0007c3a0  cmp    r3, #8
 *     0007c3a2  bne    #0x7c3be            ; wrong type -> 0
 *     0007c3a4  ldrb   r2, [r0, #0x10]     ; the presence bitmap
 *     0007c3a6  movs   r3, #0
 *     0007c3a8  movs   r0, #1              ; the mandatory control byte
 *     0007c3aa  lsr.w  r1, r2, r3
 *     0007c3ae  lsls   r1, r1, #0x1f       ; N = bit r3 of the bitmap
 *     0007c3b0  add.w  r3, r3, #1
 *     0007c3b4  it     mi
 *     0007c3b6  addmi  r0, #1
 *     0007c3b8  cmp    r3, #8
 *     0007c3ba  bne    #0x7c3aa
 *     0007c3bc  bx     lr
 * i.e. the WLCSTAI payload is 1 + popcount(record[0x10]) bytes, which is
 * exactly the fragment count FUN_00024ad8 emits (the control byte plus one
 * byte per set presence bit).
 */

unsigned int FUN_0007c39c(unsigned char *param_1)
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
  uVar1 = param_1[0x10];
  uVar2 = 1;
  uVar3 = 0;
  do {
    if ((uVar1 >> uVar3) & 1) {
      uVar2 = uVar2 + 1;
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 != 8);
  return uVar2;
}
