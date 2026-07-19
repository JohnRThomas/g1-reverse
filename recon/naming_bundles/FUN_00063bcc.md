### FUN_00063bcc  @ 0x00063bcc  (size=16)

callers (2): power_manager_system_off, reset_state_and_stop_timer
callees (1): FUN_0004f564

```c
/* readable reconstruction; identity: FUN_00063bcc @ 0x00063bcc
 * public-name: FUN_00063bcc
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_fa9cc                             @ 0x000fa9cc
 */
/* Reconstructed FUN_00063bcc @ 0x63bcc  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_0004f564(unsigned int a);
void FUN_00063bcc(void) {
  unsigned int r = FUN_0004f564(0xc);
  if (r != 0) {
    *(unsigned int*)(r + 4) = 0x000fa9ccUL;
  }
}
```