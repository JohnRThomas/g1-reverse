/* named: message_table_contains_id */
/* globals referenced:
//   0x20007dac  g_message_pool               
*/
/* Reconstructed message_table_contains_id @ 0x33f24  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint;

uint message_table_contains_id(uint param_1, int param_2)
{
    unsigned char bVar1;
    int iVar2;
    bVar1 = 0;
    while (1) {
        if (param_1 <= bVar1) {
            return 0;
        }
        iVar2 = (int)bVar1 * 0x1b4 + 0x20007dac;
        if ((*(volatile char*)(iVar2 + 0x10) != 0) && (*(volatile int*)(iVar2 + 8) == param_2)) {
            break;
        }
        bVar1 = bVar1 + 1;
    }
    return 1;
}

