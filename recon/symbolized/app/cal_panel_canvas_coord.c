#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00042fb0 @ 0x00042fb0
 * public-name: cal_panel_canvas_coord
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_aa7a2                             @ 0x000aa7a2   [INLINED -- G6 literal batch]
 *   rodata_aa7cb                             @ 0x000aa7cb   [INLINED -- G6 literal batch]
 *   rodata_aa855                             @ 0x000aa855   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed cal_panel_canvas_coord @ 0x42fb0 (raw: FUN_00042fb0). */
#include <stdint.h>
#include "../../headers/g1_log.h"

/* Callee backmap:
 *   get_device_info  <- FUN_000167a8 @ 0x000167a8
 *   debug_print      <- FUN_00019c70 @ 0x00019c70
 *   DEBUG_PRINT                         @ 0x0007dda4
 */
extern uintptr_t get_device_info(void);

/* Fixed-address backmap retained for the standalone parity build. */
#define g_log_level           (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define g_log_use_alt_sink    (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define LOG_CANVAS_GEAR_FMT   ((uintptr_t)((unsigned long)"%s(): canvas_distance_gear:%d, pos_x:%d\n") /*=0xaa7a2*/)
#define LOG_RASTER_GEAR_FMT   ((uintptr_t)((unsigned long)"%s(): raster_height_gear:%d, pos_y:%d\n") /*=0xaa7cb*/)
#define LOG_FUNCTION_NAME     ((uintptr_t)((unsigned long)"cal_panel_canvas_coord") /*=0xaa855*/)

/* Only the fields consumed here are named.  The offsets are the recovered
 * device_info_t layout: device role/handedness at +0, raster-height gear at
 * +0xec0, and canvas-distance gear at +0xec1. */
struct panel_calibration_state {
    uint8_t device_type;
    uint8_t reserved_0001[0xebf];
    uint8_t raster_height_gear;
    uint8_t canvas_distance_gear;
};

static inline const struct panel_calibration_state *panel_state(void)
{
    return (const struct panel_calibration_state *)get_device_info();
}

void cal_panel_canvas_coord(int *canvas_x, int *raster_y)
{
    if (canvas_x != 0) {
        int previous_x = *canvas_x;
        int computed_x;

        switch (panel_state()->canvas_distance_gear) {
        case 1:
            computed_x = 22;
            break;
        case 2:
            computed_x = 8;
            break;
        case 4:
            computed_x = -4;
            break;
        case 5:
            computed_x = -8;
            break;
        case 6:
            computed_x = -10;
            break;
        case 7:
            computed_x = -12;
            break;
        case 8:
            computed_x = -14;
            break;
        case 9:
            computed_x = -16;
            break;
        default:
            computed_x = 0;
            break;
        }

        /* The shipped body publishes the unsigned-side coordinate before it
         * reloads the device role and, for the opposite temple, negates it. */
        *(volatile int *)canvas_x = computed_x;
        if (panel_state()->device_type == 1) {
            *(volatile int *)canvas_x = -*canvas_x;
        }

        if (*canvas_x != previous_x && g_log_level > 1) {
            unsigned int gear = panel_state()->canvas_distance_gear;
            if (g_log_use_alt_sink == 0) {
                log_message(LOG_CANVAS_GEAR_FMT, LOG_FUNCTION_NAME,
                            gear, *canvas_x);
            } else {
                debug_print(LOG_CANVAS_GEAR_FMT, LOG_FUNCTION_NAME,
                            gear, *canvas_x);
            }
        }
    }

    if (raster_y != 0) {
        int previous_y = *raster_y;
        unsigned int gear = panel_state()->raster_height_gear;
        int computed_y = (int)((8u - gear) * 35u);

        *(volatile int *)raster_y = computed_y;
        if (computed_y != previous_y && g_log_level > 1) {
            gear = panel_state()->raster_height_gear;
            if (g_log_use_alt_sink == 0) {
                log_message(LOG_RASTER_GEAR_FMT, LOG_FUNCTION_NAME,
                            gear, *raster_y);
            } else {
                debug_print(LOG_RASTER_GEAR_FMT, LOG_FUNCTION_NAME,
                            gear, *raster_y);
            }
        }
    }
}
