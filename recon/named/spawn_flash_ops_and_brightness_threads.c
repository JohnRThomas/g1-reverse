/* named: spawn_flash_ops_and_brightness_threads */
/* globals referenced:
//   0x200079e4  g_app_language_msgq          
*/
/* Reconstructed spawn_flash_ops_and_brightness_threads @ 0x23a54  (parity: 300/300 trials, PROVEN) */
extern void z_impl_k_sem_init(unsigned a, int b, int c);
extern void FUN_00071eac(unsigned, ...);
void spawn_flash_ops_and_brightness_threads(int param_1){
    z_impl_k_sem_init(0x200079e4, 0, 0x14);
    FUN_00071eac(0x20003e38, 0x20021968, 0x800, 0x23481, param_1, 0, 0, 0xfffffff4, 0);
    FUN_00071eac(0x20003f10, 0x20022168, 0x1400, 0x23845, param_1, 0, 0, 0xfffffff5, 0);
}

