/* named: jbd_panel_suspend */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed jbd_panel_suspend @ 0x475f0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern void projector_send_command(void);

unsigned int jbd_panel_suspend(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    projector_send_command();
    return 0;
}

