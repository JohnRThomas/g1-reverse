/* named: register_imu_funsion_context */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed register_imu_funsion_context @ 0x26250  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void debug_print(void);

unsigned int register_imu_funsion_context(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    *(unsigned int*)(param_1+0x8c) = 0x00025fadUL;
    *(unsigned int*)(param_1+0x90) = 0x00025df9UL;
    *(unsigned int*)(param_1+0x94) = 0x00025dc5UL;
    *(unsigned int*)(param_1+0x98) = 0x00025d8dUL;
    if (*(volatile int*)0x2000230cUL > 1) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    return 0;
}

