/* named: bond_deleted_cb */
/* globals referenced:
//   0x20006ab8  g_ancs_active_conn           
*/
/* Reconstructed bond_deleted_cb @ 0x183ac  (parity: 300/300 trials, PROVEN) */

extern void format_bt_addr_str(int, int);
extern void DEBUG_PRINT(int, int);
void bond_deleted_cb(int param_1, int param_2)
{
    char auStack_28[40];
    format_bt_addr_str(param_2, (int)auStack_28);
    DEBUG_PRINT(0x0009a458, (int)auStack_28);
    (*(volatile int*)0x20007514UL)--;
    *(volatile char*)(*(volatile int*)0x20006ab8UL + 0x367) = 0;
}

