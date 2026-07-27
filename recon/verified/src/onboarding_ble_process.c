/* Reconstructed onboarding_ble_process @ 0x42a64  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern void DEBUG_PRINT(unsigned long, ...);
extern u32 FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern u32 FUN_0002eb40(void);
extern void FUN_00040708(void);
extern u64 FUN_0007d382(void);
extern void thunk_FUN_00043308(void);
extern void update_persist_task_status(u32,u32,u32);

u32 onboarding_ble_process(u32 param_1, u32 param_2, u32 param_3, u32 param_4)
{
  u8 cVar1;
  u32 uVar4;
  u64 uVar9;
  u32 ctx;
  u32 puVar6;

  if (0x17 < *(volatile u8*)(param_3 + 1)) {
    if (0 < *(volatile int*)0x2000230cUL) {
      if (*(volatile int*)0x20007554UL == 0) {
        DEBUG_PRINT(0x000aa611UL, 0x000aa778UL,
                    (u32)*(volatile u8*)(param_3+1));
      } else {
        FUN_00019c70(0x000aa611UL, 0x000aa778UL,
                     (u32)*(volatile u8*)(param_3+1));
      }
    }
    *(volatile u16*)(param_4) = *(volatile u16*)(param_3);
    *(volatile u8*)(param_4+2) = 0xca;
    return 3;
  }

  *(volatile u8*)0x20004bf0UL = 0;
  uVar9 = FUN_0007d382();
  cVar1 = *(volatile u8*)(param_3 + 1);
  *(volatile u64*)(0x20004bf0UL + 8) = uVar9;
  if (cVar1 == 0x12) goto LAB_tail;

  FUN_00040708();
  ctx = *(volatile u32*)(param_1 + 0x1014);
  *(volatile u8*)ctx = 1;
  uVar9 = FUN_0007d382();
  ctx = *(volatile u32*)(param_1 + 0x1014);
  *(volatile u32*)(ctx + 4) = (u32)uVar9;
  *(volatile u32*)(ctx + 8) = (u32)(uVar9 >> 32);
  ctx = *(volatile u32*)(param_1 + 0x1014);
  *(volatile u8*)(ctx + 2) = *(volatile u8*)(param_3 + 1);

  if (2 < *(volatile int*)0x2000230cUL) {
    ctx = *(volatile u32*)(param_1 + 0x1014);
    if (*(volatile int*)0x20007554UL == 0) {
      DEBUG_PRINT(0x000aa63dUL, 0x000aa778UL,
                  (u32)*(volatile u8*)(ctx+2));
    } else {
      FUN_00019c70(0x000aa63dUL, 0x000aa778UL,
                   (u32)*(volatile u8*)(ctx+2));
    }
  }

  ctx = *(volatile u32*)(param_1 + 0x1014);
  switch (*(volatile u8*)(ctx + 2)) {
  case 1:
    *(volatile u8*)(ctx + 1) = 1;
    ctx = *(volatile u32*)(param_1 + 0x1014);
    puVar6 = 0x000aa661UL;
    goto LAB_00042b1c;
  case 2:
    puVar6 = 0x000aa665UL;
    goto LAB_00042b1c;
  case 3:
    *(volatile u32*)(ctx + 0x1b) = *(volatile u32*)0x000aa669UL;
    *(volatile u8*)0x2001cdcfUL = 0;
    *(volatile u8*)0x2001cdceUL = 0;
    *(volatile u8*)(ctx + 3) = 0;
    *(volatile u8*)(ctx + 0xd) = 0;
    *(volatile u8*)(ctx + 0xe) = 0;
    *(volatile u8*)(ctx + 0xf) = 0;
    *(volatile u8*)(ctx + 0x10) = 0;
    *(volatile u8*)(ctx + 0x11) = 0;
    *(volatile u8*)(ctx + 0x12) = 0;
    *(volatile u8*)(ctx + 0x13) = 0;
    *(volatile u8*)(ctx + 0x14) = 0;
    *(volatile u8*)(ctx + 0x15) = 0;
    *(volatile u8*)(ctx + 0x16) = 0;
    *(volatile u8*)(ctx + 0x17) = 0;
    *(volatile u8*)(ctx + 0x18) = 0;
    *(volatile u8*)(ctx + 0x19) = 0;
    *(volatile u8*)(ctx + 0x1a) = 0;
    *(volatile u8*)(ctx + 0xc) = 0;
    break;
  case 4:
  case 5:
  case 6:
    *(volatile u32*)(ctx + 0x1b) = *(volatile u32*)0x000aa66dUL;
    *(volatile u8*)0x2001cdd2UL = 0;
    *(volatile u8*)0x2001cdceUL = 0;
    uVar4 = FUN_000167a8();
    *(volatile u8*)(ctx + 3) = *(volatile u8*)(uVar4 + 0xee4);
    if (*(volatile u8*)(ctx + 2) == 6) {
      *(volatile u8*)(ctx + 0x1f) = 0;
    }
    break;
  case 7:
    puVar6 = 0x000aa671UL;
    goto LAB_00042b1c;
  case 8:
  case 9:
    puVar6 = 0x000aa66dUL;
    goto LAB_00042b1c;
  case 10:
  case 11:
    *(volatile u8*)ctx = 0;
    *(volatile u8*)(ctx + 1) = 0;
    break;
  case 12:
    *(volatile u8*)(ctx + 1) = 1;
    ctx = *(volatile u32*)(param_1 + 0x1014);
    puVar6 = 0x000aa675UL;
LAB_00042b1c:
    *(volatile u32*)(ctx + 0x1b) = *(volatile u32*)puVar6;
    break;
  case 15:
  case 17: {
    u32 t1 = FUN_000167a8();
    u32 t2 = FUN_000167a8();
    ctx = *(volatile u32*)(t2 + 0x1014);
    *(volatile u8*)(ctx + 3) = *(volatile u8*)(t1 + 0xee4);
    break;
  }
  default:
    break;
  }
  thunk_FUN_00043308();

LAB_tail:
  if (*(volatile u16*)(param_2 + 2) == 2) {
    uVar4 = 3;
    *(volatile u16*)(param_4) = *(volatile u16*)(param_3);
    *(volatile u8*)(param_4+2) = 0xc9;
  } else if (*(volatile u16*)(param_2 + 2) == 3) {
    u8 uVar2;
    *(volatile u16*)(param_4) = *(volatile u16*)(param_3);
    *(volatile u8*)(param_4+2) = 0xc9;
    uVar2 = *(volatile u8*)(param_3 + 2);
    *(volatile u8*)(param_4+3) = uVar2;
    if (*(volatile u8*)(*(volatile u32*)(param_1 + 0x1014)) != 0) {
      *(volatile u8*)(param_1 + 0xcd) = uVar2;
    }
    uVar4 = 4;
  } else {
    uVar4 = 0;
  }

  if (*(volatile u8*)(param_3 + 1) != 0x12) {
    u32 t1 = FUN_000167a8();
    u32 p = *(volatile u32*)(t1 + 0x1054);
    if (*(volatile u32*)p != 0xe) {
      if (FUN_0002eb40() == 0) {
        u32 t2 = FUN_000167a8();
        update_persist_task_status(t2, 0xe, 2);
        {
          u32 t3 = FUN_000167a8();
          u32 t4 = FUN_000167a8();
          ctx = *(volatile u32*)(t4 + 0x1014);
          *(volatile u8*)(ctx + 0x20) = *(volatile u8*)(t3 + 0xed5);
          {
            u32 t5 = FUN_000167a8();
            *(volatile u8*)(t5 + 0xed5) = 0x2a;
          }
        }
      }
    }
  }

  return uVar4;
}
