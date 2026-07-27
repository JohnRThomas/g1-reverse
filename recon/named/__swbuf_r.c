struct _reent;
/* readable reconstruction; identity: FUN_00077c8c @ 0x00077c8c
 * public-name: __swbuf_r
 * durable-map: recon/catalogs/function_names_app.json
 */
/* __swbuf_r @ 0x00077c8c; raw ext77c8c */
#include <stdint.h>

struct newlib_file {
    uint8_t *position;
    int32_t read_space;
    int32_t write_space;
    uint16_t flags;
    int16_t file_number;
    uint8_t *buffer_base;
    int32_t buffer_size;
    int32_t line_buffer_size;
};

extern void __sinit(struct _reent *); /* FUN_00076bcc */
extern int __swsetup_r(void *reent, struct newlib_file *file); /* FUN_00077d54 */
extern int _fflush_r(void *reent, struct newlib_file *file); /* FUN_00076ad0 */

int __swbuf_r(void *reent, int character, struct newlib_file *file)
{
    int used;

    if (reent != 0 && *(uint32_t *)((uint8_t *)reent + 0x18) == 0u) {
        __sinit(reent);
    }
    if (file == (struct newlib_file *)0x0009871cu) {
        file = *(struct newlib_file **)((uint8_t *)reent + 4);
    } else if (file == (struct newlib_file *)0x000986fcu) {
        file = *(struct newlib_file **)((uint8_t *)reent + 8);
    } else if (file == (struct newlib_file *)0x000986dcu) {
        file = *(struct newlib_file **)((uint8_t *)reent + 12);
    }

    file->write_space = file->line_buffer_size;
    if (((file->flags & 8u) == 0u || file->buffer_base == 0) &&
        __swsetup_r(reent, file) != 0) {
        return -1;
    }

    character = (uint8_t)character;
    used = (int)(file->position - file->buffer_base);
    if (used >= file->buffer_size) {
        if (_fflush_r(reent, file) != 0) {
            return -1;
        }
        used = 0;
    }

    file->write_space--;
    *file->position++ = (uint8_t)character;
    used++;
    if (used == file->buffer_size ||
        (((file->flags & 1u) != 0u) && character == '\n')) {
        if (_fflush_r(reent, file) != 0) {
            return -1;
        }
    }
    return character;
}
