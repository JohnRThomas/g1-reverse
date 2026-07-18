/* _vsprintf_r @ 0x00077c4c; raw FUN_00077c4c */
#include <stdint.h>

struct newlib_string_file {
    uint8_t *position;
    int32_t read_space;
    int32_t write_space;
    uint32_t flags_and_file;
    uint8_t *buffer_base;
    int32_t buffer_size;
};

extern int svfprintf_reentrant(void *reent, struct newlib_string_file *file, const char *format, void *arguments); /* FUN_00078d90 */

int _vsprintf_r(void *reent, char *output, const char *format, void *arguments)
{
    struct newlib_string_file file;
    int result;

    file.position = (uint8_t *)output;
    file.write_space = 0x7fffffff;
    file.flags_and_file = 0xffff0208u;
    file.buffer_base = (uint8_t *)output;
    file.buffer_size = 0x7fffffff;
    result = svfprintf_reentrant(reent, &file, format, arguments);
    *file.position = 0;
    return result;
}
