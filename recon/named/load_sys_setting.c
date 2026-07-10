/* named: load_sys_setting */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20002fe3  g_product_code_buf           
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed load_sys_setting @ 0x22bd0  (parity: 300/300 trials, PROVEN) */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int undefined4;

extern void DEBUG_PRINT(u32 fmt, ...);
extern void debug_print(void);
extern int flash_settings_read(u32 a, void *b, u32 c);
extern void build_and_send_device_status_report(int a);
extern void memset_bytes(void *a, int b, u32 c);

undefined4 load_sys_setting(int param_1)
{
  const unsigned long BUF = 0x2007EF60UL;
  volatile int  *sp4  = (volatile int*)(BUF+4);
  volatile u8   *spC  = (volatile u8*)(BUF+0xc);
  volatile u32  *sp10 = (volatile u32*)(BUF+0x10);
  volatile u32  *sp14 = (volatile u32*)(BUF+0x14);
  volatile u8   *sp18 = (volatile u8*)(BUF+0x18);
  volatile u8   *sp19 = (volatile u8*)(BUF+0x19);
  volatile u8   *sp39 = (volatile u8*)(BUF+0x39);
  volatile u8   *sp59 = (volatile u8*)(BUF+0x59);
  volatile u8   *sp5a = (volatile u8*)(BUF+0x5a);
  volatile u16  *sp64 = (volatile u16*)(BUF+0x64);
  volatile u16  *sp66 = (volatile u16*)(BUF+0x66);
  volatile u32  *sp6c = (volatile u32*)(BUF+0x6c);
  volatile u32  *sp68 = (volatile u32*)(BUF+0x68);
  volatile u32  *sp70 = (volatile u32*)(BUF+0x70);
  volatile u32  *sp74 = (volatile u32*)(BUF+0x74);
  volatile u32  *sp80 = (volatile u32*)(BUF+0x80);
  volatile u32  *sp84 = (volatile u32*)(BUF+0x84);
  volatile u16  *sp78 = (volatile u16*)(BUF+0x78);
  volatile u16  *sp7a = (volatile u16*)(BUF+0x7a);
  volatile u16  *sp7c = (volatile u16*)(BUF+0x7c);

  volatile int *DAT_db8 = (volatile int*)0x2000230cUL;
  volatile int *DAT_dbc = (volatile int*)0x20007554UL;
  volatile u32 *DAT_dcc = (volatile u32*)0x20003003UL;
  volatile u32 *DAT_dd0 = (volatile u32*)0x20002fe3UL;

  int iVar2;
  int i;

  memset_bytes((void*)(BUF+4), 0, 0x84);
  iVar2 = flash_settings_read(0x130000u, (void*)(BUF+4), 0x84u);

  if (iVar2 != 0) {
    if (1 < *DAT_db8) {
      if (*DAT_dbc == 0) { DEBUG_PRINT(0x9e580u, 0x9e7c9u); }
      else { debug_print(); }
    }
    return 0xffffffffu;
  }
  if (1 < *DAT_db8) {
    if (*DAT_dbc == 0) { DEBUG_PRINT(0x9e5a6u, 0x9e7c9u); }
    else { debug_print(); }
  }
  *(u32*)(long)(param_1 + 0x1050) = (u32)*sp4;
  *(volatile u8*)(long)(param_1 + 2) = *spC;
  *(u32*)(long)(param_1 + 0xf64) = *sp10;
  *(u32*)(long)(param_1 + 0xf94) = *sp14;
  *(volatile u8*)(long)(param_1 + 0xed4) = *sp18;

  if (*sp19 != 0xff) {
    for (i = 0; i < 4; i++) {
      *(DAT_dcc + i) = *(volatile u32*)(BUF + 0x19 + (unsigned)i*4);
    }
  }
  if (*sp39 != 0xff) {
    for (i = 0; i < 4; i++) {
      *(DAT_dd0 + i) = *(volatile u32*)(BUF + 0x39 + (unsigned)i*4);
    }
  }

  *(volatile u8*)(long)(param_1 + 3) = *sp59;
  *(volatile u8*)(long)(param_1 + 4) = *sp5a;
  *(u16*)(long)(param_1 + 0x1072) = *sp64;
  *(u16*)(long)(param_1 + 0x1074) = *sp66;
  *(u32*)(long)(param_1 + 4000) = *sp6c;
  *(u32*)(long)(param_1 + 0xfa4) = *sp68;
  *(u32*)(long)(param_1 + 0xfa8) = *sp70;
  *(u32*)(long)(param_1 + 0xfac) = *sp74;
  *(u32*)(long)(param_1 + 0xfb0) = *sp80;
  *(u32*)(long)(param_1 + 0xfb4) = *sp84;
  *(u16*)(long)(param_1 + 0xeda) = *sp78;
  *(u16*)(long)(param_1 + 0xedc) = *sp7a;
  *(u16*)(long)(param_1 + 0xede) = *sp7c;

  if (*sp4 != 1) {
    if (1 < *DAT_db8) {
      if (*DAT_dbc == 0) { DEBUG_PRINT(0x9e5c8u, 0x9e7c9u); }
      else { debug_print(); }
    }
    *(volatile u8*)(long)(param_1 + 2) = 0xff;
    *(u32*)(long)(param_1 + 0xf94) = 0x00013880u;
    *(u32*)(long)(param_1 + 0xf64) = 0;
    *(volatile u8*)(long)(param_1 + 0xed4) = 0;
    *(u16*)(long)(param_1 + 0x1072) = 0x20;
    *(u16*)(long)(param_1 + 0x1074) = 0x20;
    *(u32*)(long)(param_1 + 0xfb0) = 0x1f400;
    *(u16*)(long)(param_1 + 0xeda) = 0x3f;
    *(u32*)(long)(param_1 + 4000) = 0;
    *(u32*)(long)(param_1 + 0xfa4) = 0;
    *(u32*)(long)(param_1 + 0xfa8) = 0;
    *(u32*)(long)(param_1 + 0xfac) = 0;
    *(u32*)(long)(param_1 + 0xfb4) = 0;
    *(u32*)(long)(param_1 + 0xedc) = 0x3f003f;
    build_and_send_device_status_report(param_1);
  }

  *(u32*)(long)(param_1 + 0x1050) = 1;
  if (*(volatile u8*)(long)(param_1 + 0xed4) != 1) {
    *(volatile u8*)(long)(param_1 + 0xed4) = 0;
  }
  {
    u32 uVar9 = (u32)(*(u32*)(long)(param_1 + 0xfb0)) + 1;
    u32 uVar10 = uVar9;
    if (uVar9 < 2) uVar10 = 0x1f400;
    if (uVar9 < 2) *(u32*)(long)(param_1 + 0xfb0) = uVar10;
  }
  {
    u16 uVar4 = (u16)(*(u16*)(long)(param_1 + 0x1072) - 0x16);
    u16 uVar5 = uVar4;
    if (0x14 < uVar4) uVar5 = 0x20;
    if (0x14 < uVar4) *(u16*)(long)(param_1 + 0x1072) = uVar5;
  }
  if (*(u16*)(long)(param_1 + 0x1074) < 0x41) {
    if (3 < *(u16*)(long)(param_1 + 0x1074)) {
      goto LAB_d8a;
    }
    *(u16*)(long)(param_1 + 0x1074) = 4;
  } else {
    *(u16*)(long)(param_1 + 0x1074) = 0x20;
  }
LAB_d8a:
  if (0x3e < (u16)(*(u16*)(long)(param_1 + 0xede) - 1)) {
    *(u16*)(long)(param_1 + 0xede) = 0x3f;
  }
  return 0;
}

