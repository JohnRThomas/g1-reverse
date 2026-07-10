/* named: opt_record_decode */
/* Reconstructed opt_record_decode @ 0x7c4f4  (parity: 300/300 trials, PROVEN) */
extern int opt_record_init(unsigned char*);
unsigned opt_record_decode(int *param_1, unsigned char *param_2){
  unsigned char bVar1;
  unsigned uVar3, uVar4, uVar5, uVar6, uVar7;
  volatile unsigned char *pb = param_2;
  if (param_1 == 0 || *param_1 == 0 || param_2 == 0) return 7;
  if (opt_record_init(param_2) != 0) return 0xc;
  if (param_1[1] == 0) return 0xb;
  bVar1 = *(unsigned char*)*param_1;
  pb[0] = bVar1;
  if ((unsigned)param_1[1] < 2) return 0xb;
  uVar3 = *(unsigned char*)(*param_1 + 1);
  pb[1] = *(unsigned char*)(*param_1 + 1);
  if ((bVar1 & 0x10) == 0){
    if ((unsigned)param_1[1] < 6) return 0xb;
    uVar6 = 6;
    uVar4 = *(unsigned*)(*param_1 + 2);
    uVar4 = uVar4<<0x18 | ((uVar4>>8)&0xff)<<0x10 | ((uVar4>>0x10)&0xff)<<8 | uVar4>>0x18;
  } else {
    if ((unsigned)param_1[1] < 3) return 0xb;
    uVar6 = 3;
    uVar4 = *(unsigned char*)(*param_1 + 2);
  }
  uVar5 = bVar1 & 8;
  *(volatile unsigned*)(param_2 + 0x10) = uVar4;
  if ((bVar1 & 8) == 0){
    pb[2] = (unsigned char)uVar5;
    if (uVar3 == 0){
      *(volatile unsigned*)(param_2 + 4) = 0;
      uVar5 = 0;
      goto LAB_c552;
    }
   LAB_c58a:
    uVar7 = uVar3 + uVar6;
    if ((unsigned)param_1[1] < uVar7) return 0xb;
    uVar3 = *param_1 + uVar6;
  } else {
    uVar7 = uVar6 + 1;
    if ((unsigned)param_1[1] < uVar7) return 0xb;
    uVar5 = *(unsigned char*)(*param_1 + uVar6);
    pb[2] = *(unsigned char*)(*param_1 + uVar6);
    uVar6 = uVar7;
    if (uVar3 != 0) goto LAB_c58a;
  }
  *(volatile unsigned*)(param_2 + 4) = uVar3;
  uVar6 = uVar7;
  if (uVar5 != 0){
    uVar6 = uVar5 + uVar7;
    if ((unsigned)param_1[1] < uVar6) return 0xb;
    uVar5 = *param_1 + uVar7;
  }
 LAB_c552:
  *(volatile unsigned*)(param_2 + 8) = uVar5;
  if (uVar4 != 0){
    if ((unsigned)param_1[1] < uVar4 + uVar6) return 0xb;
    uVar4 = *param_1 + uVar6;
  }
  *(volatile unsigned*)(param_2 + 0xc) = uVar4;
  *(volatile unsigned*)(param_2 + 0x18) = 0;
  return 0;
}

