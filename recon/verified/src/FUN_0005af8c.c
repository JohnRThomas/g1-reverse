/* Reconstructed FUN_0005af8c @ 0x5af8c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00059edc(void);
extern int FUN_00077c1c(int,...);
extern int FUN_0007f1a0(int,...);
extern int FUN_0007f1e8(int,...);
extern int FUN_00080cf2(int,...);
extern int FUN_00082a42(int,...);
extern int FUN_00082c9c(int,...);
typedef int (*codeptr)(int,...);
unsigned int FUN_0005af8c(int param_1,int param_2,codeptr param_3,int param_4,int param_5)
{
  int iVar1;
  unsigned int uVar2;
  struct request_frame {
    int object;
    int identity;
    unsigned char address[8];
    unsigned char *address_ptr;
    unsigned char kind;
    unsigned char kind_pad[3];
    unsigned char *payload_ptr;
    unsigned int payload_words;
    unsigned char payload[192];
    unsigned char compiler_frame_pad[8];
  } frame;
  unsigned int lookup_result;
  iVar1 = FUN_0007f1a0(param_5, 0xf4a9e, &frame.object);
  if (iVar1 == 0) {
    uVar2 = FUN_00059edc();
  } else {
    FUN_0007f1e8(frame.object, &frame.identity);
    if (frame.object == 0) {
      struct { unsigned level, message; } log = { 2, 0x000f2b65 };
      FUN_00082a42(0x88128, 0x1040, &log);
    } else {
      if ((frame.identity == 0) ||
          (lookup_result = FUN_00077c1c(frame.identity,0,10), lookup_result == 0)) {
        frame.kind = 0;
        iVar1 = FUN_00080cf2(frame.object, frame.address);
        if (iVar1 == 0) {
          frame.address_ptr = frame.address;
          if (param_2 == 0) {
            frame.payload_ptr = 0;
            frame.payload_words = 0;
          } else {
            int payload_bytes = param_3(param_4, (int)frame.payload, 0xc0);
            if (payload_bytes < 0) {
              struct { unsigned level, message; int error; } log = {
                3, 0x000f4783, payload_bytes
              };
              FUN_00082a42(0x88128, 0x1840, &log);
              return (unsigned int)payload_bytes;
            }
            frame.payload_words = (unsigned int)payload_bytes >> 2;
            frame.payload_ptr = frame.payload;
          }
          FUN_00082c9c(1, 0xffff, 0x59ded, &frame.address_ptr);
          return 0;
        }
        struct { unsigned type, message; int value; unsigned short flags; } log = {
          0x01000003, 0x000f472a, frame.object, 0x200
        };
        FUN_00082a42(0x88128, 0x1c40, &log);
      } else {
        struct { unsigned level, message; int error; } log = {
          3, 0x000f4746, (int)lookup_result
        };
        FUN_00082a42(0x88128, 0x1840, &log);
      }
    }
    uVar2 = 0xffffffea;
  }
  return uVar2;
}
