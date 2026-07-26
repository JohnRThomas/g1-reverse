/* readable reconstruction; identity: FUN_00035afc @ 0x00035afc
 * public-name: draw_message
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_a8bcd                             @ 0x000a8bcd   [INLINED -- G6 literal batch]
 *   rodata_a8be6                             @ 0x000a8be6   [INLINED -- G6 literal batch]
 *   rodata_a8c09                             @ 0x000a8c09   [INLINED -- G6 literal batch]
 *   rodata_a8c11                             @ 0x000a8c11   [INLINED -- G6 literal batch]
 *   rodata_a8c34                             @ 0x000a8c34   [INLINED -- G6 literal batch]
 *   rodata_a8c37                             @ 0x000a8c37
 *   rodata_a8c3a                             @ 0x000a8c3a   [INLINED -- G6 literal batch]
 *   rodata_a8ce7                             @ 0x000a8ce7   [INLINED -- G6 literal batch]
 *   rodata_f4ca5                             @ 0x000f4ca5
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed draw_message @ 0x35afc; reviewed executable extent 0x41e bytes.
 * Raw identity: FUN_00035afc.  The bytes at 0x35f1c..0x35f27 are its literal
 * pool, not executable code. */
#include <stdint.h>

/* Keep stable raw link identities while making the recovered body readable. */
extern void debug_log(uintptr_t format, ...) __asm__("DEBUG_PRINT");
extern void buffered_debug_log(uintptr_t format, ...) __asm__("FUN_00019c70");
extern uint8_t current_notification_slot(void) __asm__("FUN_00034390");
extern int notification_icon_type_from_package(uint32_t slot);
extern void format_message_relative_time(char *output, uint32_t timestamp);
extern void gui_bmp_bitmap_draw(uint32_t bitmap, uint32_t x, uint32_t y,
                                uint32_t, uint32_t, uint32_t);
extern void gui_utf_draw(uint32_t, const char *, uint32_t, uint32_t, uint32_t,
                         uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                         uint32_t, uint32_t);
extern void gui_utf_draw_truncate(uint32_t, const char *, uint32_t, uint32_t,
                                  uint32_t, uint32_t, uint32_t, uint32_t,
                                  uint32_t, uint32_t, uint32_t, uint32_t);
extern void gui_utf_draw_middle(uint32_t, const char *, uint32_t, uint32_t,
                                uint32_t, uint32_t, uint32_t, uint32_t,
                                uint32_t, uint32_t, uint32_t, uint32_t);
extern void gui_utf_Wordwrap_draw(uint32_t, const char *, uint32_t, uint32_t,
                                  uint32_t, uint32_t, uint32_t, uint32_t,
                                  uint32_t, uint32_t, uint32_t, uint32_t);
extern int bounded_snprintf(char *output, uint32_t capacity,
                            uintptr_t format, ...) __asm__("FUN_00077914");
extern uint32_t display_text_width(void) __asm__("FUN_0007d3ee");
extern uint32_t display_text_height(void) __asm__("FUN_0007d446");
extern void clear_bytes(void *output, uint32_t value,
                        uint32_t length) __asm__("FUN_00086c78");
extern void format_uint_bounded(void *output, uint32_t reserved,
                                int32_t capacity, uintptr_t format,
                                uint32_t value) __asm__("FUN_00086f00");

/* Notification record used by the draw queue.  Each text field is a fixed
 * 32-byte slot; retaining the offsets documents every pointer seen in the
 * original code without inventing ownership beyond the last accessed field. */
struct notification_message {
    uint32_t received_at;                 /* +0x00 */
    uint8_t reserved_04[0x2c];
    char title[0x20];                     /* +0x30 */
    char body[0x20];                      /* +0x50 */
    char subtitle[0x20];                  /* +0x70 */
    char package_name[0x20];              /* +0x90 */
};

enum notification_icon_type {
    ICON_TYPE_SMS = 0,
    ICON_TYPE_MISSED_CALL = 1,
    ICON_TYPE_IN_CALL = 2,
    ICON_TYPE_PACKAGE_GROUP_3 = 3,
    ICON_TYPE_PACKAGE_GROUP_4 = 4,
};

enum notification_bitmap {
    BITMAP_IN_CALL = 0x36,
    BITMAP_MISSED_CALL = 0x37,
    BITMAP_SMS_OR_DEFAULT = 0x38,
    BITMAP_PACKAGE_GROUP_4 = 0x39,
    BITMAP_PACKAGE_GROUP_3 = 0x3a,
    BITMAP_CLOCK = 0x3c,
};

#define DEBUG_SINK_MODE (*(volatile uint32_t *)0x20007554u)

#define LOG_FUNCTION_NAME       ((uintptr_t)0x000a8ce7u) /* "draw_message" */
#define LOG_NULL_MESSAGE        ((uintptr_t)0x000a8bcdu)
#define LOG_MESSAGE_TYPE        ((uintptr_t)0x000a8be6u)
#define FORMAT_STRING           ((uintptr_t)0x000a8c37u) /* "%s" */
#define FORMAT_TITLE_SUBTITLE   ((uintptr_t)0x000a8c09u) /* "%s | %s" */
#define LOG_MESSAGE             ((uintptr_t)0x000a8c11u)
#define FORMAT_COUNTER          ((uintptr_t)0x000f4ca5u) /* "%u" */
#define FORMAT_BODY_PACKAGE_NL  ((uintptr_t)0x000a8c34u) /* "%s\n%s" */
#define FORMAT_BODY_PACKAGE_DASH ((uintptr_t)0x000a8c3au) /* "%s - %s" */

void draw_message(uint32_t unread_count, struct notification_message *message)
{
    /* These split initializations reproduce the four firmware-owned local
     * objects exactly: the memset calls begin four bytes into each large
     * buffer, while the leading word is cleared directly. */
    char heading[72];
    char relative_time[32];
    uint32_t count_text[2];
    char body_text[292];
    uint32_t icon_type;
    uint32_t x1, y1, x2, y2;
    const char *heading_source;

    *(uint32_t *)heading = 0;
    clear_bytes(heading + 4, 0, 68);
    *(uint32_t *)relative_time = 0;
    clear_bytes(relative_time + 4, 0, 28);
    count_text[0] = 0;
    count_text[1] = 0;
    *(uint32_t *)body_text = 0;
    clear_bytes(body_text + 4, 0, 0x11f);

    if (message == 0) {
        if (DEBUG_SINK_MODE != 0)
            buffered_debug_log(LOG_NULL_MESSAGE, LOG_FUNCTION_NAME, 0xdb);
        else
            debug_log(LOG_NULL_MESSAGE, LOG_FUNCTION_NAME, 0xdb);
        return;
    }

    icon_type = (uint32_t)notification_icon_type_from_package(
        current_notification_slot());
    if (DEBUG_SINK_MODE == 0)
        debug_log(LOG_MESSAGE_TYPE, icon_type, unread_count);
    else
        buffered_debug_log(LOG_MESSAGE_TYPE, icon_type, unread_count);

    switch (icon_type) {
    case ICON_TYPE_SMS:
        x1 = display_text_width();
        y1 = display_text_height();
        gui_bmp_bitmap_draw(BITMAP_SMS_OR_DEFAULT, x1, y1 + 4, 0, 0, 0);
        clear_bytes(heading, 0, 72);
        heading_source = message->title;
        break;

    case ICON_TYPE_MISSED_CALL:
        x1 = display_text_width();
        y1 = display_text_height();
        gui_bmp_bitmap_draw(BITMAP_MISSED_CALL, x1, y1 + 4, 0, 0, 0);
        clear_bytes(heading, 0, 72);
        heading_source = message->package_name;
        break;

    case ICON_TYPE_IN_CALL:
        clear_bytes(heading, 0, 72);
        bounded_snprintf(heading, 72, FORMAT_STRING, message->package_name);
        x1 = display_text_width();
        y1 = display_text_height();
        x2 = display_text_width();
        y2 = display_text_height();
        gui_utf_draw_middle(0, heading, 0, x1, y1 + 0x36,
                            x2 + 0x240, y2 + 0x51, 1, 0, 0, 0, 0);

        x1 = display_text_width();
        y1 = display_text_height();
        gui_bmp_bitmap_draw(BITMAP_IN_CALL, x1, y1 + 0x3a, 0, 0, 0);

        clear_bytes(body_text, 0, 0x123);
        bounded_snprintf(body_text, 0x123, FORMAT_STRING, message->body);
        if (body_text[0] == '\0')
            return;
        x1 = display_text_width();
        y1 = display_text_height();
        x2 = display_text_width();
        y2 = display_text_height();
        gui_utf_draw_middle(0, body_text, 0, x1, y1 + 0x51,
                            x2 + 0x240, y2 + 0x51, 1, 0, 0, 0, 0);
        return;

    case ICON_TYPE_PACKAGE_GROUP_3:
        x1 = display_text_width();
        y1 = display_text_height();
        gui_bmp_bitmap_draw(BITMAP_PACKAGE_GROUP_3, x1, y1 + 4, 0, 0, 0);
        clear_bytes(heading, 0, 72);
        bounded_snprintf(heading, 72, FORMAT_TITLE_SUBTITLE,
                         message->title, message->subtitle);
        goto draw_heading;

    case ICON_TYPE_PACKAGE_GROUP_4:
        x1 = display_text_width();
        y1 = display_text_height();
        gui_bmp_bitmap_draw(BITMAP_PACKAGE_GROUP_4, x1, y1 + 4, 0, 0, 0);
        clear_bytes(heading, 0, 72);
        heading_source = message->title;
        break;

    default:
        x1 = display_text_width();
        y1 = display_text_height();
        gui_bmp_bitmap_draw(BITMAP_SMS_OR_DEFAULT, x1, y1 + 4, 0, 0, 0);
        clear_bytes(heading, 0, 72);
        if (message->subtitle[0] != '\0') {
            bounded_snprintf(heading, 72, FORMAT_TITLE_SUBTITLE,
                             message->title, message->subtitle);
            goto draw_heading;
        }
        heading_source = message->title;
        break;
    }

    bounded_snprintf(heading, 72, FORMAT_STRING, heading_source);

draw_heading:
    x1 = display_text_width();
    y1 = display_text_height();
    x2 = display_text_width();
    y2 = display_text_height();
    gui_utf_draw_truncate(0, heading, 0, x1 + 0x24, y1,
                          x2 + 0x186, y2 + 0x1b, 1, 0, 0, 0, 0);

    if (DEBUG_SINK_MODE == 0)
        debug_log(LOG_MESSAGE, message->received_at, message->package_name);
    else
        buffered_debug_log(LOG_MESSAGE, message->received_at,
                           message->package_name);

    format_message_relative_time(relative_time, message->received_at);
    x1 = display_text_width();
    y1 = display_text_height();
    gui_bmp_bitmap_draw(BITMAP_CLOCK, x1 + 0x210, y1, 0, 0, 0);

    count_text[0] = 0;
    count_text[1] = 0;
    format_uint_bounded(count_text, 0, 8, FORMAT_COUNTER, unread_count);
    x1 = display_text_width();
    y1 = display_text_height();
    x2 = display_text_width();
    y2 = display_text_height();
    gui_utf_draw(0, (const char *)count_text, 0, x1 + 0x22c, y1,
                 x2 + 0x244, y2 + 0x1b, 1, 0, 0, 0, 0);

    clear_bytes(body_text, 0, 0x123);
    if (icon_type == ICON_TYPE_MISSED_CALL) {
        bounded_snprintf(body_text, 0x123, FORMAT_STRING, message->body);
    } else if (icon_type == ICON_TYPE_PACKAGE_GROUP_4) {
        bounded_snprintf(body_text, 0x123, FORMAT_BODY_PACKAGE_NL,
                         message->body, message->package_name);
    } else if (message->body[0] == '\0') {
        bounded_snprintf(body_text, 0x123, FORMAT_STRING,
                         message->package_name);
    } else {
        bounded_snprintf(body_text, 0x123, FORMAT_BODY_PACKAGE_DASH,
                         message->body, message->package_name);
    }

    if (body_text[0] == '\0')
        return;
    x1 = display_text_width();
    y1 = display_text_height();
    x2 = display_text_width();
    y2 = display_text_height();
    gui_utf_Wordwrap_draw(0, body_text, 0, x1, y1 + 0x36,
                          x2 + 0x240, y2 + 0x87, 3, 0, 0, 0, 0);
}
