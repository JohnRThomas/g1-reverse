/* ---------------------------------------------------------------------------
 * BRING-UP WIRING TU (P4 iteration 10) — the ST25DV transport ops vtable.
 *
 * `serialization_ipc_ept_register` (original 0x259d4, the ST25DV bring-up)
 * stores `&rodata_88a38` into the descriptor's +8 slot, and
 * `st25dv_read_chip_ids` (0x25290) then calls the table's THIRD entry:
 *
 *     (*(void (**)(void))(*(int *)(descriptor + 8) + 8))();
 *
 * The pin ledger brackets the table exactly: `rodata_88a38` at 0x00088a38 and
 * the next pin `rodata_88a44` at 0x00088a44, i.e. 12 bytes = three function
 * pointers.  Read out of app_update.bin with tools/extract.py:
 *
 *     0x88a38: 0x00025789  -> 0x25788 ipc_send_len_prefixed_packet_locked_retry
 *     0x88a3c: 0x000256dd  -> 0x256dc ipc_ept_op_a_locked_retry
 *     0x88a40: 0x0007c86d  -> 0x7c86c FUN_0007c86c  (Ghidra catalog gap;
 *                             reconstructed + proven this iteration)
 *
 * Those are ORIGINAL-image Thumb addresses.  A bare `PROVIDE(rodata_88a38 =
 * 0x88a38)` leaves both the table address and its contents unrelocated: in the
 * rebuilt image 0x88a38 holds an unrelated string ("ng_with_len.c"), so the
 * indirect call jumped to garbage.
 *
 * MEASURED FAILURE (iteration 10, build /private/tmp/g1-i10e-app): usage fault
 * "Illegal use of the EPSR" at 0x21396 = `st25dv_read_chip_ids+0x3a`, the
 * `blx r3` of exactly that call, at t = 0.0656 s (UART fault dump; r12 = 3).
 * The call became reachable for the first time once iteration 10's group-4 RAM
 * relocation gave the ST25DV i2c_dt_spec a real bus pointer, so
 * `serialization_ipc_ept_register` started returning a valid descriptor.
 *
 * Emitting the table relocates both the table and every pointer inside it;
 * `recon/symbols/g1_app_globals.ld` binds the `rodata_88a38` pin onto it.  The
 * canonical parity bodies in recon/app/src are untouched.  Same mechanism as
 * iteration 5's `g1_gpio_dt_specs.c`.
 * ------------------------------------------------------------------------- */

/* Address-taken only; the real prototypes live in the recovered sources. */
extern int ipc_send_len_prefixed_packet_locked_retry();
extern int ipc_ept_op_a_locked_retry();
extern unsigned int FUN_0007c86c();

typedef void (*g1_st25dv_op_fn)(void);

/* was rodata_88a38 (original 0x00088a38, 12 B) */
/* `retain`: the rodata_88a38 binding is a lazy linker-script PROVIDE, which
 * does not root the section against --gc-sections. */
const g1_st25dv_op_fn g1_st25dv_ops_table[3] __attribute__((used, retain)) = {
	(g1_st25dv_op_fn)ipc_send_len_prefixed_packet_locked_retry,
	(g1_st25dv_op_fn)ipc_ept_op_a_locked_retry,
	(g1_st25dv_op_fn)FUN_0007c86c,
};
