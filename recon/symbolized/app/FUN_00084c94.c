#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084c94 @ 0x00084c94
 * public-name: FUN_00084c94
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
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

void FUN_00084c94(struct request *request)
{
  int status = dev_write_reg3(*request->value, 7, 1, 1);
  if (status >= 0) {
    *request->completion = 0;
  }
}
