/* readable reconstruction; identity: FUN_010198cc @ 0x010198cc
 * public-name: FUN_010198cc
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_work_submit                          <= FUN_0100ef88 @ 0x0100ef88
 *   sdc_buffer_elapsed_units_get             <= FUN_01026d3e @ 0x01026d3e
 *   sdc_buffer_accumulate                    <= FUN_01026f32 @ 0x01026f32
 *   sdc_buffer_payload_get                   <= FUN_010270d2 @ 0x010270d2
 *   sdc_buffer_descriptor_resolve            <= FUN_0102714a @ 0x0102714a
 */
/* net-core FUN_010198cc @ 0x10198cc  (parity 300 trials PROVEN) */
extern void sdc_assertion_fail(unsigned int, unsigned int);
extern unsigned int FUN_0100a5a0(void);
extern unsigned int FUN_0100a5b4(void);
extern int FUN_0100ca98(unsigned int, int);
extern void sdc_work_submit(int, unsigned int, unsigned int);
extern int sdc_buffer_elapsed_units_get(void);
extern int sdc_buffer_accumulate(unsigned int, unsigned short, unsigned int);
extern int sdc_buffer_payload_get(unsigned int);
extern void sdc_buffer_descriptor_resolve(unsigned int, unsigned int *, unsigned char *);

#define DAT_010199c8 0x01019a9du

void FUN_010198cc(int param_1, int param_2, unsigned char param_3, unsigned char param_4,
                   unsigned char param_5)
{
  unsigned short uVar1;
  unsigned int uVar2;
  int iVar3;
  int iVar4;
  unsigned int *puVar5;
  unsigned char auStack_26[2];
  unsigned int local_24[2];

  uVar2 = FUN_0100a5a0();
  iVar3 = sdc_buffer_elapsed_units_get();
  if (iVar3 == 1) {
    return;
  }
  sdc_buffer_descriptor_resolve(uVar2, local_24, auStack_26);
  iVar3 = sdc_buffer_payload_get(local_24[0]);
  *(volatile unsigned int *)(long)(iVar3 + 0x12) = 0;
  *(volatile unsigned int *)(long)(iVar3 + 0x16) = 0;
  *(volatile unsigned int *)(long)(iVar3 + 0x1a) = 0;
  *(volatile unsigned int *)(long)(iVar3 + 0x1e) = 0;
  *(volatile unsigned int *)(long)(iVar3 + 0x22) = 0;
  *(volatile unsigned int *)(long)(iVar3 + 0x26) = 0;
  *(volatile unsigned int *)(long)(iVar3 + 0x2a) = 0;
  *(volatile unsigned char *)(long)(iVar3 + 0x12) = 1;
  if (param_2 == 0xff) {
    *(volatile unsigned char *)(long)(iVar3 + 0x13) = *(volatile unsigned char *)(long)(param_1 + 0x11);
    puVar5 = *(unsigned int **)(long)(param_1 + 4);
    *(volatile unsigned int *)(long)(iVar3 + 0x14) = *puVar5;
    *(volatile unsigned short *)(long)(iVar3 + 0x18) = *(unsigned short *)(puVar5 + 1);
  } else {
    iVar4 = FUN_0100ca98((unsigned int)param_2, iVar3 + 0x13);
    if (iVar4 == 0) {
      sdc_assertion_fail(0x33, 0xe6);
      __builtin_unreachable();
    }
    *(volatile unsigned char *)(long)(iVar3 + 0x13) = *(volatile unsigned char *)(long)(iVar3 + 0x13) | 2;
  }
  *(volatile unsigned char *)(long)(iVar3 + 0x2d) = param_4;
  *(volatile unsigned char *)(long)(iVar3 + 0x1b) = param_5;
  *(volatile unsigned char *)(long)(iVar3 + 0x20) = 0xff;
  *(volatile unsigned char *)(long)(iVar3 + 0x25) = 0xff;
  *(volatile unsigned char *)(long)(iVar3 + 0x1c) =
      (param_3 & 0x1b) | 0x1a | (*(volatile unsigned char *)(long)(iVar3 + 0x1c) & 0xe4);
  *(volatile unsigned char *)(long)(iVar3 + 0x2c) = 0x7f;
  *(volatile unsigned short *)(long)(iVar3 + 0x1e) = 1;
  uVar2 = FUN_0100a5a0();
  uVar1 = (unsigned short)FUN_0100a5b4();
  iVar4 = sdc_buffer_accumulate(uVar2, uVar1, 1);
  uVar2 = DAT_010199c8;
  if (iVar4 != 0) {
    *(volatile unsigned char *)(long)(iVar3 + 8) = 0;
    sdc_work_submit(iVar3, uVar2, 6);
    return;
  }
  sdc_assertion_fail(0x33, 0x361);
  __builtin_unreachable();
}
