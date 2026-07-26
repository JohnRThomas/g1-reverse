/* net-core FUN_0101ff4c @ 0x101ff4c  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

volatile unsigned char * const DAT_0101ff90 = (volatile unsigned char *)0x210014dc;
volatile unsigned int * const DAT_0101ff94 = (volatile unsigned int *)G1_NRF_AAR_NS_BASE;
volatile unsigned int * const DAT_0101ff98 = (volatile unsigned int *)G1_NRF_DPPIC_NS_BASE;

void FUN_0101ff4c(void)
{
  volatile unsigned char *pcVar1 = DAT_0101ff90;
  volatile unsigned int *iVar2 = DAT_0101ff94;
  volatile unsigned int *iVar3 = DAT_0101ff98;

  if (*pcVar1 != 0) {
    *(volatile unsigned int *)((char*)iVar2 + 0x84) = 0;
    *(volatile unsigned int *)((char*)iVar3 + 0x508) = 0x200;
    *(volatile unsigned int *)((char*)iVar2 + 0x180) = 0;
    *(volatile unsigned int *)((char*)iVar2 + 0x84) = 0;
    *(volatile unsigned int *)((char*)iVar3 - 0x7000 + 0x1d0) = 0;
    *(volatile unsigned int *)((char*)iVar2 + 0x8c) = 0;
    *pcVar1 = 0;
    *(volatile unsigned short *)(pcVar1 + 1) = 0;
    return;
  }
  *(volatile unsigned short *)(pcVar1 + 1) = 0;
}

