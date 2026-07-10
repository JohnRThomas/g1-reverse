/* named: init_analytics_settings */
/* Reconstructed init_analytics_settings @ 0x7c360  (parity: 300/300 trials, PROVEN) */

extern int load_sys_setting(void);
extern int load_usr_setting(int);
extern int load_burial_point(int);
extern int get_device_info(void);
extern void reset_countdown_timer_default(int);
int init_analytics_settings(int param_1)
{
    int iVar1 = load_sys_setting();
    if (iVar1 == 0 && (iVar1 = load_usr_setting(param_1)) == 0 &&
        (iVar1 = load_burial_point(param_1)) == 0) {
        int r = get_device_info();
        reset_countdown_timer_default(*(int*)(r + 0xff0));
    }
    return 0;
}

