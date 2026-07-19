#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_watchdog_disable_work_ctx__param_0682  [param_0682; G1-original]
 * Raw function identity: 0x00084c94.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00084c94 @ 0x00084c94
 * public-name: watchdog_disable_write_work
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 *   watchdog_disable_write_work              <= FUN_00084c94 @ 0x00084c94
 */
/* Reconstructed FUN_00084c94 @ 0x84c94  (parity: 300/300 trials, PROVEN) */

extern int dev_write_reg3(unsigned int, unsigned int,
                        unsigned int, unsigned int);

struct request {
  unsigned int reserved_00;
  unsigned int *value;
  unsigned int reserved_08;
  unsigned int reserved_0c;
  unsigned char *completion;
};

void watchdog_disable_write_work(struct request *request)
{
  int status = dev_write_reg3(*request->value, 7, 1, 1);
  if (status >= 0) {
    *request->completion = 0;
  }
}
