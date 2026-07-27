/* readable reconstruction; identity: FUN_0007cbae @ 0x0007cbae
 * public-name: resolve_not_disturb_context
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   resolve_not_disturb_context              <= FUN_0007cbae @ 0x0007cbae
 *   is_system_idle_ready                     <= FUN_0007ce00 @ 0x0007ce00
 */
/* Reconstructed FUN_0007cbae @ 0x7cbae  (parity: 300/300 trials, PROVEN) */
extern int get_device_info(void);
extern int is_system_idle_ready(void);
extern char* not_disturb_disable_pending(void);
char* resolve_not_disturb_context(int p1,int p2,int p3){
  char *r; int iv;
  (void)p1;(void)p2;(void)p3;
  r = (char*)get_device_info();
  if (*r == 1){
    iv = (int)get_device_info();
    if (*(char*)(*(int*)(iv+0x1010)+1) != 0){
      if (is_system_idle_ready() != 0) goto tail;
    }
  }
  r = (char*)get_device_info();
  if (*r != 2) return r;
  iv = (int)get_device_info();
  if (*(char*)(*(int*)(iv+0x1010)+1) == 0) return (char*)(iv+0x1000);
 tail:
  iv = (int)get_device_info();
  { volatile char c = *(char*)(*(int*)(iv+0x1010)+2); (void)c; }
  return not_disturb_disable_pending();
}
