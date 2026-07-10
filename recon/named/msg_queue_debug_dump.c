/* named: msg_queue_debug_dump */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
//   0x20007dac  g_message_pool               
*/
/* Reconstructed msg_queue_debug_dump @ 0x33b0c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int, int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void debug_print(unsigned int);

void msg_queue_debug_dump(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int format_string = 0xa7d1cUL;
    volatile int *piVar1 = (volatile int*)0x20007554UL;
    volatile unsigned int *puVar3 = (volatile unsigned int*)0x20007dacUL;
    int iVar2 = 0;
    do {
        if (*piVar1 == 0) {
            DEBUG_PRINT(format_string, iVar2, puVar3[2], puVar3[1], puVar3[0], param_2, param_3);
        } else {
            debug_print(format_string);
        }
        iVar2 = iVar2 + 1;
        puVar3 = puVar3 + 0x6d;
    } while (iVar2 != 10);
}

