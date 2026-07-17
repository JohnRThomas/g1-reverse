/* readable reconstruction; identity: FUN_01019160 @ 0x01019160
 * public-name: FUN_01019160
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01019160 @ 0x1019160  (parity 300 trials PROVEN) */

void FUN_01019160(unsigned char *param_1)
{
  volatile unsigned char * const base = (volatile unsigned char *)0x21000f90;
  unsigned char b0 = param_1[0];
  unsigned int uVar4 = (unsigned int)b0;
  unsigned int uVar3;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned char bTmp;

  if ((b0 & 1) == 0) {
    uVar6 = 1;
    uVar3 = 0;
  } else {
    bTmp = param_1[1];
    uVar6 = 2;
    base[0x54] = bTmp;
    base[0xbd] = 1;
    uVar3 = 1;
    if (bTmp == 3) {
      *(volatile unsigned int *)(base + 0x50) = 0;
    }
  }

  uVar5 = b0 & 1;

  if ((int)(uVar4 << 0x1e) < 0) {
    bTmp = param_1[2];
    if (bTmp == 3) {
      *(volatile unsigned int *)(base + 0x50) = 0;
    }
    base[0x54] = bTmp;
    *(base + uVar3 + 0xbd) = 2;
    uVar5 = uVar6;
  }

  if ((int)(uVar4 << 0x1d) < 0) {
    bTmp = param_1[3];
    if (bTmp == 3) {
      *(volatile unsigned int *)(base + 0x50) = 0;
    }
    base[0x54] = bTmp;
    *(base + uVar5 + 0xbd) = 8;
  }

  base[0x44] = param_1[4];
  bTmp = param_1[5];
  base[0x55] = bTmp;
  base[0x4d] = ((bTmp & 0xfd) == 0) ? 1 : 0;
  base[0x4c] = param_1[6];
  base[0x57] = param_1[7];
}
