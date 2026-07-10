/* named: notify_config_change_if_connected */
/* globals referenced:
//   0x20006a1c  g_settings_notify_mutex      
*/
/* Reconstructed notify_config_change_if_connected @ 0x17e84  (parity: 300/300 trials, PROVEN) */
extern int FUN_00019b2c(void);
extern long long is_battery_critical(void);
extern int get_device_info(void);
extern void k_mutex_lock(unsigned,unsigned,unsigned,unsigned);
extern int FUN_0004f518(int,unsigned,unsigned);
extern void k_mutex_unlock(unsigned);
extern void DEBUG_PRINT(unsigned,int,unsigned);
unsigned notify_config_change_if_connected(unsigned param_1, unsigned param_2){
    int r6 = FUN_00019b2c();
    long long uVar3 = is_battery_critical();
    int r4;
    if ((int)uVar3 != 0) goto L_work;
    if (r6 == 0) goto L_dc;
    {
        int t = get_device_info();
        if (*(char*)(t + 0xae3) != 0) goto L_dc;
        t = get_device_info();
        if (*(int*)(t + 0x9b4) == 0) goto L_dc;
    }
L_work:
    k_mutex_lock(0x20006a1c, (unsigned)((unsigned long long)uVar3 >> 32), 0xffffffff, 0xffffffff);
    r4 = FUN_0004f518(0, param_1, param_2);
    k_mutex_unlock(0x20006a1c);
    if (r4 == 0) return 0;
    DEBUG_PRINT(0x9a155, r4, param_2);
    goto L_dc;
L_dc:
    r4 = -1;
    return (unsigned)r4;
}

