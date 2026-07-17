/* z_fdtable_call_ioctl @ 0x0007dcb8; raw FUN_0007dcb8 */
#include <stdarg.h>

struct fd_vtable {
    void *read;
    void *write;
    void *close;
    int (*ioctl)(void *, unsigned long, va_list);
};

int z_fdtable_call_ioctl(const struct fd_vtable *vtable, void *object,
                         unsigned long request, ...)
{
    va_list arguments;
    va_start(arguments, request);
    int result = vtable->ioctl(object, request, arguments);
    va_end(arguments);
    return result;
}
