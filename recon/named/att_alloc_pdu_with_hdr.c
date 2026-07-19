/* readable reconstruction; identity: FUN_000573f4 @ 0x000573f4
 * public-name: att_alloc_pdu_with_hdr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_create_pdu_timeout               <= FUN_000569ec @ 0x000569ec
 *   log_bt_buf_alloc_failure                 <= FUN_000573c8 @ 0x000573c8
 *   att_alloc_pdu_with_hdr                   <= FUN_000573f4 @ 0x000573f4
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 */
/* Reconstructed FUN_000573f4 @ 0x573f4  (parity: 300/300 trials, PROVEN) */

extern int bt_conn_create_pdu_timeout(int,int,unsigned,int);
extern void* net_buf_simple_add(int,int);
extern int log_bt_buf_alloc_failure(int);
int att_alloc_pdu_with_hdr(int param_1, unsigned char param_2, unsigned short param_3, unsigned param_4){
  unsigned uVar1 = 0x20003ab0;
  if(param_1!=6) uVar1=0;
  int iVar2 = bt_conn_create_pdu_timeout(uVar1,4,0x10000,0);
  if(iVar2==0){ return log_bt_buf_alloc_failure(param_1); }
  unsigned char* puVar3 = (unsigned char*)net_buf_simple_add(iVar2+0xc,4);
  *puVar3=(unsigned char)param_1;
  puVar3[1]=param_2;
  *(unsigned short*)(puVar3+2)=param_3;
  return iVar2;
}
