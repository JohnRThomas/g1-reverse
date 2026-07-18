# CPUAPP heap-local cohesion proof

The three remaining Zephyr `lib/os/heap.c` local identities are resolved only
inside their retained callers when `G1_APP_SDK_INLINE_COHESION` is enabled:

- `FUN_0007def6` / `free_list_remove` (two calls from `free_chunk`);
- `free_list_remove_bidx` (one call from `alloc_chunk`); and
- `merge_chunks` (two calls from `free_chunk`).

The implementation is transcribed from pinned NCS 2.5.1 / Zephyr 3.4.99
`zephyr/lib/os/heap.c` (SHA-256
`56662aa35c280aae3539f0f2f56e741917dd65a04ffa3c0190d7ea9ca9847278`;
definitions at lines 34, 60, and 125). The helpers are `static`,
`always_inline`, and guarded by the build-only cohesion macro. The default
canonical/parity path still calls the original external identities, so no
oracle boundary was weakened. No standalone, weak, or global helper body was
added.

## Verification

- `cfg_verify app free_chunk`: PASS, four reviewed merge combinations.
- `cfg_verify app FUN_0007df24`: PASS.
- `tools/test_app_heap_local_cohesion.py`: 5/5 PASS. It cross-compiles the
  canonical and symbolized owners in both modes, confirms the default
  unresolved oracle boundaries, and proves the cohesive objects neither
  reference nor export the three local identities.
- `tools/full_link.py app`: 3097/3097 objects compiled, relocatable link
  returned 0, and none of the three identities appears in the undefined set.
- Retain-all Zephyr probe `/private/tmp/g1_cpuapp_shell_build_0717j`: both
  retained heap objects compiled into `app/libapp.a`; `nm -u` and `nm -g`
  show none of the three identities. The later final link still stops on the
  pre-existing retained-vs-SDK strong-owner collision set; it reports no
  group-A heap-local unresolved or duplicate owner.

Thus the measured SDK/config residue delta for this group is exactly three
symbols removed, with no new exported definition.
