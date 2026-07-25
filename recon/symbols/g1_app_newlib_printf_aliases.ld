/* P4 iteration 22 — library-displacement Batch 4, "newlib printf family".
 *
 * adoption_manifest.json excludes the sixteen recovered bodies of the
 * newlib-nano formatting closure (see recon/emulator/reports/our_boot_bringup.md
 * §22).  The shipped bytes at each of those VAs are byte-identical to the
 * pinned arm-zephyr-eabi 12.2 newlib-nano libc_nano.a
 * (thumb/v8-m.main+fp/hard) over the ENTIRE upstream section after masking
 * relocation slots, so the identities below are the genuine library entry
 * points under the reversible names the naming waves happened to pick.
 *
 * These aliases do not pin code to original firmware addresses.  They only map
 * a historical spelling onto the upstream owner, so retained callers outside
 * the batch keep binding to exactly one definition.  PROVIDE stays non-owning:
 * were a real definition of any of these names to reappear, it would win.
 *
 * `quorem` is file-static upstream and therefore has no alias; after this batch
 * its only caller (_dtoa_r) is the library's own.
 */

/* Called from retained Even code (bt_start, DashBoard_Reflash, gui_clock_draw,
 * build_str_response_frame, send_notification_app_whitelist,
 * spec_ble_command_hook, test_mode_apply_base_status_cmd). */
PROVIDE(vdprintf_to_fd = __sprintf_chk);
/* Called from format_message_relative_time. */
PROVIDE(format_string_to_buffer = sprintf);
PROVIDE(snprintf_engine_bounded = _vsnprintf_r);
/* Batch 4b wrappers.  `vsnprintf_impl` is still called from debug_print;
 * `fprintf_stream` is spelled by g1_app_function_aliases.ld. */
PROVIDE(vsnprintf_impl = vsnprintf);
PROVIDE(vsprintf_impl = vsprintf);
PROVIDE(fprintf_stream = fprintf);

/* The remaining members of the closure have no retained caller once the whole
 * family is displaced together, but g1_app_function_aliases.ld and the
 * reversible-name aliases still spell some of them, and a later iteration may
 * re-add a caller.  Binding them here keeps every historical spelling
 * single-owner instead of silently undefined. */
PROVIDE(printf_parse_format = _svfprintf_r);
PROVIDE(iobuf_ensure_capacity_and_append = __ssputs_r);
PROVIDE(vfprintf_format_engine = _printf_i);
PROVIDE(vfprintf_emit_padded_field = _printf_common);
PROVIDE(printf_render_float = _printf_float);
PROVIDE(dtoa_format_cvt = __cvt);
PROVIDE(itoa_signed_exponent = __exponent);
PROVIDE(libc_write_buffer_via_putc = __sfputs_r);
PROVIDE(dtoa_r = _dtoa_r);
