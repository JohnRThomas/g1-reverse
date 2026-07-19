/* readable reconstruction; identity: FUN_0007c9fe @ 0x0007c9fe
 * public-name: ipc_send_byte_cmd2002
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_ept_op_a_locked_retry                <= FUN_000256dc @ 0x000256dc
 *   ipc_send_byte_cmd2002                    <= FUN_0007c9fe @ 0x0007c9fe
 */
/* Reconstructed FUN_0007c9fe @ 0x7c9fe  (parity: 300/300 trials, PROVEN) */

extern void ipc_ept_op_a_locked_retry(unsigned int,unsigned int,void*,unsigned int,unsigned int,unsigned int);
void ipc_send_byte_cmd2002(unsigned int param_1,unsigned int param_2)
{
  unsigned char b = (unsigned char)param_2;
  ipc_ept_op_a_locked_retry(param_1,0x2002,&b,1,param_1,param_2);
}
