/* net-core FUN_01009c68 @ 0x1009c68  (parity 300 trials PROVEN) */

extern void FUN_01008d00(unsigned int, unsigned int);
extern signed char FUN_0102741e(void *, unsigned int, signed char);
extern signed char FUN_01027470(void *, unsigned short);
extern unsigned int FUN_010274ea(void *, signed char);
extern unsigned int FUN_0102751a(void *, unsigned short, signed char);

unsigned int FUN_01009c68(unsigned int event_counter_raw,
                          unsigned int channel_raw)
{
  /* Firmware normalizes the incoming register values through STRH/LDRH and
   * STRB/LDRB.  Do it explicitly rather than relying on narrow-argument ABI
   * extension, because callers may leave non-semantic upper bits in r0/r1. */
  const unsigned short event_counter = (unsigned short)event_counter_raw;
  const unsigned char channel = (unsigned char)channel_raw;
  volatile int * const tbl = (volatile int *)0x21000b7c;
  int iVar3 = tbl[channel];
  if (iVar3 == 0) {
    return 0;
  }
  if (event_counter > 0xeff) {
    FUN_01008d00(0x17, 0x27e);
  }
  signed char cVar1 = FUN_01027470((void *)iVar3, event_counter);
  if (cVar1 != -1) {
    return FUN_010274ea((void *)iVar3, cVar1);
  }
  signed char divv = *(volatile unsigned char *)(iVar3 + 2);
  signed char cVar1b = (signed char)event_counter -
                       (signed char)((short)event_counter / divv) * divv;
  signed char cVar2 = FUN_0102741e((void *)iVar3, 0xfff0, cVar1b);
  if (cVar2 == -1) {
    return 0;
  }
  if (cVar2 != cVar1b) {
    *(volatile unsigned char *)(iVar3 + 3) = 0;
  }
  return FUN_0102751a((void *)iVar3, event_counter, cVar2);
}
