/* readable reconstruction; identity: FUN_0100ac98 @ 0x0100ac98
 * public-name: FUN_0100ac98
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_tx_buffer_ready_get           <= FUN_0100a960 @ 0x0100a960
 *   sdc_pdu_type_bits_set                    <= FUN_0100e5dc @ 0x0100e5dc
 * address symbols (name @ address):
 *   g_net_radio_drv_ctx                      @ 0x21000c48
 *   g_ll_conn_empty_pdu_buf                  @ 0x21000c90
 *   g_ll_conn_tx_ctx_addr                    @ 0x21000cc4
 *   g_ll_conn_pdu_hdr_ptr                    @ 0x21000cfc
 */
/* net-core FUN_0100ac98 @ 0x100ac98  (parity 200 trials PROVEN) */
/* net-core FUN_0100ac98 @ 0x100ac98  (parity 300 trials PROVEN) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char i8;

extern void FUN_010202fc(u32, i8);
extern int controller_tx_buffer_ready_get(u32);
extern int FUN_0100a9b0(void);
extern void sdc_pdu_type_bits_set(u32, int);
extern void FUN_0100e8f8(void *, u16);
extern void FUN_0101fe98(u32, u32);
extern void FUN_0101ff4c(void);
extern void sdc_assertion_fail(u32, u32);
extern void FUN_01020368(u32, int);
extern void FUN_01020764(u32);
extern void FUN_010208f0(int, int, u8);
extern void *FUN_01026b58(u32, u16 *, i8 *);
extern int FUN_01026dae(u32);

#define DAT_0100ae9c 0x21000c48u
#define DAT_0100aea0 0x21000cc4u
#define DAT_0100aea4 0x21000c90u
#define DAT_0100aea8 0x21000cfcu

void FUN_0100ac98(int param_1)
{
  volatile u8 *b;
  volatile u16 *h;
  volatile u32 *w;
  u8 bVar2;
  u16 uVar3;
  int iVar4;
  volatile u16 *puVar5;
  int iVar6;
  volatile u8 *pbVar7 = 0;
  u8 bVar8;
  i8 cVar9;
  u32 uVar10;
  int iVar11;
  i8 local_13;
  u16 local_12;
  u8 uVar1;

  iVar4 = DAT_0100ae9c;
  iVar11 = *(volatile int *)(DAT_0100ae9c + 0x28);
  local_13 = 0;
  cVar9 = *(volatile i8 *)(DAT_0100ae9c + 0x7a);
  if (*(volatile i8 *)(iVar11 + 0xcb) != 0) {
    cVar9 = (i8)(cVar9 + 4);
  }
  if ((cVar9 == -1) && (param_1 == 0)) {
    cVar9 = *(volatile i8 *)(iVar11 + 0x6e);
    if (*(volatile i8 *)(iVar11 + 0x6f) != cVar9) goto LAB_0100acca;
  } else {
    cVar9 = *(volatile i8 *)(iVar11 + 0x6e);
LAB_0100acca:
    FUN_010202fc(0xff, cVar9);
  }
  uVar10 = DAT_0100aea0;
  switch (*(volatile u8 *)(iVar11 + 0xbe)) {
  case 0:
    local_12 = (u16)*(volatile u8 *)(iVar4 + 0x7b);
    *(volatile u16 *)(iVar11 + 0x54) = local_12;
    iVar6 = controller_tx_buffer_ready_get(uVar10);
    if (iVar6 != 0) {
      *(volatile u16 *)(iVar4 + 0x32) = *(volatile u16 *)(iVar4 + 0x32) | 0x80;
      ((void (*)(u32, u32))(*(volatile u32 *)(iVar4 + 0x34)))(0x80, *(volatile u32 *)(iVar4 + 0x7c));
      pbVar7 = (volatile u8 *)*(volatile u32 *)(iVar4 + 0x7c);
      *(volatile u8 *)(iVar11 + 0xb9) = 1;
      bVar2 = pbVar7[3];
      goto joined_r0x0100adce;
    }
    puVar5 = (volatile u16 *)FUN_01026b58(*(volatile u32 *)(iVar4 + 0x80), &local_12, &local_13);
    *(volatile u32 *)(iVar4 + 0x7c) = (u32)(unsigned long)puVar5;
    if ((puVar5 == (volatile u16 *)0) || (*(volatile i8 *)(iVar11 + 0x105) != 0))
      goto switchD_0100acd8_caseD_1;
    if (local_13 == 0) {
      *puVar5 = 0;
      *(volatile u8 *)((u8 *)(void *)puVar5 + 2) = 0;
      sdc_pdu_type_bits_set(*(volatile u32 *)(iVar4 + 0x7c), 1);
      puVar5 = (volatile u16 *)*(volatile u32 *)(iVar4 + 0x7c);
    }
    FUN_0100e8f8((void *)puVar5, local_12);
    pbVar7 = (volatile u8 *)*(volatile u32 *)(iVar4 + 0x7c);
    break;
  case 1:
switchD_0100acd8_caseD_1:
    pbVar7 = (volatile u8 *)DAT_0100aea4;
    *(volatile u32 *)(iVar4 + 0x7c) = DAT_0100aea4;
    break;
  case 2:
    local_12 = *(volatile u16 *)(iVar11 + 0x54);
    pbVar7 = (volatile u8 *)FUN_01026b58(*(volatile u32 *)(iVar4 + 0x80), &local_12, &local_13);
    *(volatile u32 *)(iVar4 + 0x7c) = (u32)(unsigned long)pbVar7;
    if (pbVar7 == (volatile u8 *)0) {
      sdc_assertion_fail(0x27, 0x2e9);
    }
    break;
  case 3:
    iVar6 = controller_tx_buffer_ready_get(DAT_0100aea0);
    if (iVar6 == 0) {
      sdc_assertion_fail(0x27, 0x2f2);
    }
    pbVar7 = (volatile u8 *)*(volatile u32 *)(iVar4 + 0x7c);
    bVar2 = pbVar7[3];
joined_r0x0100adce:
    if (bVar2 == 0x1b) {
      FUN_01020368(iVar11 + 0x10, 1);
      pbVar7 = (volatile u8 *)*(volatile u32 *)(iVar4 + 0x7c);
    }
    break;
  default:
    sdc_assertion_fail(0x27, 0x2ff);
  }
  bVar2 = *pbVar7;
  bVar8 = (u8)((bVar2 & 0xe3) | ((*(volatile u8 *)(iVar11 + 0xbf) & 1) << 3) |
               ((*(volatile u8 *)(iVar11 + 0xc0) & 1) << 2));
  *pbVar7 = bVar8;
  if (((bVar2 & 3) == 3) && (pbVar7[3] == 2)) goto LAB_0100ad76;
  iVar6 = FUN_01026dae(*(volatile u32 *)(iVar4 + 0x80));
  if (iVar6 == 0) {
    pbVar7 = (volatile u8 *)*(volatile u32 *)(iVar4 + 0x7c);
    bVar8 = *pbVar7;
    if ((bVar8 & 3) == 3) goto LAB_0100ad76;
    iVar6 = FUN_0100a9b0();
    if (iVar6 != 0) {
      pbVar7 = (volatile u8 *)*(volatile u32 *)(iVar4 + 0x7c);
      bVar8 = *pbVar7;
      goto LAB_0100ad76;
    }
  }
  pbVar7 = (volatile u8 *)*(volatile u32 *)(iVar4 + 0x7c);
  bVar8 = *pbVar7 | 0x10;
LAB_0100ad76:
  *pbVar7 = bVar8;
  if ((*(volatile i8 *)(iVar11 + 0xca) == 0) || (pbVar7[1] == 0)) {
    FUN_01020764((u32)(unsigned long)pbVar7);
    FUN_0101ff4c();
  } else {
    FUN_01020764(*(volatile u32 *)(iVar4 + 0x84));
    uVar10 = *(volatile u32 *)(iVar11 + 0x124);
    *(volatile u32 *)(iVar4 + 0x98) = *(volatile u32 *)(iVar11 + 0x120);
    *(volatile u32 *)(iVar4 + 0x9c) = uVar10;
    *(volatile u8 *)(iVar4 + 0xa0) = (*(volatile i8 *)(iVar4 + 0x24) == 0);
    FUN_0101fe98(*(volatile u32 *)(iVar4 + 0x84), *(volatile u32 *)(iVar4 + 0x7c));
  }
  if (*(volatile u32 *)(iVar11 + 0x14) < 0x1d4c) {
    FUN_010208f0(1, 1, *(volatile u8 *)(iVar11 + 0x6f));
  } else {
    FUN_010208f0(0, 1, *(volatile u8 *)(iVar11 + 0x6f));
  }
  iVar11 = DAT_0100aea8;
  {
    volatile u16 *pp = (volatile u16 *)*(volatile u32 *)(iVar4 + 0x7c);
    uVar3 = *pp;
    uVar1 = *((volatile u8 *)pp + 2);
  }
  *(volatile u8 *)(iVar4 + 0xb0) = 1;
  *(volatile u16 *)(iVar4 + 0xb4) = uVar3;
  *(volatile u8 *)(iVar4 + 0x44) = 1;
  *(volatile u8 *)(iVar11 + 2) = uVar1;
}
