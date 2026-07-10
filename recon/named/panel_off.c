/* named: panel_off */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed panel_off @ 0x46d2c  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(int);
extern void DEBUG_PRINT(int a, int b);
extern int debug_print(void);
extern int get_ambient_light_sensor_ready_flag(void);
extern int opt3007_chip_deinit(void);
extern int power_down_panel(void);

unsigned int panel_off(int param_1)
{
    int iVar1;

    *(int *)(param_1 + 0x374) = param_1 + -0x5c;
    if (*(int *)(param_1 + -0x48) != 0) {
        *(int *)(param_1 + 0x35c) = 0;
        if (*(volatile int *)0x2000230cUL > 2) {
            if (*(volatile int *)0x20007554UL == 0) {
                DEBUG_PRINT(0xd721e, 0xd72d1);
            } else {
                debug_print();
            }
        }
        iVar1 = get_ambient_light_sensor_ready_flag();
        if (iVar1 == 0) {
            opt3007_chip_deinit();
        }
        ((fn_t)(*(int *)(param_1 + -0x58)))(*(int *)(param_1 + 0x374));
        power_down_panel();
    }
    return 0;
}

