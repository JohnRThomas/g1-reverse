/* readable reconstruction; identity: FUN_0100f1a8 @ 0x0100f1a8
 * public-name: FUN_0100f1a8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100f1a8 @ 0x100f1a8  (parity 300 trials PROVEN) */
/* net-core FUN_0100f1a8 @ 0x100f1a8  (parity 300 trials PROVEN) */
/* net-core FUN_0100f1a8 @ 0x100f1a8  (parity 300 trials PROVEN) */

void FUN_0100f1a8(int param_1, int param_2)
{
  volatile unsigned short *p16;
  volatile unsigned int *p32;
  p16 = (volatile unsigned short *)(param_1 + 0x20); *p16 = 0x1b;
  p16 = (volatile unsigned short *)(param_1 + 0x1c); *p16 = 0x1b;
  p32 = (volatile unsigned int *)(param_1 + 0x14); *p32 = 0x1b001b;
  p16 = (volatile unsigned short *)(param_1 + 0x10); *p16 = 0x1b;
  p32 = (volatile unsigned int *)(param_1 + 8); *p32 = 0x1b001b;
  p32 = (volatile unsigned int *)(param_1 + 0x2a); *p32 = 0x1b001b;
  p16 = (volatile unsigned short *)(param_1 + 0x24); *p16 = 0x1b;
  if (param_2 == 0) {
    p16 = (volatile unsigned short *)(param_1 + 0x22); *p16 = 0x148;
    p16 = (volatile unsigned short *)(param_1 + 0x1e); *p16 = 0x148;
    p32 = (volatile unsigned int *)(param_1 + 0x18); *p32 = 0x01480148;
    p16 = (volatile unsigned short *)(param_1 + 0x12); *p16 = 0x148;
    p32 = (volatile unsigned int *)(param_1 + 0xc); *p32 = 0x01480148;
    p32 = (volatile unsigned int *)(param_1 + 0x2e); *p32 = 0x01480148;
    return;
  }
  p16 = (volatile unsigned short *)(param_1 + 0x22); *p16 = 0xa90;
  p16 = (volatile unsigned short *)(param_1 + 0x1e); *p16 = 0xa90;
  p32 = (volatile unsigned int *)(param_1 + 0x18); *p32 = 0x0a900a90;
  p16 = (volatile unsigned short *)(param_1 + 0x12); *p16 = 0x148;
  p32 = (volatile unsigned int *)(param_1 + 0xc); *p32 = 0x0a900a90;
  p32 = (volatile unsigned int *)(param_1 + 0x2e); *p32 = 0x0a900a90;
}
