/*
 * g1_log.h -- the ONE declaration of each recovered logging entry point.
 *
 * G7-B2 / cluster G7-C10 of recon/analysis/prerefactor_plan.md.
 *
 * Before this header the corpus declared these entry points 1,256 times in
 * 384 distinct signature spellings (`recon/ownership/code_dedupe_plan.json`,
 * cluster G7-C10).  That is not a style problem: under this build's
 * `-mfloat-abi=hard -mfpu=fpv5-sp-d16`, a VARIADIC function passes floating
 * point arguments in CORE registers while a NON-VARIADIC one passes them in
 * VFP registers, and `void debug_print(void)` cannot be called with arguments
 * at all.  Every translation unit was compiling against its own belief.
 *
 * GROUND TRUTH -- READ OFF THE SHIPPED DISASSEMBLY, NOT CHOSEN FOR TIDINESS.
 *
 * There are THREE distinct entry points on the application core, not four.
 * `DEBUG_PRINT` is Ghidra's name for the same address as `log_message`
 * (`recon/symbolized/app/log_message.c` binds it with an `__asm__` alias):
 *
 *   debug_print   FUN_00019c70 @ 0x00019c70   ring-buffer sink (vsnprintf_impl)
 *   log_message   FUN_0007dda4 @ 0x0007dda4   console sink (vprintf)
 *   DEBUG_PRINT   == log_message, same address
 *   printk        FUN_0007e2fa @ 0x0007e2fa   console sink (vprintf)
 *   printk (net)  FUN_01039722 @ 0x01039722   net-core console sink
 *
 * All three application entries open with the AAPCS variadic register-save
 * prologue and then take the va_list from the SECOND saved word:
 *
 *   00019c70  push {r0, r1, r2, r3}      0007dda4  push {r0, r1, r2, r3}
 *   00019c72  push {r4, r5, r6, lr}      0007dda6  push {r0, r1, r2, lr}
 *   00019c74  sub  sp, #0xd0             0007dda8  add  r1, sp, #0x10
 *   00019c76  add  r5, sp, #0xe0         0007ddaa  ldr  r0, [r1], #4   <- fixed arg
 *   00019c78  ldr  r6, [r5], #4  <- fixed arg, va_list = r5 afterwards
 *
 *   0007e2fa  push {r0, r1, r2, r3}   /  push {r0, r1, r2, lr}
 *   0007e300  ldr  r0, [r1], #4       <- fixed arg, va_list = r1 afterwards
 *
 * Therefore, for all three: EXACTLY ONE fixed parameter, in r0, followed by
 * `...`.  The post-increment load is the decisive evidence: the callee reads
 * one word out of the r0..r3 save area and starts the va_list at the next
 * word.  None of the three touches a VFP register anywhere in its prologue,
 * which is what the variadic ABI requires and what a non-variadic hard-float
 * declaration would violate.
 *
 * RETURN TYPE is `void`.  All 2,526 `bl`/`b.w` sites that target these three
 * addresses in `app_update.bin` were disassembled and the instructions after
 * each call examined: not one reads r0 before redefining it.  The ten sites
 * that mention r0 at all execute `eors r0, r0` (a write, zeroing it).  The
 * corpus spellings `int`, `uint32_t`, `uint64_t`, `long long`, `uintptr_t`
 * and `unsigned int` are all decompiler noise from r0/r1 being live scratch.
 *
 * The shipped firmware DOES pass floating point through these entries, under
 * the variadic convention, which is why the declaration matters:
 * `fuel_gauge_update` @ 0x10c14 converts three floats with __aeabi_f2d
 * (FUN_0000d848) and hands the results over in CORE register pairs and on the
 * stack -- `vmov r0,s21; bl 0xd848; ...; strd r0,r1,[sp,#8]; strd r8,sb,[sp]`
 * -- before `bl 0x19c70`.  A non-variadic declaration in that translation
 * unit would have placed them in s0..s15 instead.
 *
 * FORMAT PARAMETER TYPE.  In the shipped firmware r0 holds a pointer to a
 * format string, i.e. `const char *`.  This header spells it `uintptr_t`,
 * which on arm-zephyr-eabi in this build is `unsigned long`: the same 32-bit
 * value in the same register, so the declaration is ABI-identical.  The
 * reason is that after batch G6-B1 the corpus universally spells format
 * addresses as integer expressions -- `((unsigned long)"...")`,
 * `DAT_000241a8`, `0x000a6a28u` -- and declaring `const char *` would emit
 * roughly 2,500 `-Wint-conversion` diagnostics plus, through Zephyr's
 * `__printf_like(1, 2)` attribute, a `-Wformat` diagnostic per variadic
 * argument, without changing a single emitted instruction.  Re-spelling the
 * call sites is a separate, purely textual batch.
 *
 * printk AND ZEPHYR.  In the cohesive build the linked `printk` is NOT the
 * reconstruction in recon/symbolized/{app,net}/printk.c -- the adoption
 * manifest displaces both onto the stock `libzephyr.a(printk.c.obj)`, which
 * both link maps confirm.  The stock prototype is
 * `extern __printf_like(1, 2) void printk(const char *fmt, ...)`: the same
 * ABI (one fixed 32-bit fixed argument in r0, variadic, void) but not the
 * same C type.  Two different declarations of one symbol in one translation
 * unit is a hard error, so where <zephyr/sys/printk.h> is already in scope IT
 * is the single authority and this header stays silent; the include is always
 * emitted last in a translation unit so the guard below is decided correctly.
 * Converging the corpus spelling onto `const char *` is a follow-on textual
 * batch: the SDK prototype carries `__printf_like(1, 2)`, so it would also
 * emit a `-Wformat` diagnostic for every variadic argument, and roughly 700
 * format arguments must be re-spelled first.
 *
 * DO NOT add a `float`, `double` or fixed extra parameter to any declaration
 * here without re-reading the prologue above.
 */
#ifndef G1_LOG_H
#define G1_LOG_H

#include <stdint.h>

/* FUN_0007dda4 @ 0x0007dda4 -- console sink. */
void log_message(uintptr_t format, ...);

/* Ghidra's spelling of the SAME entry point, 0x0007dda4.  Bound as an
 * `__asm__` alias by recon/symbolized/app/log_message.c.  Never the distinct
 * debug_print @ 0x00019c70. */
void DEBUG_PRINT(uintptr_t format, ...);

/* FUN_00019c70 @ 0x00019c70 -- ring-buffer sink. */
void debug_print(uintptr_t format, ...);

/* FUN_0007e2fa @ 0x0007e2fa (app) / FUN_01039722 @ 0x01039722 (net). */
#ifndef ZEPHYR_INCLUDE_SYS_PRINTK_H_
void printk(uintptr_t format, ...);
#endif

#endif /* G1_LOG_H */
