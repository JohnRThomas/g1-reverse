/* readable reconstruction; identity: FUN_0001694c @ 0x0001694c
 * public-name: change_work_mode_to
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   enable_ship_mode                         <= FUN_000167f4 @ 0x000167f4
 *   global_system_resume                     <= FUN_00016854 @ 0x00016854
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   global_ipc_service_send                  <= FUN_00025b78 @ 0x00025b78
 *   app_msleep_thunk_a                       <= FUN_0007c038 @ 0x0007c038
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9976b                             @ 0x0009976b   [INLINED -- G6 literal batch]
 *   rodata_99bb7                             @ 0x00099bb7   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   device_info                              @ 0x200069fc
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_change_work_mode_busy                  @ 0x2000ff4b
 */
/* Reconstructed change_work_mode_to @ 0x1694c  (parity: 296/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef unsigned int uint;
extern int log_message(int,...);
extern int enable_ship_mode(int,...);
extern int global_system_resume(int,...);
extern int debug_print(int,...);
extern int global_ipc_service_send(int,...);
extern int app_msleep_thunk_a(int,...);
extern int memset_bytes(int,...);

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
    app_msleep_thunk_a(1);

  *busy = 1;
  int state = *state_slot;
  if ((uint)*(volatile byte *)(state + 1) != mode) {
    *(volatile byte *)(state + 1) = (byte)mode;
    if (0 < *(volatile int*)0x2000230c) {
      if (*(volatile int*)0x20007554 == 0) log_message(((unsigned long)"%s(): change_work_mode to %d\n"),((unsigned long)"change_work_mode"),mode & 0xff);
      else debug_print(0);
    }
    unsigned selected = *(volatile byte *)(*state_slot + 1);
    if (selected < 10) {
      if (selected == 7) {
        enable_ship_mode(1);
      } else {
        for (unsigned i = 0; i < 10; ++i) {
          unsigned mask = masks[i];
          if ((selected == 3 || selected == 8 || selected == 9) && i < 2)
            mask = masks[1 - i];
          global_system_resume(values[selected][i], mask);
        }
        if (selected == 1) {
          unsigned char message[64];
          memset_bytes((int)(message + 4), 0, 60);
          *(unsigned short *)message = 0x801;
          global_ipc_service_send((int)message, 4);
        } else if (selected == 2) {
          memset_bytes(*state_slot + 0xef, 0, 1500);
        }
      }
    }
  }
  *busy = 0;
}
