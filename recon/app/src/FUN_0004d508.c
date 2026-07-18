/* Reconstructed FUN_0004d508 @ 0x4d508  (parity: 300/300 trials, PROVEN) */

/* mpsc_pbuf_init <= FUN_0004bc28 @ 0x0004bc28 */
extern void mpsc_pbuf_init(void *, const void *);
void FUN_0004d508(void)
{
  mpsc_pbuf_init((void *)0x20003648UL, (const void *)0x0008aca0UL);
  *(volatile unsigned int *)0x2000a0ccUL = 0x20003648UL;
}
