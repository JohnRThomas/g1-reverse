/* named: spawn_display_thread */
/* globals referenced:
//   0x2000a09c  g_display_thread_id          [g_obj_2000a018.f_84]
*/
/* Reconstructed spawn_display_thread @ 0x49638  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00071eac(unsigned int, unsigned int, int, unsigned int, unsigned int, int, int, int, int);

unsigned int spawn_display_thread(unsigned int param_1)
{
    unsigned int uVar1 = FUN_00071eac(0x20004d18UL, 0x20028e68UL, 0x1400, 0x49091UL, param_1, 0, 0, 0xfffffff2, 0);
    *(volatile unsigned int*)0x2000a09cUL = uVar1;
    return 0;
}

