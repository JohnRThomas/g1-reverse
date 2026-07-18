# COLLISION-11: `virtqueue_free`

Verdict: **exact configured OpenAMP adoption candidate**, not yet activated.

The old collision audit compared a 186-byte Ghidra extent against the configured
56-byte ELF section and therefore reported low opcode/shape/length scores. The
firmware function actually returns at `0x00070f12`: 46 bytes of Thumb code,
followed by the `_metal` and format-string literals through `0x00070f1b`.
Bytes after that belong to subsequent functions.

After masking the three ELF relocations (the `k_free` tail branch and two
literal words), all 56 bytes match exactly. The normalized SHA-256 is
`23c39b8c66df8e52ee7191e155d92ca205fea5d4ebd1e3d2b311159bcc4c950d`.
ABI, null handling, structure offsets, log gate/callback, format bytes, and the
final free call are identical. Authoritative verification of the recovered
owner passes two CFG cases (`vq == NULL` and non-NULL).

The sole reference-graph caller is `ipc_static_vrings_deinit` at `0x0007eda4`,
which calls `virtqueue_free` twice with the two `vr->vq[]` pointers. Although no
recovered caller source exists for `cfg_verify`, its complete 96-byte firmware
body is relocation-normalized exact to the configured Zephyr
`ipc_static_vrings.c` section (SHA-256
`fc20a970edb292a70fa87cf94c6dd33303b0834f1c9e366fa45ff7b8bbfd50f6`).
This proves the caller ABI and call ordering directly.

Implementation closure is one VA only: the configured `virtqueue.c.obj` is
already selected, `virtqueue_free` is its only retained collision, and removing
the reconstruction introduces no new undefined symbols. The implementation
step should add one explicit authorization for `0x00070ee4`, regenerate the
manifest/retained list, and require a retain-all collision delta of exactly
minus one with map/`nm` proof of the configured OpenAMP owner. No namespace
retention is needed.
