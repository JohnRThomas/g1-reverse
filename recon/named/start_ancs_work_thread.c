/* readable reconstruction; identity: FUN_000198cc @ 0x000198cc
 * public-name: start_ancs_work_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 * address symbols (name @ address):
 *   ADDR_ble_ancs_data_req_thread_THUMB      @ 0x00019719
 *   rodata_9af2e                             @ 0x0009af2e
 *   rodata_9b0f1                             @ 0x0009b0f1
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_work_thread                       @ 0x20003c50
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ancs_work_thread_stack                 @ 0x2001d568
 */
/* Reconstructed start_ancs_work_thread @ 0x198cc  (parity: 300/300 trials, PROVEN) */

extern void log_message(int,...);
extern int get_device_info(void);
extern int debug_print(void);
extern int is_battery_critical(void);
/* CONFIG_TIMEOUT_64BIT: z_impl_k_thread_create's 10th parameter is a
 * 64-bit k_timeout_t delay, AAPCS-placed 8-byte aligned at sp+0x18.
 * The original writes it (strd r,r,[sp,#0x18]); it must be passed. */
extern int z_impl_k_thread_create(unsigned,unsigned,int,unsigned,unsigned,int,int,int,int,unsigned long long);
void start_ancs_work_thread(unsigned param_1){
  char* pcVar1; int iVar2;
  pcVar1 = (char*)get_device_info();
  if((*(unsigned char*)pcVar1==2) && (iVar2=is_battery_critical(), iVar2!=1)){
    z_impl_k_thread_create(0x20003c50, 0x2001d568, 0x1400, 0x19719, param_1, 0,0,0xfffffff5,0,0ULL);
    if(2 < *(volatile int*)0x2000230cUL){
      if(*(volatile int*)0x20007554UL != 0){
        debug_print();
        return;
      }
      log_message(0x9af2e, 0x9b0f1);
      return;
    }
  }
  return;
}
