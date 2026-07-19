### FUN_0007c1fe  @ 0x0007c1fe  (size=12)

callers (1): get_notification_counts_cmd_process
callees (1): audio_fw_load_get_wrapper

```c
/* readable reconstruction; identity: FUN_0007c1fe @ 0x0007c1fe
 * public-name: FUN_0007c1fe
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_fw_load_get_wrapper                <= FUN_00019b54 @ 0x00019b54
 */
/* Reconstructed FUN_0007c1fe @ 0x7c1fe  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void audio_fw_load_get_wrapper(void);
unsigned int FUN_0007c1fe(unsigned int param_1,unsigned int param_2,unsigned int param_3)
{
  audio_fw_load_get_wrapper();
  return param_3;
}
```