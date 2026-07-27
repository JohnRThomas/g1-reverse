/* readable reconstruction; identity: FUN_00085dd2 @ 0x00085dd2
 * public-name: cbor_decode_expect_break
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   zcbor_backup_store_count                 <= FUN_00085d70 @ 0x00085d70
 *   cbor_decode_precheck                     <= FUN_00085d82 @ 0x00085d82
 *   cbor_decode_expect_break                 <= FUN_00085dd2 @ 0x00085dd2
 */
/* Reconstructed FUN_00085dd2 @ 0x85dd2  (parity: 300/300 trials, PROVEN) */

extern int cbor_decode_precheck(unsigned long);
extern void zcbor_backup_store_count(unsigned int *a0, int a1);

int cbor_decode_expect_break(unsigned int *param_1)
{
  int iVar1;
  iVar1 = cbor_decode_precheck(param_1);
  if (iVar1 != 0) {
    unsigned char *p = (unsigned char *)*param_1;
    if (*p == 0xff) {
      *param_1 = (unsigned int)(p + 1);
      return iVar1;
    }
    zcbor_backup_store_count(param_1, 10);
  }
  return 0;
}
