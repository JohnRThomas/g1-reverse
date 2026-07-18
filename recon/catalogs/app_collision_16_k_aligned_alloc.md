# COLLISION-16: `k_aligned_alloc`

Verdict: **non-exact; retain under a recovered namespace**.

The firmware owner at `0x000758cc` has the public two-argument allocator ABI,
but it is not the configured 16-byte SDK wrapper. Its 78-byte true body checks
both Zephyr alignment assertions, logs the condition/message/source line, and
invokes the assertion post-action before tail-calling `z_heap_aligned_alloc`
with the system heap at `0x200037d8`. Authoritative CFG verification passes
three alignment cases.

The configured `zephyr/kernel/mempool.c` owner merely moves the two arguments,
loads `_system_heap`, and tail-calls `z_heap_aligned_alloc`. Relocation masking
cannot reconcile the missing branches and externally visible assertion/logging
side effects. The collision audit's low opcode (`0.205128`), shape (`0.153846`),
and length (`0.21875`) scores are therefore genuine, not an inflated-extent
artifact.

The only recovered direct caller is `malloc_impl` (`FUN_000868c2`) at
`0x000868c2`, an 8-byte `alignment=4` tail wrapper. It passes CFG verification
and is relocation-normalized exact to configured `k_malloc` (SHA-256
`54da22805bff6740e04bb8c1a8f1388cc6be145b295d194809cc8720893d33bd`).
That valid alignment does not make the owner replaceable because other callers
or exported uses can reach the assertion cases.

Implementation closure: rename `0x000758cc` to
`g1_recon_k_aligned_alloc_asserting`, update only `malloc_impl` to call that
owner, preserve raw/VA backmaps, and leave SDK `k_aligned_alloc`/`k_malloc`
untouched. Regeneration must remove exactly the old collision without producing
a namespace collision or unresolved symbol. No manifest exclusion is safe.
