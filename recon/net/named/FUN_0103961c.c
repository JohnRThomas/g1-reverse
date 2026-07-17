/* readable reconstruction; identity: FUN_0103961c @ 0x0103961c
 * public-name: FUN_0103961c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103961c @ 0x103961c  (parity 300 trials PROVEN) */
#include <stdint.h>

extern uint64_t FUN_0100823c(int low, int high, int divisor_low,
                            int divisor_high);
extern unsigned int FUN_01037c64(int low, int high);

void FUN_0103961c(int param_1)
{
  uint64_t quotient = FUN_0100823c(
                                   (int)((uint32_t)param_1 * 0x8000U + 999U),
                                   param_1 >> 17, 1000, 0);
  (void)FUN_01037c64((int)quotient, (int)(quotient >> 32));
}
