/* net-core FUN_01009bc4 @ 0x1009bc4  (parity 300 trials PROVEN) */
#define P_01009c64 0x21000b7c

extern unsigned char FUN_0102741e(int, int, unsigned char);
extern unsigned int FUN_0102751a(int, short, unsigned char);

unsigned int FUN_01009bc4(short *result_event, unsigned int channel_raw)
{
  /* The shipped entry stores/reloads r1 as a byte before indexing the table.
   * Keep the raw register-width ABI explicit: callers may leave upper bits. */
  const unsigned char channel = (unsigned char)channel_raw;
  unsigned char bVar1;
  unsigned char bVar2;
  unsigned char bVar3;
  int iVar4;
  unsigned int uVar5;
  unsigned int uVar6;

  *result_event = -1;
  iVar4 = *(int *)(P_01009c64 + (unsigned int)channel * 4);
  if (iVar4 == 0) {
    uVar5 = 0;
  } else {
    bVar1 = *(unsigned char *)(iVar4 + 2);
    bVar2 = *(unsigned char *)(iVar4 + 4) - bVar1 * (unsigned char)(*(unsigned char *)(iVar4 + 4) / bVar1);
    bVar3 = FUN_0102741e(iVar4, 0xfff0, bVar2);
    if (bVar3 == 0xff) {
      uVar5 = 0;
    } else {
      uVar6 = (unsigned int)bVar3 + ((unsigned int)bVar1 - (unsigned int)bVar2);
      *result_event = (short)((unsigned short)((short)uVar6 - (unsigned short)bVar1 * (short)(uVar6 / bVar1)) +
                              (unsigned short)*(unsigned char *)(iVar4 + 4));
      uVar5 = FUN_0102751a(iVar4, *result_event, bVar3);
    }
  }
  return uVar5;
}
