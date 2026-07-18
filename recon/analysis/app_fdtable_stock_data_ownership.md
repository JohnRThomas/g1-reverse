# CPUAPP fdtable stock code/data closure

The pinned Zephyr 3.4.99 `lib/os/fdtable.c` object is the exact owner of the
firmware's POSIX descriptor table closure.  Relocation-masked section bytes
match `_check_fd` at `0x0004b01c`, `z_fd_unref.isra.0` at `0x0004b048`, `read`
at `0x0004b088`, `write` at `0x0004b0dc`, `close` at `0x0004b130`, and `lseek`
at `0x0004b17c`.  The first five functions had four retained reconstructed
bodies plus one missing standalone body; adopting the configured source unit
therefore removes four duplicates and fills the missing `close` owner.

The data references independently recover the stock layout:

- array base `0x20002548`;
- `CONFIG_POSIX_MAX_FDS=16` entries;
- `sizeof(struct fd_entry) == 0x28`;
- `refcount` at byte offset `8`;
- total initialized `.data.fdtable` size `16 * 0x28 == 0x280` bytes.

`g_fdtable_entries` and `g_fdtable_refcount_field` replace the former ambiguous
`g_posix_fd_table` / `g_fd_table` labels.  In cohesive builds the application
globalizes only the compiled archive's otherwise-local `fdtable` symbol, then
aliases recovered direct-field users to `fdtable` and `fdtable + 8`.  Zephyr's
source is not copied or patched, and there is only one runtime storage owner.

The current retain-all integration probe links that owner at `0x20002218`,
whereas the shipped image places it at `0x20002548`.  The remaining `0x330`
RAM-layout delta is explicitly **not** hidden with an absolute synthetic
symbol: exact placement must fall out of whole-image section and object-order
convergence.  This closure proves ownership and layout, not final global RAM
parity.

Private SDC ownership is untouched and remains report-only.
