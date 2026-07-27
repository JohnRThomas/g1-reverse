/* Reconstructed FUN_0007c360 @ 0x7c360  (parity: 300/300 trials, PROVEN) */

extern int load_sys_setting(unsigned long);
extern int load_usr_setting(int);
extern int load_burial_point(int);
extern int get_device_info(void);
extern void FUN_0007d1b8(int);
int FUN_0007c360(int param_1)
{
    int iVar1 = load_sys_setting(param_1);
    if (iVar1 == 0 && (iVar1 = load_usr_setting(param_1)) == 0 &&
        (iVar1 = load_burial_point(param_1)) == 0) {
        int r = get_device_info();
        FUN_0007d1b8(*(int*)(r + 0xff0));
    }
    return 0;
}

