/* named: check_sw0_status */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed check_sw0_status @ 0x2a868  (parity: 300/300 trials, PROVEN) */

extern int read_sw0_pin(void);
extern void debug_print(void);
extern void pt_nfc_eeprom_link_start(void);
extern void DEBUG_PRINT(unsigned int fmt, unsigned int arg);

void check_sw0_status(void)
{
    int iVar3 = read_sw0_pin();
    volatile int *piVar2 = (volatile int *)0x2000230cUL;
    volatile int *piVar1 = (volatile int *)0x20007af0UL;

    if (iVar3 == 0) {
        if (*piVar2 > 1) {
            if (*(volatile int *)0x20007554UL == 0) {
                DEBUG_PRINT(0xa18cdU, 0xa19afU);
            } else {
                debug_print();
            }
        }
        iVar3 = *piVar1 + 1;
        *piVar1 = iVar3;
        if (iVar3 > 3) {
            if (*piVar2 > 1) {
                if (*(volatile int *)0x20007554UL == 0) {
                    DEBUG_PRINT(0xa18eaU, 0xa19afU);
                } else {
                    debug_print();
                }
            }
            pt_nfc_eeprom_link_start();
            return;
        }
    } else {
        *piVar1 = 0;
    }
    return;
}

