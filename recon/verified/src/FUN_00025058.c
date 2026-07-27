/* Reconstructed FUN_00025058 @ 0x25058  (exact extent 50 bytes)
 *
 * P4 iteration 40.  Catalog-missing sibling of FUN_00025020: the +12 op of the
 * type-8 (WLCSTAI) NDEF record, installed as the literal 0x00025059 by
 * fill_record_type8 (0x250c4) and reached through invoke_optional_op_offset12.
 * Instruction-for-instruction identical to FUN_00025020 except for the type
 * byte (8) and the type-name descriptor:
 *     00025062  cmp  r3, #8
 *     00025076  ldr  r2, [pc, #0x14]   ; @0x2508c = 0x200023bc
 * 0x200023bc is the shipped `.data` descriptor { 0x0009f1dc, 7 } and
 * 0x0009f1dc is the ASCII "WLCSTAI" — the NFC Forum Wireless Charging
 * Status-and-Information record type name.
 */

extern unsigned int FUN_0007c4b6(unsigned char *);
extern unsigned int FUN_0007c430(unsigned char *param_1, unsigned int param_2,
                                 int *param_3);
extern unsigned int FUN_0007c61e(unsigned char *param_1, unsigned char *param_2);

unsigned int FUN_00025058(unsigned char *param_1, unsigned char *param_2)
{
  if (param_1 == 0 || *param_1 != 8 || param_2 == 0) {
    return 7;
  }
  FUN_0007c4b6(param_2);
  FUN_0007c430(param_2, 1, (int *)0x200023bc);
  return (FUN_0007c61e(param_2, param_1) == 0) ? 0 : 7;
}
