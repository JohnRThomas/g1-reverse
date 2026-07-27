/* readable reconstruction; identity: FUN_00084fec @ 0x00084fec
 * public-name: enqueue_string_with_len
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   cjson_parse_with_opts                    <= FUN_00064b64 @ 0x00064b64
 *   enqueue_string_with_len                  <= FUN_00084fec @ 0x00084fec
 */
/* Reconstructed FUN_00084fec @ 0x84fec  (parity: 300/300 trials, PROVEN) */

extern int strlen(int);
extern void cjson_parse_with_opts(int,int,unsigned int,unsigned int);
void enqueue_string_with_len(int param_1,unsigned int param_2,unsigned int param_3)
{
  int iVar1;
  if (param_1 != 0) {
    iVar1 = strlen(param_1);
    cjson_parse_with_opts(param_1,iVar1+1,param_2,param_3);
    return;
  }
  return;
}
