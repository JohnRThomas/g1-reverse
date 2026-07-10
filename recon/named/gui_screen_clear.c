/* named: gui_screen_clear */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed gui_screen_clear @ 0x431c0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern int get_projector_controller(void);
extern void projector_fill_and_sync(void);

unsigned int gui_screen_clear(void)
{
    unsigned int uVar3;
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    int iVar2 = get_projector_controller();
    int field = *(volatile int*)(iVar2 + 0x35c);
    if (field == 0) {
        if (*(volatile int*)0x2000230cUL > 0) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT();
            } else {
                debug_print();
            }
        }
        uVar3 = 0xffffffffUL;
    } else {
        projector_fill_and_sync();
        uVar3 = 0;
    }
    return uVar3;
}

