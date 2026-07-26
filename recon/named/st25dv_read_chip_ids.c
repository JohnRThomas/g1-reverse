/* readable reconstruction; identity: FUN_00025290 @ 0x00025290
 * public-name: st25dv_read_chip_ids
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   adc_nfc_init                             <= FUN_00024b98 @ 0x00024b98
 *   st25dv_read_chip_ids                     <= FUN_00025290 @ 0x00025290
 *   serialization_ipc_ept_register           <= FUN_000259d4 @ 0x000259d4
 *   clear_pending_state_flags                <= FUN_0002ebc8 @ 0x0002ebc8
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   st25dv_ipc_request_chip_ids              <= FUN_0007c932 @ 0x0007c932
 *   nfc_ipc_send_op20                        <= FUN_0007c944 @ 0x0007c944
 *   st25dv_ipc_request                       <= FUN_0007c956 @ 0x0007c956
 * address symbols (name @ address):
 *   rodata_9f145                             @ 0x0009f145   [INLINED -- G6 literal batch]
 *   rodata_9f176                             @ 0x0009f176   [INLINED -- G6 literal batch]
 *   rodata_9f186                             @ 0x0009f186   [INLINED -- G6 literal batch]
 *   g_st25dv_dev                             @ 0x20007a44
 *   g_board_rev_flag                         @ 0x20018c69
 */
/* Reconstructed FUN_00025290 @ 0x25290  (parity: 300/300 trials, PROVEN) */
extern int serialization_ipc_ept_register(void);
extern void k_sleep(int,int);
extern void st25dv_ipc_request_chip_ids(int,void*);
extern void log_message(int,...);
extern void nfc_ipc_send_op20(int,void*);
extern void st25dv_ipc_request(int,void*);
extern void adc_nfc_init(void);
extern void clear_pending_state_flags(void);
int st25dv_read_chip_ids(void){
  unsigned local_10=0, local_c=0;
  unsigned char local_12=0, local_11;
  int iVar2;
  volatile int *piVar1 = (volatile int*)0x20007a44UL;
  iVar2 = serialization_ipc_ept_register();
  *piVar1 = iVar2;
  if (iVar2!=0 && *(volatile int*)(iVar2+4)!=0 && *(volatile int*)(iVar2+0x10)!=0 && *(volatile int*)(iVar2+8)!=0){
    unsigned uVar4; unsigned char uVar3; unsigned puVar5; unsigned char *puVar6;
    k_sleep(0x290,0);
    (*(void(**)(void))((*(volatile int*)((*piVar1)+8))+8))();
    st25dv_ipc_request_chip_ids(*piVar1,&local_10);
    uVar4 = (local_10>>8)&0xff;
    log_message(((unsigned long)"UUID = %02X %02X %02X %02X %02X %02X %02X %02X.\n"), local_10&0xff, uVar4, (local_10>>0x10)&0xff, local_10>>0x18, local_c&0xff, (local_c>>8)&0xff, (local_c>>0x10)&0xff, local_c>>0x18);
    uVar3 = (unsigned char)uVar4;
    puVar5 = ((local_c>>8)&0xff) - 0x50;
    puVar6 = (unsigned char*)puVar5;
    if (puVar5 < 2){ uVar3=1; puVar6=(unsigned char*)0x20018c69UL; }
    iVar2 = *piVar1;
    if (puVar5 < 2){ *(volatile unsigned char*)puVar6 = uVar3; }
    nfc_ipc_send_op20(iVar2,&local_12);
    log_message(((unsigned long)"REV_IC = %02X.\n"),(unsigned)local_12);
    st25dv_ipc_request(*piVar1,&local_11);
    log_message(((unsigned long)"REF_IC = %02X.\n"),(unsigned)local_11);
    adc_nfc_init();
    clear_pending_state_flags();
  }
  return 0;
}
