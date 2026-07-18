/* Reconstructed FUN_0004d56c @ 0x4d56c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
/* mpsc_pbuf_claim <= FUN_0004beb8 @ 0x0004beb8 */
extern unsigned mpsc_pbuf_claim(void *);
unsigned FUN_0004d56c(void)
{
  return mpsc_pbuf_claim((void *)0x20003648);
}
