/* Reconstructed change_work_mode_to @ 0x1694c  (parity: 296/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef unsigned int uint;
extern int DEBUG_PRINT(int,...);
extern int FUN_000167f4(int,...);
extern int FUN_00016854(int,...);
extern int FUN_00019c70(int,...);
extern int FUN_00025b78(int,...);
extern int FUN_0007c038(int,...);
extern int FUN_00086c78(int,...);

void change_work_mode_to(uint mode)
{
  static const unsigned char values[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,0,0,1,1},
    {1,1,2,1,1,0,1,1,1,1},
    {0,0,1,1,1,0,1,1,1,1},
    {0,0,0,1,1,0,0,0,1,1},
    {0,0,0,1,1,0,0,0,1,1},
    {0,0,0,1,1,0,0,0,1,1},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1},
    {0,1,1,0,0,1,1,1,1,1},
  };
  static const unsigned short masks[10] = {
    0x10,0x100,0x20,0x80,0x40,8,2,1,0x400,0x800
  };
  volatile unsigned char *busy = (volatile unsigned char *)0x2000ff4b;
  volatile int *state_slot = (volatile int *)0x200069fc;
  int retries = 3000;

  while (*busy != 0 && --retries != 0)
    FUN_0007c038(1);

  *busy = 1;
  int state = *state_slot;
  if ((uint)*(volatile byte *)(state + 1) != mode) {
    *(volatile byte *)(state + 1) = (byte)mode;
    if (0 < *(volatile int*)0x2000230c) {
      if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0x9976b,0x99bb7,mode & 0xff);
      else FUN_00019c70(0);
    }
    unsigned selected = *(volatile byte *)(*state_slot + 1);
    if (selected < 10) {
      if (selected == 7) {
        FUN_000167f4(1);
      } else {
        for (unsigned i = 0; i < 10; ++i) {
          unsigned mask = masks[i];
          if ((selected == 3 || selected == 8 || selected == 9) && i < 2)
            mask = masks[1 - i];
          FUN_00016854(values[selected][i], mask);
        }
        if (selected == 1) {
          unsigned char message[64];
          FUN_00086c78((int)(message + 4), 0, 60);
          *(unsigned short *)message = 0x801;
          FUN_00025b78((int)message, 4);
        } else if (selected == 2) {
          FUN_00086c78(*state_slot + 0xef, 0, 1500);
        }
      }
    }
  }
  *busy = 0;
}
