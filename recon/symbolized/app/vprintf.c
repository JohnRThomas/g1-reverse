#include "g1_app_symbols.h"
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/uart.h>
/* readable reconstruction; identity: FUN_0004b1cc @ 0x0004b1cc
 * public-name: vprintf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_cbvprintf_impl                         <= FUN_000113a8 @ 0x000113a8
 *   vprintf                                  <= FUN_0004b1cc @ 0x0004b1cc
 * address symbols (name @ address):
 *   rodata_4b1b5                             @ 0x0004b1b5
 */
/* Reconstructed FUN_0004b1cc @ 0x4b1cc  (parity: 300/300 trials, PROVEN) */

/* ---------------------------------------------------------------------------
 * BRING-UP WIRING FIX (P4 iteration 3) — relocated char-out callback.
 *
 * The original vprintf passed the ABSOLUTE address 0x4b1b5 (Thumb) to
 * z_cbvprintf_impl as its per-character output callback.  In the shipped image
 * 0x4b1b4 is a tiny char-out trampoline:
 *      ldr r3,[pc] ; =0x200027c8   (firmware stdout-hook global)
 *      ldr r3,[r3]                 (installed worker = console_out @0x608ec)
 *      bx  r3
 * that indirects through a runtime hook global (0x200027c8) whose installed
 * value is the standard Zephyr console_out ('\n'->"\r\n", uart_poll_out on the
 * chosen console UART).  The trampoline (@0x4b1b4), the char-out worker
 * (console_out @0x608ec) and its installer (uart_console init @0x608c4) are all
 * folded INSIDE the clock_control_nrf_on_blocking symbol (0x60788) in the
 * catalog and were never split out / reconstructed, so in our relocated build:
 *   (1) the literal 0x4b1b5 (symbol rodata_4b1b5, pinned absolute) now lands in
 *       the middle of an unrelated function (rtc_cb) -> z_cbvprintf_impl called
 *       through garbage -> assertion -> kernel OOPS, and
 *   (2) the hook global 0x200027c8 is never installed (its setter is DCE'd),
 *       so even a correct trampoline would read NULL.
 * We bind vprintf directly to the chosen-console UART char-out, reproducing the
 * shipped image's observable output path (console_out -> uart_poll_out) without
 * the runtime-swappable hook indirection.  Relocatable (linker/DT-resolved);
 * no absolute pin.  See recon/emulator/reports/our_boot_bringup.md §Iteration 3.
 * ------------------------------------------------------------------------- */
static int g1_vprintf_char_out(int c, void *ctx)
{
    (void)ctx;
    const struct device *dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

    if (c == '\n') {
        uart_poll_out(dev, (unsigned char)'\r');
    }
    uart_poll_out(dev, (unsigned char)c);
    return c;
}

extern void z_cbvprintf_impl(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g);

void vprintf(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    z_cbvprintf_impl((unsigned int)(unsigned long)&g1_vprintf_char_out, 0, param_1, param_2, 0, param_2, param_3);
}
