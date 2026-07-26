#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00048e28 @ 0x00048e28
 * public-name: display_reflash_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   ui_refalsh_warp                          <= FUN_00048b5c @ 0x00048b5c
 *   display_reflash_handler                  <= FUN_00048e28 @ 0x00048e28
 * address symbols (name @ address):
 *   rodata_ef7bb                             @ 0x000ef7bb   [INLINED -- G6 literal batch]
 *   rodata_ef7ef                             @ 0x000ef7ef   [INLINED -- G6 literal batch]
 *   rodata_ef87a                             @ 0x000ef87a   [INLINED -- G6 literal batch]
 *   rodata_ef8d7                             @ 0x000ef8d7   [INLINED -- G6 literal batch]
 *   rodata_ef937                             @ 0x000ef937   [INLINED -- G6 literal batch]
 *   rodata_ef9bf                             @ 0x000ef9bf   [INLINED -- G6 literal batch]
 *   rodata_efa29                             @ 0x000efa29   [INLINED -- G6 literal batch]
 *   rodata_efaa5                             @ 0x000efaa5   [INLINED -- G6 literal batch]
 *   rodata_f01d3                             @ 0x000f01d3   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_2001d447                               @ 0x2001d447
 */
/* Reconstructed FUN_00048e28 @ 0x48e28 */
#include <stdint.h>
#include "../../../headers/g1_log.h"

extern int ui_refalsh_warp(unsigned int, unsigned int, unsigned int, int);

unsigned int display_reflash_handler(unsigned int owner, unsigned int requested,
                         unsigned int payload, int mode)
{
    volatile uint8_t *state = (volatile uint8_t *)((unsigned long)&g_2001d447) /*=0x2001d447*/;
    volatile int *log_level = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    volatile int *alternate_log = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    unsigned int current = state[1];

    if (mode == 2) {
        if (requested != current && current != 0) {
            if (*log_level > 0) {
                if (*alternate_log == 0)
                    log_message(((unsigned long)"%s(): !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n") /*=0xef7bb*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, payload, 0);
                else
                    debug_print(((unsigned long)"%s(): !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n") /*=0xef7bb*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, payload,
                                 *alternate_log);

                if (*log_level > 0) {
                    current = state[1];
                    if (*alternate_log == 0)
                        log_message(((unsigned long)"%s(): The wrong screen ID has appeared, and the exception handling is closed,The message ID at startup is %d. The current message ID is%d\n") /*=0xef7ef*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, current, requested);
                    else
                        debug_print(((unsigned long)"%s(): The wrong screen ID has appeared, and the exception handling is closed,The message ID at startup is %d. The current message ID is%d\n") /*=0xef7ef*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/,
                                     current, requested);

                    if (*log_level > 0) {
                        current = state[1];
                        if (*alternate_log == 0)
                            log_message(((unsigned long)"%s(): To perform exception handling, close the previous SCREEN ID = %d UI application first\n") /*=0xef87a*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, current, 0);
                        else
                            debug_print(((unsigned long)"%s(): To perform exception handling, close the previous SCREEN ID = %d UI application first\n") /*=0xef87a*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, current,
                                         *alternate_log);
                    }
                }
            }
            ui_refalsh_warp(owner, requested, payload, 2);
            return 0xffffffff;
        }
    } else if (mode == 1) {
        if (requested != current && current != 0) {
            if (*log_level > 0) {
                if (*alternate_log == 0)
                    log_message(((unsigned long)"%s(): ----------------------------------------------------------------------------------------\n") /*=0xef8d7*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, payload, 0);
                else
                    debug_print(((unsigned long)"%s(): ----------------------------------------------------------------------------------------\n") /*=0xef8d7*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, payload,
                                 *alternate_log);

                if (*log_level > 0) {
                    current = state[1];
                    if (*alternate_log == 0)
                        log_message(((unsigned long)"%s(): There is a screen ID error. The previous screen iD was %d, the current screen ID is %d, and the UI process to be performed is %d\n") /*=0xef937*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, current,
                                    requested);
                    else
                        debug_print(((unsigned long)"%s(): There is a screen ID error. The previous screen iD was %d, the current screen ID is %d, and the UI process to be performed is %d\n") /*=0xef937*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, current,
                                     requested);

                    if (*log_level > 0) {
                        current = state[1];
                        if (*alternate_log == 0)
                            log_message(((unsigned long)"%s(): The UI framework closes the opened UI application first, and the closed application ScreenID is %d\n") /*=0xef9bf*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, current, 0);
                        else
                            debug_print(((unsigned long)"%s(): The UI framework closes the opened UI application first, and the closed application ScreenID is %d\n") /*=0xef9bf*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, current,
                                         *alternate_log);
                    }
                }
            }

            ui_refalsh_warp(owner, state[1], payload, 2);
            if (*log_level > 0) {
                if (*alternate_log == 0)
                    log_message(((unsigned long)"%s(): Because ScreenID has changed, close the old screenID application first and update the backup value of screenID to %d\n") /*=0xefa29*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, requested, 0);
                else
                    debug_print(((unsigned long)"%s(): Because ScreenID has changed, close the old screenID application first and update the backup value of screenID to %d\n") /*=0xefa29*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, requested,
                                 *alternate_log);
            }
            state[1] = (uint8_t)requested;
        }
    } else if (requested != current && *log_level > 0) {
        if (*alternate_log == 0)
            log_message(((unsigned long)"%s(): *************************************************************************************************\n") /*=0xefaa5*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, payload, 0);
        else
            debug_print(((unsigned long)"%s(): *************************************************************************************************\n") /*=0xefaa5*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, payload,
                         *alternate_log);

        if (*log_level > 0) {
            current = state[1];
            if (*alternate_log == 0)
                log_message(((unsigned long)"%s(): There is a screen ID error. The previous screen iD was %d, the current screen ID is %d, and the UI process to be performed is %d\n") /*=0xef937*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, current, requested);
            else
                debug_print(((unsigned long)"%s(): There is a screen ID error. The previous screen iD was %d, the current screen ID is %d, and the UI process to be performed is %d\n") /*=0xef937*/, ((unsigned long)"display_reflash_handler") /*=0xf01d3*/, current, requested);
        }
    }

    ui_refalsh_warp(owner, requested, payload, mode);
    return 0;
}
