/* Reconstructed FUN_0005a724 @ 0x5a724  (parity: 300/300 trials, PROVEN) */
extern int  FUN_00059b5c(int,void*);
extern int  FUN_00059c04(void);
extern int  FUN_0005a39c(int);
extern int  FUN_00077c1c(int,int,int);
extern void FUN_0007f1e8(int,int*);
extern int  FUN_00080cf2(int,void*);
extern void FUN_000828da(int,void*);
extern void FUN_00082a42(int,int,void*);
extern void FUN_00082b98(int,int);
extern void FUN_00082bb8(int,int);
#define VB(a) (*(volatile unsigned char*)(a))

struct discovery_frame {
  unsigned char decoded[2];
  unsigned char decoded_pad[2];
  int identity;
  unsigned char address[24];
  struct { unsigned level, message; } log;
  unsigned char compiler_frame_pad[8];
};

int FUN_0005a724(int param_1,int param_2,int param_3,int param_4){
  int iVar1, puVar2;
  struct discovery_frame frame;
  if (param_1 == 0) {
    frame.log.level = 2;
    frame.log.message = 0x000f2b65;
    FUN_00082a42(0x00088128, 0x1040, &frame.log);
    return -0x16;
  }
  iVar1 = FUN_00080cf2(param_1, frame.address);
  if (iVar1 != 0) {
    struct { unsigned type, message; int value; unsigned short flags; } log = {
      0x01000003, 0x000f472a, param_1, 0x200
    };
    FUN_00082a42(0x00088128, 0x1c40, &log);
    return -0x16;
  }
  FUN_0007f1e8(param_1, &frame.identity);
  if (frame.identity != 0 && (iVar1 = FUN_00077c1c(frame.identity, 0, 10)) != 0) {
    struct { unsigned level, message; int error; } log = { 3, 0x000f4746, iVar1 };
    FUN_00082a42(0x00088128, 0x1840, &log);
    return -0x16;
  }
  puVar2 = FUN_00059b5c(0, frame.address);
  if (puVar2 == 0) {
    puVar2 = FUN_00059c04();
    if (puVar2 == 0) {
      frame.log.level = 2;
      frame.log.message = 0x000f48b5;
      FUN_00082a42(0x00088128, 0x1040, &frame.log);
      return -0xc;
    }
    VB(puVar2) = 0;
    FUN_000828da(puVar2+1, frame.address);
  }
  if (param_2 != 0) {
    iVar1 = ((int(*)(int,void*,int))param_3)(param_4, frame.decoded, 2);
    if (iVar1 < 0) {
      struct { unsigned level, message; int error; } log = { 3, 0x000f4783, iVar1 };
      FUN_00082a42(0x00088128, 0x1840, &log);
      return iVar1;
    }
    VB(puVar2+8) = frame.decoded[0];
    if (iVar1 == 2) {
      unsigned int u = frame.decoded[1];
      if (u < 2) { FUN_00082b98(puVar2, u & 1); return 0; }
      struct { unsigned level, message, value; } log = { 3, 0x000f492b, u };
      FUN_00082a42(0x00088128, 0x1880, &log);
    } else {
      frame.log.level = 2;
      frame.log.message = 0x000f48d7;
      FUN_00082a42(0x00088128, 0x1080, &frame.log);
    }
    FUN_00082bb8(puVar2, 0);
    return 0;
  }
  FUN_0005a39c(puVar2);
  return 0;
}
