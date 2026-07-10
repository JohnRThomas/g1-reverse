/* named: get_localized_weekday_name */
/* Reconstructed get_localized_weekday_name @ 0x7d4b2  (parity: 300/300 trials, PROVEN) */

extern int FUN_00023ee0(void);
extern void get_localized_string_ptr(int a, int b);
void get_localized_weekday_name(int param_1) {
    int iVar1 = FUN_00023ee0();
    if (iVar1 != 6) iVar1 = 2;
    get_localized_string_ptr(iVar1, param_1);
}

