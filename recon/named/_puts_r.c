/* readable reconstruction; identity: FUN_00077820 @ 0x00077820
 * public-name: _puts_r
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_f5400                             @ 0x000f5400
 */
/* app-core _puts_r @ 0x00077820.
 * Exact reachable code is [0x00077820,0x000778c2), 162 bytes. The NOP at
 * 0x000778c2 is alignment; literals occupy [0x000778c4,0x000778d4), and
 * puts starts at 0x000778d4. Raw backmap: FUN_00077820@0x00077820. */
#include <stdint.h>

extern uint32_t strlen(const char *text); /* FUN_0000ef12@0x0000ef12 */
extern void __retarget_lock_acquire_recursive(uint32_t lock); /* FUN_000510fc@0x000510fc */
extern void __retarget_lock_release_recursive(uint32_t lock); /* FUN_00051134@0x00051134 */
extern void __sinit(void *reent); /* FUN_00076bcc@0x00076bcc */
extern int __sfvwrite_r(void *reent, void *stream, void *uio); /* FUN_00077e70@0x00077e70 */

struct __siov_local {
    const void *base;
    uint32_t length;
};

struct __suio_local {
    struct __siov_local *iov;
    uint32_t iov_count;
    uint32_t residual;
};

struct puts_uio {
    struct __suio_local uio;
    struct __siov_local iov[2];
};

enum {
    REENT_STDIN_OFFSET = 4,
    REENT_STDOUT_OFFSET = 8,
    REENT_STDERR_OFFSET = 12,
    REENT_STDIO_INITIALIZED_OFFSET = 0x18,
    FILE_FLAGS_OFFSET = 0x0c,
    FILE_LOCK_OFFSET = 0x58,
    FILE_STATE_OFFSET = 0x64,
};

#define NEWLINE_TEXT_ADDR       0x000f5400u
#define NEWLIB_FAKE_STDIN_ADDR  0x0009871cu
#define NEWLIB_FAKE_STDOUT_ADDR 0x000986fcu
#define NEWLIB_FAKE_STDERR_ADDR 0x000986dcu

static uint32_t word_at(const void *object, uint32_t offset)
{
    return *(const uint32_t *)((const uint8_t *)object + offset);
}

static uint16_t halfword_at(const void *object, uint32_t offset)
{
    return *(const uint16_t *)((const uint8_t *)object + offset);
}

int _puts_r(void *reent, const char *text)
{
    struct puts_uio call;
    uint32_t measured = strlen(text);
    uintptr_t stream;

    call.iov[0].base = text;
    call.iov[0].length = measured;
    call.iov[1].base = (const void *)NEWLINE_TEXT_ADDR;
    call.iov[1].length = 1;
    call.uio.iov = call.iov;
    call.uio.iov_count = 2;
    call.uio.residual = measured + 1;

    if (reent == 0) {
        /* The original performs a null load followed by UDF #0xff. */
        (void)*(volatile uint32_t *)(uintptr_t)8;
        __builtin_trap();
    }

    if (word_at(reent, REENT_STDIO_INITIALIZED_OFFSET) == 0) {
        __sinit(reent);
        stream = word_at(reent, REENT_STDOUT_OFFSET);
        if (word_at(reent, REENT_STDIO_INITIALIZED_OFFSET) == 0)
            __sinit(reent);
    } else {
        stream = word_at(reent, REENT_STDOUT_OFFSET);
    }

    if (stream == NEWLIB_FAKE_STDIN_ADDR)
        stream = word_at(reent, REENT_STDIN_OFFSET);
    else if (stream == NEWLIB_FAKE_STDOUT_ADDR)
        stream = word_at(reent, REENT_STDOUT_OFFSET);
    else if (stream == NEWLIB_FAKE_STDERR_ADDR)
        stream = word_at(reent, REENT_STDERR_OFFSET);

    uint32_t state = word_at((void *)stream, FILE_STATE_OFFSET);
    uint16_t flags = halfword_at((void *)stream, FILE_FLAGS_OFFSET);
    if ((state & 1u) == 0 && (flags & 0x0200u) == 0)
        __retarget_lock_acquire_recursive(
            word_at((void *)stream, FILE_LOCK_OFFSET));

    int result = __sfvwrite_r(reent, (void *)stream, &call.uio) == 0 ? 10 : -1;

    state = word_at((void *)stream, FILE_STATE_OFFSET);
    flags = halfword_at((void *)stream, FILE_FLAGS_OFFSET);
    if ((state & 1u) == 0 && (flags & 0x0200u) == 0)
        __retarget_lock_release_recursive(
            word_at((void *)stream, FILE_LOCK_OFFSET));

    return result;
}
