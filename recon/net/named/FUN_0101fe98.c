/* readable reconstruction; identity: FUN_0101fe98 @ 0x0101fe98
 * public-name: FUN_0101fe98
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_net_radio_pending_reset_flag           @ 0x210014dc
 *   REG_41008000                             @ 0x41008000
 *   REG_4100e000                             @ 0x4100e000
 */
/* net-core FUN_0101fe98 @ 0x101fe98  (parity 300 trials PROVEN) */

extern void sdc_assertion_fail(unsigned int, unsigned int);

void FUN_0101fe98(unsigned int param_1, unsigned int param_2)
{
  volatile unsigned char * const pcVar2 = (volatile unsigned char *)0x210014dc;
  volatile unsigned int * const puVar3 = (volatile unsigned int *)0x4100e000;
  volatile unsigned int * const p150 = (volatile unsigned int *)0x41008000;
  volatile unsigned int * const p504 = (volatile unsigned int *)0x4100f000;
  unsigned char bVar1;

  if (pcVar2[1] == 0) {
    goto fatal_20e;
  }

  *(volatile unsigned int *)(puVar3 + 0x143) = param_2;
  *(volatile unsigned int *)(puVar3 + 0x144) = param_1;
  pcVar2[2] = 1;

  if (pcVar2[3] == 0) {
    if (pcVar2[0] == 0) {
      goto fatal_eb;
    }
    *(volatile unsigned int *)(puVar3 + 0x41) = 0;
    *(volatile unsigned int *)((volatile unsigned char *)p504 + 0x504) = 0x200;
    if (puVar3[0x40] != 0) {
      *(volatile unsigned int *)(puVar3 + 1) = 1;
      *(volatile unsigned int *)((volatile unsigned char *)p504 + 0x508) = 0x200;
      return;
    }
  } else if (pcVar2[3] == 4) {
    pcVar2[0] = 1;
    *(volatile unsigned int *)(puVar3 + 0x41) = 0;
    *(volatile unsigned int *)(puVar3 + 0x80) = 1;
    *(volatile unsigned int *)puVar3 = 1;
    return;
  } else {
    if (pcVar2[0] == 0) {
      goto fatal_fe;
    }
    bVar1 = pcVar2[4];
    *(volatile unsigned int *)(puVar3 + 0x41) = 0;
    if ((unsigned char)(bVar1 - 2) < 2) {
      *(volatile unsigned int *)((volatile unsigned char *)p150 + 0x150) = 0;
      *(volatile unsigned int *)(puVar3 + 0x147) = 3;
    }
    *(volatile unsigned int *)((volatile unsigned char *)puVar3 + 0x84) = 0x80000005;
    *(volatile unsigned int *)((volatile unsigned char *)p504 + 0x504) = 0x200;
  }
  return;

fatal_fe:
  sdc_assertion_fail(0x3c, 0xfe);
  return;
fatal_20e:
  sdc_assertion_fail(0x3c, 0x20e);
  return;
fatal_eb:
  sdc_assertion_fail(0x3c, 0xeb);
  return;
}
