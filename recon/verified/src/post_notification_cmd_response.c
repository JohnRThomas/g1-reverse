/* Reconstructed post_notification_cmd_response @ 0x340c4  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(int,...);
extern void FUN_00019c70(int,...);
extern void FUN_0003384c(int);
extern void FUN_00033f54(int);
extern int  FUN_00034bd4(int);
extern void FUN_0008705a(int,int,int);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))
#define VH(a) (*(volatile unsigned short*)(a))

int post_notification_cmd_response(int param_1,int param_2,int param_3,int param_4,int param_5,int *param_6){
  volatile int *lvl=(volatile int*)0x2000230cUL, *g8=(volatile int*)0x20007554UL;
  int iVar5, format;
  if (param_1==0||param_2==0||param_3==0||param_4==0||param_5==0||param_6==0) {
    if (1 < *lvl) { if(*g8==0) DEBUG_PRINT(0xa7ef6,0xa831f,param_5,0,param_1,param_2,param_3); else FUN_00019c70(0); }
    return 0;
  }
  if (2 < *lvl) { if(*g8==0) DEBUG_PRINT(0xa7f12,0xa831f,VB(param_4+1),0,param_1,param_2,param_3); else FUN_00019c70(0); }
  if (VB(param_4+1) == 4) {
    FUN_0008705a(VI(param_1+0xff8)+8, param_2+0x54, 0x10);
    FUN_0008705a(VI(param_1+0xff8)+0x19, param_2+0x94, 0x96);
    { int p3=VI(param_1+0xff8); VB(p3)=0; VB(p3+1)=0; VB(p3+2)=0; VB(p3+3)=0; }
    if (VB(param_1+0xd5)==0) VB(param_1+0xb0d)=1;
    if (2 < *lvl) { if(*g8==0) DEBUG_PRINT(0xa7f41,0xa831f); else FUN_00019c70(0xa7f41); }
  } else {
    if (VH(param_4+2) != 0x1b4) {
      if (*lvl < 1) return 0;
      if (*g8 != 0) { FUN_00019c70(0xa7f79,0xa831f,0xa8300); return 0; }
      DEBUG_PRINT(0xa7f79,0xa831f,0xa8300,0x158,VH(param_4+2),param_2,param_3); return 0;
    }
    if ((unsigned int)VI(param_2+0x1b4) < 2) {
      iVar5 = FUN_00034bd4(param_2+0x14);
      if ((((unsigned int)(iVar5-2)) & 0xff) > 1) { if (iVar5 == 1) FUN_0003384c(param_2+4); }
      else FUN_00033f54(param_2+4);
    } else FUN_00033f54(param_2+4);
  }
  if (VB(param_3+1) == 4) {
    if (*lvl < 3) goto LAB_341a8;
    iVar5 = *g8; format = 0xa7fae;
  } else {
    if (VB(param_3+1) != 6 || *lvl < 3) goto LAB_341a8;
    iVar5 = *g8; format = 0xa7fe3;
  }
  if (iVar5 == 0) DEBUG_PRINT(format,0xa831f); else FUN_00019c70(0);
LAB_341a8:
  { int d=0xa1f49; *(volatile int*)param_6 = VI(d); *(volatile unsigned char*)((int)param_6+4)=VB(d+4); }
  return 5;
}

