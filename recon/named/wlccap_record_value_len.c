/* readable reconstruction; identity: FUN_0007c38a @ 0x0007c38a
 * public-name: wlccap_record_value_len
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   wlccap_record_value_len                  <= FUN_0007c38a @ 0x0007c38a
 */
/* Reconstructed FUN_0007c38a @ 0x7c38a  (exact extent 14 bytes)
 *
 * P4 iteration 40.  Ghidra never catalogued this leaf: its only reference in
 * the whole image is the literal 0x0007c38b stored into offset +4 of the
 * type-7 (WLCCAP) NDEF record by event_record_init (0x25090), i.e. it is the
 * record's `value_len` op.  opt_node_value_len (0x7c408) reaches it with
 *     0007c40c  ldr r0, [r0, #0x14]   ; the record
 *     0007c410  ldr r2, [r0, #4]
 *     0007c414  bx  r2                ; r0 = the record
 * so the single argument is the record itself.
 *
 * Shipped bytes:
 *     0007c38a  20b1      cbz   r0, #0x7c396
 *     0007c38c  0378      ldrb  r3, [r0]
 *     0007c38e  072b      cmp   r3, #7
 *     0007c390  0cbf      ite   eq
 *     0007c392  0620      moveq r0, #6
 *     0007c394  0020      movne r0, #0
 *     0007c396  7047      bx    lr
 * The NULL path falls into the same `bx lr` with r0 still 0, so a NULL record
 * and a wrong-type record both answer 0.  6 is the fixed WLCCAP payload
 * length (control byte + 5 capability bytes; see the six-way iterator
 * FUN_00024a40 that walks exactly six fragments).
 */

unsigned int wlccap_record_value_len(unsigned char *param_1)
{
  if (param_1 == 0) {
    return 0;
  }
  return (*param_1 == 7) ? 6 : 0;
}
